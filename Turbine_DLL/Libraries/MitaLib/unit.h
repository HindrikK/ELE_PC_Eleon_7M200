#ifndef __unit_h
#define __unit_h

#define UNIT_NONE          0     /* No unit */

/* Pressure */
#define UNIT_BAR           1     /* bar */
#define UNIT_MBAR          2     /* millibar */

/* Transmission speed */
#define UNIT_BPS           3     /* Bits per second */

/* Time */
#define UNIT_SECOND        4     /* Seconds */
#define UNIT_MINUTE        5     /* Minutes */
#define UNIT_HOUR          6     /* Hours */
#define UNIT_DAY           7     /* Days */
#define UNIT_MONTH         8     /* Months */
#define UNIT_YEAR          9     /* Years */

/* Amplification */
#define UNIT_DECIBEL       10    /* decibell */

/* Temperature */
#define UNIT_CELSIUS       11    /* Degree Celsius */

/* Frequency */
#define UNIT_HERTZ         12    /* Hertz */

/* Distance */
#define UNIT_METER         13    /* Metres */

/* Speed, velocity, angular velocity */
#define UNIT_MPS           14    /* Metres per second */
#define UNIT_RPM           15    /* Rotations per minute */

/* Angle */
#define UNIT_DEGREE        16    /* Degrees */

/* Current */
#define UNIT_AMPERE        17    /* Ampere */
#define UNIT_MAMPERE       18    /* Milliampere */

/* Voltage, potential */
#define UNIT_VOLT          19    /* Volt */

/* Power */
#define UNIT_WATT          20    /* Watt */
#define UNIT_KWATT         21    /* kilowatt */
#define UNIT_MWATT         22    /* Megawatt */
#define UNIT_VA            23    /* Volt-Ampere */
#define UNIT_KVA           24    /* kilo-Volt-Ampere */
#define UNIT_MVA           25    /* Mega-Volt-Ampere */
#define UNIT_VAR           26    /* Volt-Ampere-reaktiv */
#define UNIT_KVAR          27    /* kilo-Volt-Ampere-reactive */
#define UNIT_MVAR          28    /* Mega-volt-ampere-reactive */

/* Energy */
#define UNIT_WATTHOUR      29    /* Watt-hours */
#define UNIT_KWATTHOUR     30    /* Watt-hours */
#define UNIT_MWATTHOUR     31    /* Watt-hours */
#define UNIT_VAH           32    /* Volt-ampere-hours */
#define UNIT_KVAH          33    /* kilo-volt-ampere-hours */
#define UNIT_MVAH          34    /* Mega-volt-ampere-hours */
#define UNIT_VARH          35    /* Volt-ampere-reactive-hours */
#define UNIT_KVARH         36    /* kilo-volt-ampere-reactive-hours */
#define UNIT_MVARH         37    /* Mega-volt-ampere-reactive-hours */

/* Counts */
#define UNIT_TIMES         38    /* Times */
#define UNIT_COUNT         39    /* Counts */

/* Gravity */
#define UNIT_GRAVITY       40    /* Gravity */

/* Energy */
#define UNIT_WATTS         41    /* Watt-Seconds */
#define UNIT_VAS           42    /* Vols-Ampere-Seconds */
#define UNIT_VARS          43    /* Volt-Ampere-Reaktiv-Seconds */

/* Resistance */
#define UNIT_OHM           44    /* Resistance */

/* Angular velocity */
#define UNIT_DEGREESPSEC   45    /* Degress per second */

/* Angular acceleration */
#define UNIT_RPMPSEC       46    /* Revolutions per minute / s */

/* Number systems */
#define UNIT_HEX           47    /* Hexadecimal number */
#define UNIT_BIN           48    /* Binary number */
#define UNIT_OCT           49    /* Octal number */

/* Torque, effect and work due to torque */
#define UNIT_NM            50    /* Newton meters */
#define UNIT_NMSEC         51    /* Newton meters per second */
#define UNIT_NMRPM         52    /* Newton meters per revolutions per minute */

#define UNIT_PCT           53    /* % */

#define UNIT_BYTES         54    /* Bytes */
#define UNIT_KBYTES        55    /* K Bytes */
#define UNIT_MBYTES        56    /* M Bytes */

#define UNIT_PA            57    /* Pascal */
#define UNIT_HPA           58    /* hecto Pascal */

#define UNIT_VERSION       59    /* Indicates the content (U32) should be displayed as a version string */

#define UNIT_DEGREESPRPM   60    /* Degress per rpm */
#define UNIT_DEGREESPWATT  61    /* Degress per Watt */
#define UNIT_KWATTPSEC     62    /* Kilowatt per second */
#define UNIT_PSEC          63    /* Per second */
#define UNIT_PKWATT        64    /* Per Kilowatt */

#define UNIT_MAC           65    /* Ethernet Mac address - Indicates the content (U64) should be displayed as a MAC string*/
#define UNIT_IP            66    /* Ethernet IP address - Indicates the content (U32) should be displayed as a IP string */

#define UNIT_FARAD         67    /* Farad */
#define UNIT_MS            68    /* ms (milli seconds) */
#define UNIT_MMETER        69    /* milli metres */

#define UNIT_CLOCK         70    /* indicates the content (U64) should be displayed as a clock string (hh:mm:ss,ms) */
#define UNIT_PCTPSEC       71    // percent per second.

#define UNIT_CUBICMETER    72    // m3 
#define UNIT_CUBICMETERPH  73    // m3/h
#define UNIT_MWATTSPMIN    74    // MWh/min, 
#define UNIT_PCTPMIN       75    // %/min,
#define UNIT_CMPPMIN       76    // cm/min, 
#define UNIT_CUBICMETERN   77    // Nm3, 
#define UNIT_KVOLT         78    // kV, 
//#define UNIT_PCTPSEC2      79    // �/s2    UNIT_PCTPSEC is erroneous as it gives "�/s�" and should not
                                 //         be used. It is preserved only for backwards compatibility.
                                 //         Want "%/s�" ? Use UNIT_PERCENTPSEC2
#define UNIT_DEGREEPSEC2   79    // Correct spelling of define to be consistent with actual text "�/s�"
#define UNIT_LITR          80    // l(litr).

#define UNIT_DEGREESPKWATT 81    // Degrees per kiloWatt
#define UNIT_KVARPVOLT     82    // kilo-Volt-Ampere-reactive per Volt
#define UNIT_KELVIN        83    // Temperature - Degrees Kelvin. °K
#define UNIT_RPMPMPS       84    // rpm /(m/s)
#define UNIT_KVARPVOLTSEC  85    // kVar/(V*s)
#define UNIT_METERPSEC2    86    // meter per (second)^2
#define UNIT_AMPERESEC     87    // Ampere * second
#define UNIT_KGRAMMETER2   88    // kilo-gram-(meter)²
#define UNIT_NMPKWATT      89    // Newtonmeter per kiloWatt
#define UNIT_RADIANS       90    // Radians
#define UNIT_NMPKWATTSEC   91    // Newtonmeter per kiloWatt-second
#define UNIT_NMPRMPSEC     92    // Newtonmeter per rpm-second
#define UNIT_PSEC2         93    // Per (second)^2
#define UNIT_PULSEPREVOLUT 94    // Imp/rpm Imp/rpm
#define UNIT_NMPSEC2       95    // Newtonmeter per (second)^2
#define UNIT_MILIHERZ      96    // mili Hertz
#define UNIT_NMRAD         97    // Newtonmeter-radians
#define UNIT_RADPSEC       98    // Radians per second
#define UNIT_PCTPHERZ      99    // Percent per Hertz
#define UNIT_PERCENTPSEC2 100    // Percent per (second)^2. Use this instead of UNIT_PCTPSEC2
#define UNIT_KGRAMPMETER3 101    // Kilogram per (meter)^3. Used for air density


// Defines to convert from ms.
#define SEC       (1000)
#define MINUTE    (60 * SEC)
#define HOUR      (60 * MINUTE)
#define DAY       (24 * HOUR)
#define WEEK      (7 * DAY)



// Defines related to UNIT_CLOCK

// UNIT_CLOCK is stored in a U64 and it is encoded as follows:
//
//       msb                                                                               lsb
//      ---------------------------------------------------------------------------------------
//     |  byte 7  |  byte 6  |  byte 5  |  byte 4  |  byte 3  |  byte 2  |  byte 1  |  byte 0  |
//     |---------------------|---------------------|----------|----------|---------------------|
//     | unused              | hours               | minutes  | seconds  | milliseconds        |
//     |                     | (0-65535)           | (0-59)   | (0-59)   | (0-999)             |
//      ---------------------------------------------------------------------------------------
//
#define UNIT_CLOCK_PRECISION_H         3     // Format = "h"
#define UNIT_CLOCK_PRECISION_H_M       2     // Format = "h:mm"
#define UNIT_CLOCK_PRECISION_H_M_S     1     // Format = "h:mm:ss"
#define UNIT_CLOCK_PRECISION_H_M_S_MS  0     // Format = "h:mm:ss.ms"

#define UNIT_CLOCK_FORMAT_H            "%u"
#define UNIT_CLOCK_FORMAT_H_M          UNIT_CLOCK_FORMAT_H":%02u"
#define UNIT_CLOCK_FORMAT_H_M_S        UNIT_CLOCK_FORMAT_H_M":%02u"
#define UNIT_CLOCK_FORMAT_H_M_S_MS     UNIT_CLOCK_FORMAT_H_M_S".%03u"

#define UNIT_CLOCK_MINUTES_MAX         59
#define UNIT_CLOCK_MINUTES_MIN         0
#define UNIT_CLOCK_SECONDS_MAX         59
#define UNIT_CLOCK_SECONDS_MIN         0
#define UNIT_CLOCK_MILLISECONDS_MAX    999
#define UNIT_CLOCK_MILLISECONDS_MIN    0


#endif
