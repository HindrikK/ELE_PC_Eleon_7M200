#ifndef BLADED_DISCON_IF_H
#define BLADED_DISCON_IF_H

extern unsigned char MenuServer_enabled;

__declspec(dllexport)
void __cdecl DISCON(float* avrSWAP, int* aviFAIL, char* accINFILE, char* avcOUTNAME, char* avcMSG);

#endif /* BLADED_DISCON_IF_H */
