//********************************************************************
//
//            Copyright (c) 2003 Mita-Teknik a/s
//
//*******************************************************************
//
// $Date$
// $Author$
// $RCSfile$
// $Revision$
//
//*******************************************************************
#ifndef FILE_HASH_H
#define FILE_HASH_H

#include <os_lib.h>
#include <limits.h>

// ---------------------------------------------------------------------
// Only this module uses these variables and functions. (xx_lib.c and xx_app.c)
// ---------------------------------------------------------------------
#define SIZE_HASH_BUFFER       2048

#define sfx_lo(x,y) x##y
#define sfx_hi(x,y) sfx_lo(x,y)
#define n_u32(p)    sfx_hi(0x##p,s_u32)

/* define an unsigned 32-bit type */

#if UINT_MAX == 0xffffffff
  typedef   unsigned int     sha2_32t;
  #define s_u32    u
#elif ULONG_MAX == 0xffffffff
  typedef   unsigned long    sha2_32t;
  #define s_u32   ul
#else
#error Please define sha2_32t as an unsigned 32 bit type in Hash_256_t1_v1.h
#endif

#define SHA256_DIGEST_SIZE  32
#define SHA256_BLOCK_SIZE   64

  /* type to hold the SHA256 context				*/

  typedef struct
  {   sha2_32t count[2];
      sha2_32t hash[8];
      sha2_32t wbuf[16];
  } sha256_ctx;

  typedef struct
  {   union
      {   sha256_ctx  ctx256[1];
          //sha512_ctx  ctx512[1];
      } uu[1];
      sha2_32t    sha2_len;
  } sha2_ctx;

  void sha256_compile(sha256_ctx ctx[1]);

// ---------------------------------------------------------------------
// This module uses these variables and functions from other modules.
// ---------------------------------------------------------------------
void sha256_begin(sha256_ctx ctx[1]);
void sha256_hash(const unsigned char data[], unsigned long len, sha256_ctx ctx[1]);
void sha256_end(unsigned char hval[], sha256_ctx ctx[1]);

// ---------------------------------------------------------------------
// Other modules may uses these variables and functions.
// ---------------------------------------------------------------------

/********************************************************************

 FUNCTION NAME    ValidateHash
 -------------
 DESCRIPTION
 -----------      
                  The validation function to prevent from changing the
                  IPR data in PEPTOOL Objects.       
 
 ARGUMENTS
 ---------
   CopyRight      IPR string in Object.

   ModuleName     Name of the Object.

   InitValues     Hash string to compare with. Calculated by PEPTOOL.

 RETURN VALUES
 -------------
    0                       Success.
    ERR_LOADAPPL_WRONG_APPL Failure.

 HISTORY
 -------
    NAME         DATE        REMARKS
    ABO          2010-03-02  New function.
*******************************************************************/

extern STATUS ValidateHash(char *CopyRight, char *ModuleName, char *InitValues);

#endif

