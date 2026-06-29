#ifndef DISCON_DEFS_H
#define DISCON_DEFS_H


/*
 * DNV Bladed (v4.18) Legacy Swap Array Interface
 * - Swap array index definitions are 1-based (record 1 is the first element). :contentReference[oaicite:1]{index=1}
 * - SI units are used throughout. :contentReference[oaicite:2]{index=2}
 */


 /* 1 */
#define SWAP_STATUS_FLAG                                    1  /* Status Flag [ - ] */

/* 2-3 */
#define SWAP_CURRENT_TIME                                   2  /* Current time [s] */
#define SWAP_COMMUNICATION_INTERVAL                         3  /* Communication interval [s] */

/* 4-12 (pitch signals and limits) */
#define SWAP_BLADE1_PITCH_ANGLE                             4  /* Blade 1 pitch angle [rad] */
#define SWAP_BELOW_RATED_PITCH_SETPOINT                     5  /* Below-rated pitch angle set-point [ - ] */
#define SWAP_MIN_PITCH_ANGLE                                6  /* Minimum pitch angle [rad] */
#define SWAP_MAX_PITCH_ANGLE                                7  /* Maximum pitch angle [rad] */
#define SWAP_MIN_PITCH_RATE                                 8  /* Minimum pitch rate (most negative allowed) [rad/s] */
#define SWAP_MAX_PITCH_RATE                                 9  /* Maximum pitch rate [rad/s] */
#define SWAP_PITCH_ACTUATOR_TYPE                           10  /* 0=position actuator, 1=rate actuator [ - ] */
#define SWAP_CURRENT_DEMANDED_PITCH_ANGLE                  11  /* Current demanded pitch angle [rad] */
#define SWAP_CURRENT_DEMANDED_PITCH_RATE                   12  /* Current demanded pitch rate [rad/s] */

/* 13-24 (power/speed/torque/yaw) */
#define SWAP_DEMANDED_POWER                                13  /* Demanded power [W] */
#define SWAP_MEASURED_SHAFT_POWER                          14  /* Measured shaft power [W] */
#define SWAP_MEASURED_ELECTRICAL_POWER_OUTPUT              15  /* Measured electrical power output [W] */
#define SWAP_OPTIMAL_MODE_GAIN                             16  /* Optimal mode gain [N*m*s^2/rad^2] */
#define SWAP_MIN_GENERATOR_SPEED                           17  /* Minimum generator speed [rad/s] */
#define SWAP_OPTIMAL_MODE_MAX_SPEED                        18  /* Optimal mode maximum speed [rad/s] */
#define SWAP_REF_GENERATOR_SPEED_ABOVE_RATED               19  /* Demanded generator speed above rated [rad/s] */
#define SWAP_MEASURED_GENERATOR_SPEED                      20  /* Measured generator speed [rad/s] */
#define SWAP_MEASURED_ROTOR_SPEED                          21  /* Measured rotor speed [rad/s] */
#define SWAP_REF_GENERATOR_TORQUE_ABOVE_RATED              22  /* Demanded generator torque above rated [N*m] */
#define SWAP_MEASURED_GENERATOR_TORQUE                     23  /* Measured generator torque [N*m] */
#define SWAP_MEASURED_YAW_ERROR                            24  /* Measured yaw error [rad] */

/* 25-26 (below-rated torque-speed lookup table) */
#define SWAP_LUT_START_RECORD_R                            25  /* Start of below-rated torque-speed lookup table (=R) [record number] */
#define SWAP_LUT_NUM_POINTS_N                              26  /* Number of points in lookup table (=N) [ - ] */

/* 27-29 */
#define SWAP_HUB_WIND_SPEED                                27  /* Hub wind speed [m/s] */
#define SWAP_PITCH_CONTROL_MODE                            28  /* Pitch control: 0=collective, 1=individual [ - ] */
#define SWAP_YAW_CONTROL_MODE                              29  /* Yaw control: 0=yaw rate control, 1=yaw torque control [ - ] */

/* 30-32 */
#define SWAP_BLADE1_ROOT_OOP_BENDING_MOMENT                30  /* Blade 1 root out-of-plane bending moment [N*m] (hinged-blade note: flap angle [rad]) */
#define SWAP_BLADE2_ROOT_OOP_BENDING_MOMENT                31  /* Blade 2 root out-of-plane bending moment [N*m] (hinged-blade note: flap angle [rad]) */
#define SWAP_BLADE3_ROOT_OOP_BENDING_MOMENT                32  /* Blade 3 root out-of-plane bending moment [N*m] (hinged-blade note: flap angle [rad]) */

/* 33-34 */
#define SWAP_BLADE2_PITCH_ANGLE                            33  /* Blade 2 pitch angle [rad] */
#define SWAP_BLADE3_PITCH_ANGLE                            34  /* Blade 3 pitch angle [rad] */

/* 35-37 */
#define SWAP_GENERATOR_CONTACTOR                           35  /* Generator contactor [ - ] */
#define SWAP_SHAFT_BRAKE_STATUS_FLAG                       36  /* Shaft brake status bit-flag [ - ] (see Table 2 indices) */
#define SWAP_NACELLE_ANGLE_FROM_NORTH                      37  /* Nacelle angle from North [rad] */

/* 38-40 */
#define SWAP_DEMANDED_AILERON_ANGLE_B1                     38  /* Demanded aileron angle (combined with pitch), blade 1 [rad] (hinged-blade note: record 38 used as hinge restraint switch [ - ]) */
#define SWAP_DEMANDED_AILERON_ANGLE_B2                     39  /* Demanded aileron angle (combined with pitch), blade 2 [rad] */
#define SWAP_DEMANDED_AILERON_ANGLE_B3                     40  /* Demanded aileron angle (combined with pitch), blade 3 [rad] */

/* 41-48 */
#define SWAP_DEMANDED_YAW_ACTUATOR_TORQUE                  41  /* Demanded yaw actuator torque [N*m] */
#define SWAP_DEMANDED_BLADE1_PITCH_INDIV                   42  /* Demanded blade 1 individual pitch position or rate [rad or rad/s] */
#define SWAP_DEMANDED_BLADE2_PITCH_INDIV                   43  /* Demanded blade 2 individual pitch position or rate [rad or rad/s] */
#define SWAP_DEMANDED_BLADE3_PITCH_INDIV                   44  /* Demanded blade 3 individual pitch position or rate [rad or rad/s] */
#define SWAP_DEMANDED_COLLECTIVE_PITCH_ANGLE               45  /* Demanded collective pitch angle [rad] */
#define SWAP_DEMANDED_COLLECTIVE_PITCH_RATE                46  /* Demanded collective pitch rate [rad/s] */
#define SWAP_DEMANDED_GENERATOR_TORQUE                     47  /* Demanded generator torque [N*m] */
#define SWAP_DEMANDED_NACELLE_YAW_RATE                     48  /* Demanded nacelle yaw rate [rad/s] */

/* 49-52 */
#define SWAP_MESSAGE_LENGTH_OR_NEG_M0                      49  /* OUT: message length OR -M0 [ - ]; IN: max chars allowed in MESSAGE [ - ] */
#define SWAP_INFILE_CHAR_COUNT                             50  /* Number of characters in INFILE argument [ - ] */
#define SWAP_OUTNAME_CHAR_COUNT                            51  /* Number of characters in OUTNAME argument [ - ] */
#define SWAP_DLL_INTERFACE_VERSION                         52  /* DLL interface version number (reserved) [ - ] */

/* 53-56 */
#define SWAP_TOWER_TOP_FOREAFT_ACCEL                       53  /* Tower top fore-aft acceleration [m/s^2] */
#define SWAP_TOWER_TOP_SIDESIDE_ACCEL                      54  /* Tower top side-to-side acceleration [m/s^2] */
#define SWAP_PITCH_OVERRIDE_STATUS                         55  /* Pitch override [ - ] */
#define SWAP_TORQUE_OVERRIDE_STATUS                        56  /* Torque override [ - ] */

/* 57-59 (reserved / hinged-blade note: hinge moment add-ins) */
#define SWAP_RESERVED_57_OR_HINGE_MOMENT_B1                57  /* Reserved [ - ] (hinged-blade note: hinge moment add-in blade 1 [N*m]) */
#define SWAP_RESERVED_58_OR_HINGE_MOMENT_B2                58  /* Reserved [ - ] (hinged-blade note: hinge moment add-in blade 2 [N*m]) */
#define SWAP_RESERVED_59_OR_HINGE_MOMENT_B3                59  /* Reserved [ - ] (hinged-blade note: hinge moment add-in blade 3 [N*m]) */

/* 60-65 */
#define SWAP_ROTOR_AZIMUTH_ANGLE                           60  /* Rotor azimuth angle [rad] */
#define SWAP_NUMBER_OF_BLADES                              61  /* Number of blades [ - ] */
#define SWAP_MAX_LOGGING_VALUES                            62  /* Maximum number of values which can be returned for logging [ - ] */
#define SWAP_LOGGING_START_RECORD                          63  /* Record number for start of logging output [ - ] */
#define SWAP_MAX_OUTNAME_CHARS                             64  /* Maximum number of characters which can be returned in OUTNAME [ - ] */
#define SWAP_NUM_LOGGING_VARIABLES_RETURNED                65  /* Number of variables returned for logging [ - ] */

/* 66-68 (not listed as fixed rows; referenced by hinged-blade note) */
#define SWAP_FLAP_VELOCITY_B1                              66  /* Hinged-blade note: flap velocity blade 1 [rad/s] */
#define SWAP_FLAP_VELOCITY_B2                              67  /* Hinged-blade note: flap velocity blade 2 [rad/s] */
#define SWAP_FLAP_VELOCITY_B3                              68  /* Hinged-blade note: flap velocity blade 3 [rad/s] */

/* 69-72 */
#define SWAP_BLADE1_ROOT_IP_BENDING_MOMENT                 69  /* Blade 1 root in-plane bending moment [N*m] */
#define SWAP_BLADE2_ROOT_IP_BENDING_MOMENT                 70  /* Blade 2 root in-plane bending moment [N*m] */
#define SWAP_BLADE3_ROOT_IP_BENDING_MOMENT                 71  /* Blade 3 root in-plane bending moment [N*m] */
#define SWAP_GENERATOR_STARTUP_RESISTANCE_FOR_LOGGING      72  /* Generator startup resistance for logging [ohm/phase] */

/* 73-78 */
#define SWAP_ROTATING_HUB_MY_GL                            73  /* Rotating hub My (GL co-ords) [N*m] */
#define SWAP_ROTATING_HUB_MZ_GL                            74  /* Rotating hub Mz (GL co-ords) [N*m] */
#define SWAP_FIXED_HUB_MY_GL                               75  /* Fixed hub My (GL co-ords) [N*m] */
#define SWAP_FIXED_HUB_MZ_GL                               76  /* Fixed hub Mz (GL co-ords) [N*m] */
#define SWAP_YAW_BEARING_MY_GL                             77  /* Yaw bearing My (GL co-ords) [N*m] */
#define SWAP_YAW_BEARING_MZ_GL                             78  /* Yaw bearing Mz (GL co-ords) [N*m] */

/* 79-84 */
#define SWAP_REQUEST_FOR_LOADS                             79  /* Request for loads [ - ] */
#define SWAP_VARIABLE_SLIP_STATUS                          80  /* 1=variable slip current demand uses record 81 [ - ] */
#define SWAP_VARIABLE_SLIP_CURRENT_DEMAND                  81  /* Variable slip current demand [A] */
#define SWAP_NACELLE_ROLL_ACCEL                            82  /* Nacelle roll acceleration [rad/s^2] */
#define SWAP_NACELLE_NODDING_ACCEL                         83  /* Nacelle nodding acceleration [rad/s^2] */
#define SWAP_NACELLE_YAW_ACCEL                             84  /* Nacelle yaw acceleration [rad/s^2] */

/* 85-89 reserved */

/* 90-94 */
#define SWAP_REALTIME_SIM_TIMESTEP                         90  /* Real time simulation time step [s] */
#define SWAP_REALTIME_TIMESTEP_MULTIPLIER                  91  /* Real time simulation time step multiplier [ - ] */
#define SWAP_MEAN_WIND_SPEED_INCREMENT                     92  /* Mean wind speed increment [m/s] */
#define SWAP_TURBULENCE_INTENSITY_INCREMENT                93  /* Turbulence intensity increment [%] */
#define SWAP_WIND_DIRECTION_INCREMENT                      94  /* Wind direction increment [rad] */

/* 95-96 reserved */

/* 97-101 */
#define SWAP_ACTIVE_SAFETY_SYSTEM_NUMBER                   97  /* Safety system number that has been activated [ - ] */
#define SWAP_SAFETY_SYSTEM_NUMBER_TO_ACTIVATE              98  /* Safety system number to activate [ - ] */
#define SWAP_PITCH_ACTUATOR_TORQUE_START_P                 99  /* Start of pitch actuator torque (=P) [record number] */
#define SWAP_NUM_PITCH_ACTUATOR_TORQUES_NP                100  /* Number of pitch actuator torques (=NP) [ - ] */
#define SWAP_NOMINAL_START_WIND_SPEED                     101  /* Mean or start wind speed [m/s] */

/* 102-104 */
#define SWAP_YAW_CONTROL_FLAG                             102  /* Yaw control flag [ - ] */
#define SWAP_YAW_STIFFNESS                                103  /* Yaw stiffness if record 102 = 1 or 3 [ - ] */
#define SWAP_YAW_DAMPING                                  104  /* Yaw damping if record 102 = 2 or 3 [ - ] */

/* 105-106 reserved (explicitly listed) */
#define SWAP_RESERVED_105                                 105  /* Reserved [ - ] */
#define SWAP_RESERVED_106                                 106  /* Reserved [ - ] */

/* 107-114 */
#define SWAP_BRAKE_TORQUE_DEMAND                          107  /* Brake torque demand [N*m] */
#define SWAP_YAW_BRAKE_TORQUE_DEMAND                      108  /* Yaw brake torque demand [N*m] */
#define SWAP_MEASURED_SHAFT_TORQUE                        109  /* Shaft torque (= hub Mx for clockwise rotor) [N*m] */
#define SWAP_FIXED_HUB_FX                                 110  /* Hub fixed Fx [N] */
#define SWAP_FIXED_HUB_FY                                 111  /* Hub fixed Fy [N] */
#define SWAP_FIXED_HUB_FZ                                 112  /* Hub fixed Fz [N] */
#define SWAP_NETWORK_VOLTAGE_DISTURBANCE_FACTOR           113  /* Network voltage disturbance factor [ - ] */
#define SWAP_NETWORK_FREQUENCY_DISTURBANCE_FACTOR         114  /* Network frequency disturbance factor [ - ] */

/* 115-116 reserved */

/* 117-119 */
#define SWAP_CONTROLLER_STATE                             117  /* Controller state  0: Power production
                                                                                    1: Parked
                                                                                    2: Idling
                                                                                    3: Startup
                                                                                    4: Normal stop
                                                                                    5: Emergency stop
                                                                                    */
#define SWAP_SETTLING_TIME                                118  /* Settling time (time to start writing output) [s] */
#define SWAP_RESERVED_119_SETTEETERLOCK                   119  /* Reserved (SetTeeterLock) [ - ] */

/* 120-129 (user-defined variables 1..10) */
#define SWAP_USER_DEFINED_VAR_1                           120  /* User-defined variable 1 [ - ] */
#define SWAP_USER_DEFINED_VAR_2                           121  /* User-defined variable 2 [ - ] */
#define SWAP_USER_DEFINED_VAR_3                           122  /* User-defined variable 3 [ - ] */
#define SWAP_USER_DEFINED_VAR_4                           123  /* User-defined variable 4 [ - ] */
#define SWAP_USER_DEFINED_VAR_5                           124  /* User-defined variable 5 [ - ] */
#define SWAP_USER_DEFINED_VAR_6                           125  /* User-defined variable 6 [ - ] */
#define SWAP_USER_DEFINED_VAR_7                           126  /* User-defined variable 7 [ - ] */
#define SWAP_USER_DEFINED_VAR_8                           127  /* User-defined variable 8 [ - ] */
#define SWAP_USER_DEFINED_VAR_9                           128  /* User-defined variable 9 [ - ] */
#define SWAP_USER_DEFINED_VAR_10                          129  /* User-defined variable 10 [ - ] */

/* 130-136 (hardware-in-loop pitch signals) */
#define SWAP_HW_PITCH_POSITION_B1                         130  /* Hardware pitch position blade 1 [rad] */
#define SWAP_HW_PITCH_POSITION_B2                         131  /* Hardware pitch position blade 2 [rad] */
#define SWAP_HW_PITCH_POSITION_B3                         132  /* Hardware pitch position blade 3 [rad] */
#define SWAP_HW_PITCH_RATE_B1                             133  /* Hardware pitch rate blade 1 [rad/s] */
#define SWAP_HW_PITCH_RATE_B2                             134  /* Hardware pitch rate blade 2 [rad/s] */
#define SWAP_HW_PITCH_RATE_B3                             135  /* Hardware pitch rate blade 3 [rad/s] */
#define SWAP_HW_UPDATE_INDICATOR                          136  /* Update indicator for position/rate signals (130-135) [ - ] */

/* 137-144 (pitch bearing / teeter) */
#define SWAP_PITCH_BEARING_MZ_B1                          137  /* Pitch bearing Mz blade 1 [N*m] */
#define SWAP_PITCH_BEARING_MZ_B2                          138  /* Pitch bearing Mz blade 2 [N*m] */
#define SWAP_PITCH_BEARING_MZ_B3                          139  /* Pitch bearing Mz blade 3 [N*m] */
#define SWAP_PITCH_BEARING_FRICTION_B1                    140  /* Pitch bearing friction blade 1 [N*m] */
#define SWAP_PITCH_BEARING_FRICTION_B2                    141  /* Pitch bearing friction blade 2 [N*m] */
#define SWAP_PITCH_BEARING_FRICTION_B3                    142  /* Pitch bearing friction blade 3 [N*m] */
#define SWAP_TEETER_ANGLE                                 143  /* Teeter angle [rad] */
#define SWAP_TEETER_VELOCITY                              144  /* Teeter velocity [rad/s] */

/* 145-150 (pitch bearing forces) */
#define SWAP_PITCH_BEARING_FXY_B1                         145  /* Pitch bearing Fxy blade 1 [N] */
#define SWAP_PITCH_BEARING_FXY_B2                         146  /* Pitch bearing Fxy blade 2 [N] */
#define SWAP_PITCH_BEARING_FXY_B3                         147  /* Pitch bearing Fxy blade 3 [N] */
#define SWAP_PITCH_BEARING_FZ_B1                          148  /* Pitch bearing Fz blade 1 [N] */
#define SWAP_PITCH_BEARING_FZ_B2                          149  /* Pitch bearing Fz blade 2 [N] (text view shows unit as '[-]' due to formatting) */
#define SWAP_PITCH_BEARING_FZ_B3                          150  /* Pitch bearing Fz blade 3 [N] (text view shows blade 2 twice due to formatting) */

/* 151-153 obsolete */

/* 154-155 (LIDAR) */
#define SWAP_NUM_LIDAR_BEAMS_BF                           154  /* Number of effectively independent LIDAR beams (BF) [ - ] */
#define SWAP_NUM_LIDAR_FOCAL_POINTS_NF                    155  /* Number of focal points (NF) [ - ] */

/* 156-157 obsolete */

/* 158 (active dampers) */
#define SWAP_NUM_ACTIVE_DAMPERS_ND                        158  /* Number of active dampers (=ND) [count] (text view shows unit 'rad' due to formatting) */

/* 159-160 obsolete */

/* 161-165 */
#define SWAP_CONTROLLER_FAILURE_FLAG                      161  /* Controller failure flag [ - ] */
#define SWAP_YAW_BEARING_ANGULAR_POSITION                 162  /* Yaw bearing angular position [rad] */
#define SWAP_YAW_BEARING_ANGULAR_VELOCITY                 163  /* Yaw bearing angular velocity [rad/s] */
#define SWAP_YAW_BEARING_ANGULAR_ACCEL                    164  /* Yaw bearing angular acceleration [rad/s^2] */
#define SWAP_YAW_MOTOR_RATE_DEMAND                        165  /* Yaw motor rate demand [rad/s] */

/* 166-168 (additional user-defined variables metadata) */
#define SWAP_ADDITIONAL_UDV_START_NUMBER                  166  /* Start number for additional user-defined variables (=UDV) [ - ] */
#define SWAP_ADDITIONAL_UDV_READONLY_COUNT_NUDVR          167  /* Number of additional read-only user-defined variables (=NUDVR) [ - ] */
#define SWAP_ADDITIONAL_UDV_WRITEONLY_COUNT_NUDVW         168  /* Number of additional write-only user-defined variables (=NUDVW) [ - ] */

/* 169 obsolete */

/* 170-171 (grid-side converter d-axis control) */
#define SWAP_GSC_D_AXIS_CONTROL_TYPE                      170  /* Grid side converter d-axis control type [rad/s^2] */
#define SWAP_GSC_D_AXIS_CONTROL_REFERENCE                 171  /* Grid side converter d-axis control reference value [rad/s^2] */




/* Torque-speed lookup table region (below-rated):
 * - R = SWAP_LUT_START_RECORD_R
 * - N = SWAP_LUT_NUM_POINTS_N
 * - Records R..R+2N-1 store pairs: speed_1, torque_1, speed_2, torque_2, ... :contentReference[oaicite:3]{index=3}
 */
#define SWAP_LUT_PAIR_STRIDE_RECORDS                        2  /* Two records per point: speed then torque */
#define SWAP_LUT_SPEED_UNITS                               "rad/s"
#define SWAP_LUT_TORQUE_UNITS                              "N*m"

 /* Message block:
  * - If record 49 is < 0, then M0 is implied by (-record49), and:
  *   M0: message length; M1..Mn: message text (4 chars per record). :contentReference[oaicite:4]{index=4}
  */
#define SWAP_MESSAGE_CHARS_PER_RECORD                       4

  /* Logging output block:
   * - L1 onwards: variables returned for logging output (SI units). :contentReference[oaicite:5]{index=5}
   */

   /* -----------------------------------
	* Shaft brake flag indices
	* ----------------------------------- */
#define SWAP_BRAKE_INDEX_SHAFT_BRAKE_1                      1  /* Shaft brake 1 [ - ] */
#define SWAP_BRAKE_INDEX_SHAFT_BRAKE_2                      2  /* Shaft brake 2 [ - ] */
#define SWAP_BRAKE_INDEX_GENERATOR_BRAKE                    3  /* Generator brake [ - ] */
#define SWAP_BRAKE_INDEX_SHAFT_BRAKE_3                      4  /* Shaft brake 3 [ - ] */
#define SWAP_BRAKE_INDEX_BRAKE_TORQUE_RECORD_107            5  /* Brake torque set in record 107 [ - ] */


#endif /* DISCON_DEFS_H */