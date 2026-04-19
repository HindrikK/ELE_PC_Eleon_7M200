#include "Bladed_DISCON_Interface.h"

//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <ctype.h>
//#include <math.h>
#include "Bladed_SwapArray_Defs.h"
#include "DLL_InOut.h"

/*
  - Control loop time is hardcoded to 20ms.
  - Bladed legacy external controller interface DISCON().
  - Reads inputs from swap array and forwards to controller variables.
  - Writes controller outputs to swap array.

  Build notes (on Windows):
  - Build as x86 (32-bit), Release DLL.
*/

//#ifndef _WIN32
//#  define __cdecl
//#  define __declspec(x)
//#endif

/* ----------------- Helpers ----------------- */

static float clampf(float x, float lo, float hi)
{
    if (x < lo) return lo;
    if (x > hi) return hi;
    return x;
}

static float deg2rad(float deg)
{
    return deg * 0.01745329251994329577f/*pi/180*/;
}

static float rad2deg(float rad)
{
	return rad / 0.01745329251994329577f/*pi*180*/;
}

static float rad_s2rpm(float rad_s)
{
    return rad_s * 0.10472/*pi/30*/;
}

/* Convert 1-based record number to 0-based C index */
static int R(int record_1_based) { return record_1_based - 1; }

/* Safe message write into avcMSG (host may provide non-null-terminated buffer) */
static void write_msg(char* avcMSG, int msg_len, const char* s)
{
    int n;
    if (!avcMSG || msg_len <= 0 || !s) return;
    n = (int)strlen(s);
    if (n > msg_len - 1) n = msg_len - 1;
    memcpy(avcMSG, s, (size_t)n);
    avcMSG[n] = '\0';
}

/* Copy fixed-length char buffer to C string, trimming trailing spaces and NULs */
static void copy_trimmed(char* dst, int dst_cap, const char* src, int src_len)
{
    int n, i;
    if (!dst || dst_cap <= 0) return;
    dst[0] = '\0';
    if (!src || src_len <= 0) return;

    n = src_len;
    while (n > 0 && (src[n - 1] == '\0' || isspace((unsigned char)src[n - 1]))) n--;

    if (n > dst_cap - 1) n = dst_cap - 1;
    for (i = 0; i < n; ++i) dst[i] = src[i];
    dst[n] = '\0';
}

static void trim_inplace(char* s)
{
    char* p;
    size_t len;
    if (!s) return;

    /* left trim */
    p = s;
    while (*p && isspace((unsigned char)*p)) p++;
    if (p != s) memmove(s, p, strlen(p) + 1);

    /* right trim */
    len = strlen(s);
    while (len > 0 && isspace((unsigned char)s[len - 1])) {
        s[len - 1] = '\0';
        len--;
    }
}

/* ----------------- Controller params/state ----------------- */

typedef struct State {
    int   inited;
    float int_err;
    float last_time;
    FILE* log;
} State;

static State g;

/* key=value parser for controller parameter file */
static void load_params_from_file(const char* path)
{
    FILE* f;
    char line[512];

    if (!path || !*path) return;
    f = fopen(path, "r");
    if (!f) return;

    while (fgets(line, (int)sizeof(line), f)) {
		printf("DISCON: read line: '%s'\n", line);
        char* eq;
        char* key;
        char* val;
        char* c1;
        char* c2;
        char* c;

        /* strip comments starting with # or ! */
        c1 = strchr(line, '#');
        c2 = strchr(line, '!');
        c = NULL;
        if (c1 && c2) c = (c1 < c2) ? c1 : c2;
        else if (c1) c = c1;
        else if (c2) c = c2;
        if (c) *c = '\0';

        eq = strchr(line, '=');
        if (!eq) continue;
        *eq = '\0';

        key = line;
        val = eq + 1;
        trim_inplace(key);
        trim_inplace(val);
        if (!*key || !*val) continue;

        float x = (float)atof(val);

		if (strcmp(key, "controller_folder") == 0) snprintf(root_folder, (int)sizeof(root_folder), "%s", val);
        /*else if (strcmp(key, "p_rated") == 0) p->p_rated = x;
        else if (strcmp(key, "kopt") == 0) p->kopt = x;
        else if (strcmp(key, "torque_max") == 0) p->torque_max = x;
        else if (strcmp(key, "kp_pitch") == 0) p->kp_pitch = x;
        else if (strcmp(key, "ki_pitch") == 0) p->ki_pitch = x;
        else if (strcmp(key, "pitch_min_deg") == 0) p->pitch_min = deg2rad(x);
        else if (strcmp(key, "pitch_max_deg") == 0) p->pitch_max = deg2rad(x);*/
    }

    fclose(f);
}

/* ----------------- DISCON entry point ----------------- */
void DISCON(float* avrSWAP, int* aviFAIL, char* accINFILE, char* avcOUTNAME, char* avcMSG)
{
    int   iStatus;
    float t, dt;
    int   msg_len, infile_len, outname_len;
    char  inFile[512];
    char  outRoot[512];
    int result;

    if (aviFAIL) *aviFAIL = 0;

    if (!avrSWAP) {
        printf("DISCON: avrSWAP is NULL\n");
        write_msg(avcMSG, 256, "DISCON: avrSWAP is NULL");
        if (aviFAIL) *aviFAIL = -1;
        return;
    }

    /* Status flag in avrSWAP(1):
     * 0 = init
     * 1 = run
     * -1 = final
    */
    iStatus = (int)lround((double)avrSWAP[R(SWAP_STATUS_FLAG)]);

    /* Get string lengths from avrSWAP */
    msg_len = (int)lround((double)avrSWAP[R(SWAP_MESSAGE_LENGTH_OR_NEG_M0)]);
    infile_len = (int)lround((double)avrSWAP[R(SWAP_INFILE_CHAR_COUNT)]);
    outname_len = (int)lround((double)avrSWAP[R(SWAP_OUTNAME_CHAR_COUNT)]);

    if (msg_len <= 0) msg_len = 256;
    if (infile_len < 0) infile_len = 0;
    if (outname_len < 0) outname_len = 0;

    copy_trimmed(inFile, (int)sizeof(inFile), accINFILE, infile_len);
    copy_trimmed(outRoot, (int)sizeof(outRoot), avcOUTNAME, outname_len);

    t = avrSWAP[R(SWAP_CURRENT_TIME)];
    dt = avrSWAP[R(SWAP_COMMUNICATION_INTERVAL)];
    if (dt < 1e-4f) dt = 1e-4f;

    /* Inputs */
    {
        DLL_IN_PowerDemand = 9999;// avrSWAP[R(SWAP_DEMANDED_POWER)] * 1000;
        DLL_IN_GenSpeed = rad_s2rpm(avrSWAP[R(SWAP_MEASURED_ROTOR_SPEED)]) * 100;
        DLL_IN_HubWindSpeed = avrSWAP[R(SWAP_HUB_WIND_SPEED)];
        DLL_IN_WindDirectionRel = rad2deg(avrSWAP[R(SWAP_MEASURED_YAW_ERROR)]);
        DLL_IN_NacAccForeAft = avrSWAP[R(SWAP_TOWER_TOP_FOREAFT_ACCEL)] / 10;   // need to check
		DLL_IN_NacAccSideSide = avrSWAP[R(SWAP_TOWER_TOP_SIDESIDE_ACCEL)] / 10; // need to check
        DLL_IN_PitchAngle_1 = rad2deg(avrSWAP[R(SWAP_BLADE1_PITCH_ANGLE)]);
        DLL_IN_PitchAngle_2 = rad2deg(avrSWAP[R(SWAP_BLADE2_PITCH_ANGLE)]);
        DLL_IN_PitchAngle_3 = rad2deg(avrSWAP[R(SWAP_BLADE3_PITCH_ANGLE)]);
        DLL_IN_RotorAzimuth = rad2deg(avrSWAP[R(SWAP_ROTOR_AZIMUTH_ANGLE)]);
    }

    /* One-time init on first call */
    if (iStatus == 0 && !g.inited) {
        memset(&g, 0, sizeof(g));
        g.last_time = t;

		/* Load controller parameters from file if specified */
        if (inFile[0] != '\0') {
            load_params_from_file(inFile);
        }

		/* Write log file if output name specified */
        if (outRoot[0] != '\0') {
            char logPath[600];
            snprintf(logPath, (int)sizeof(logPath), "%s_Eleon_LOG.log", outRoot);
            g.log = fopen(logPath, "w");
            if (g.log) {
                fprintf(g.log, "DISCON: Init\n");
                fprintf(g.log, "DISCON: controller folder= '%s'\n", root_folder);
                fprintf(g.log, "DISCON: INFILE= '%s'\n", inFile);
                fprintf(g.log, "DISCON: OUTNAME= '%s'\n", outRoot);
            }
        }

        /* Check if controller directory is defined */
        if (root_folder[0] == '\0') {
            //printf("DISCON: 'controller_folder' unspecified\n");
            write_msg(avcMSG, 256, "DISCON: 'controller_folder' unspecified");
            if (aviFAIL) *aviFAIL = -1;
            return;
        }

        DLL_IN_Initialize = true;
        result = MainCall();    // make one call just to get initialized
        if (result < 0) {
            //printf("DISCON: Init failed(%d) in MainCall\n", result);
            write_msg(avcMSG, msg_len, "DISCON: Init failed in MainCall");
            if (g.log) {
                fprintf(g.log, "DISCON: Init failed(%d) in MainCall\n", result);
            }
            if (aviFAIL) *aviFAIL = -2;
            return;
		}
        DLL_IN_Initialize = false;

        g.inited = 1;
        //printf("DISCON: initialized OK\n");
        write_msg(avcMSG, msg_len, "DISCON: initialized OK");
        if (g.log) {
            fprintf(g.log, "DISCON: initialized OK\n");
        }

        DLL_IN_AllowStart = true;

        return;
    }

    /* Final call */
    if (iStatus == -1) {
        if (g.log) {
            fprintf(g.log, "DISCON: final call\n");
            fflush(g.log);
            fclose(g.log);
            g.log = NULL;
        }
        g.inited = 0;
        //printf("DISCON: final call\n");
        write_msg(avcMSG, msg_len, "DISCON: final call");
        return;
    }

    result = MainCall();
    if (result < 0) {
        //printf("DISCON: MainCall failed(%d)\n", result);
        write_msg(avcMSG, msg_len, "DISCON: MainCall failed\n");
        if (g.log) {
            fprintf(g.log, "DISCON: initialization failed(%d) in MainCall\n", result);
        }
        if (aviFAIL) *aviFAIL = -3;
        return;
    }

    /* Outputs */
    {
		//avrSWAP[R(SWAP_DEMANDED_COLLECTIVE_PITCH_ANGLE)] = 0;  // always set to 0 since we are using individual pitch control mode
        
        
        avrSWAP[R(SWAP_PITCH_OVERRIDE_STATUS)] = 0.0f;     // pitch override flag (0 => use DLL pitch demand)
        avrSWAP[R(SWAP_TORQUE_OVERRIDE_STATUS)] = 0.0f;    // torque override flag (0 => use DLL torque demand)

        //avrSWAP[R(SWAP)] = DLL_OUT_ActiveCP1CodeNo;
        avrSWAP[R(SWAP_CONTROLLER_STATE)] = DLL_OUT_OperationState;
        //avrSWAP[R(SWAP)] = DLL_OUT_PowerSetpoint;
        avrSWAP[R(SWAP_MEASURED_ELECTRICAL_POWER_OUTPUT)] = DLL_OUT_PowerOutput;
        avrSWAP[R(SWAP_DEMANDED_GENERATOR_TORQUE)] = DLL_OUT_GenTorque;
        avrSWAP[R(SWAP_GENERATOR_CONTACTOR)] = DLL_OUT_GenConnected ? 1.0f : 0.0f;
        avrSWAP[R(SWAP_DEMANDED_BLADE1_PITCH_INDIV)] = deg2rad(DLL_OUT_PitchAngle_1);
        avrSWAP[R(SWAP_DEMANDED_BLADE2_PITCH_INDIV)] = deg2rad(DLL_OUT_PitchAngle_2);
        avrSWAP[R(SWAP_DEMANDED_BLADE3_PITCH_INDIV)] = deg2rad(DLL_OUT_PitchAngle_3);

    }

    g.last_time = t;
    if (aviFAIL) *aviFAIL = 0;
}
