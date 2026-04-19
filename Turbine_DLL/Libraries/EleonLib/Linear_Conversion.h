//*****************************PEPTOOL Header Start******************************
//                                                                               
//                            Copyright © 2014 Eleon.                            
//                                                                               
//*******************************************************************************
//                                                                               
// $PEPTOOL file version:103$                                                    
//                                                                               
//******************************PEPTOOL Header End*******************************

//***********************************************************************
#ifndef FILE_LINEAR_CONVERSION_H
#define FILE_LINEAR_CONVERSION_H

#include <lib_main.h>



//*******************************************************************************************
//
// "Input" value is converter to another scale by linear conversion.
// "OutLow" and "OutHigh" will act also as limits which the output will not ever exceed.
//
//*******************************************************************************************


S32 Linear_Conversion(S32/*Input*/, S32/*InLow*/, S32/*InHigh*/, S32/*OutLow*/, S32/*OutHigh*/);
S32 Linear_Conversion_Unlimited(S32/*Input*/, S32/*InLow*/, S32/*InHigh*/, S32/*OutLow*/, S32/*OutHigh*/);
F32 Linear_Conversion_F32(F32/*Input*/, F32/*InLow*/, F32/*InHigh*/, F32/*OutLow*/, F32/*OutHigh*/);
F32 Linear_Conversion_F32_Unlimited(F32/*Input*/, F32/*InLow*/, F32/*InHigh*/, F32/*OutLow*/, F32/*OutHigh*/);

#endif
