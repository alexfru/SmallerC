/*
  Copyright (c) 2016, Alexey Frunze
  2-clause BSD license.
*/
#ifndef __INTTYPES_H
#define __INTTYPES_H

#include <stdint.h>

#define PRId8 "d"
#define PRIdLEAST8 "d"
#define PRIdFAST8 "d"
#define PRIi8 "i"
#define PRIiLEAST8 "i"
#define PRIiFAST8 "i"
#define PRIo8 "o"
#define PRIoLEAST8 "o"
#define PRIoFAST8 "o"
#define PRIu8 "u"
#define PRIuLEAST8 "u"
#define PRIuFAST8 "u"
#define PRIx8 "x"
#define PRIxLEAST8 "x"
#define PRIxFAST8 "x"
#define PRIX8 "X"
#define PRIXLEAST8 "X"
#define PRIXFAST8 "X"

#define PRId16 "d"
#define PRIdLEAST16 "d"
#define PRIdFAST16 "d"
#define PRIi16 "i"
#define PRIiLEAST16 "i"
#define PRIiFAST16 "i"
#define PRIo16 "o"
#define PRIoLEAST16 "o"
#define PRIoFAST16 "o"
#define PRIu16 "u"
#define PRIuLEAST16 "u"
#define PRIuFAST16 "u"
#define PRIx16 "x"
#define PRIxLEAST16 "x"
#define PRIxFAST16 "x"
#define PRIX16 "X"
#define PRIXLEAST16 "X"
#define PRIXFAST16 "X"

#ifdef __SMALLER_C_16__
#define PRIdMAX "d"
#define PRIiMAX "i"
#define PRIoMAX "o"
#define PRIuMAX "u"
#define PRIxMAX "x"
#define PRIXMAX "X"
#endif

#ifdef __SMALLER_C_32__
#define PRId32 "d"
#define PRIdLEAST32 "d"
#define PRIdFAST32 "d"
#define PRIi32 "i"
#define PRIiLEAST32 "i"
#define PRIiFAST32 "i"
#define PRIo32 "o"
#define PRIoLEAST32 "o"
#define PRIoFAST32 "o"
#define PRIu32 "u"
#define PRIuLEAST32 "u"
#define PRIuFAST32 "u"
#define PRIx32 "x"
#define PRIxLEAST32 "x"
#define PRIxFAST32 "x"
#define PRIX32 "X"
#define PRIXLEAST32 "X"
#define PRIXFAST32 "X"

#define PRIdMAX "ld"
#define PRIiMAX "li"
#define PRIoMAX "lo"
#define PRIuMAX "lu"
#define PRIxMAX "lx"
#define PRIXMAX "lX"
#endif

#define PRIdPTR "d"
#define PRIiPTR "i"
#define PRIoPTR "o"
#define PRIuPTR "u"
#define PRIxPTR "x"
#define PRIXPTR "X"

#define SCNd8 "hhd"
#define SCNdLEAST8 "hhd"
#define SCNdFAST8 "hhd"
#define SCNi8 "hhi"
#define SCNiLEAST8 "hhi"
#define SCNiFAST8 "hhi"
#define SCNo8 "hho"
#define SCNoLEAST8 "hho"
#define SCNoFAST8 "hho"
#define SCNu8 "hhu"
#define SCNuLEAST8 "hhu"
#define SCNuFAST8 "hhu"
#define SCNx8 "hhx"
#define SCNxLEAST8 "hhx"
#define SCNxFAST8 "hhx"

#define SCNd16 "hd"
#define SCNdLEAST16 "hd"
#define SCNdFAST16 "hd"
#define SCNi16 "hi"
#define SCNiLEAST16 "hi"
#define SCNiFAST16 "hi"
#define SCNo16 "ho"
#define SCNoLEAST16 "ho"
#define SCNoFAST16 "ho"
#define SCNu16 "hu"
#define SCNuLEAST16 "hu"
#define SCNuFAST16 "hu"
#define SCNx16 "hx"
#define SCNxLEAST16 "hx"
#define SCNxFAST16 "hx"

#ifdef __SMALLER_C_16__
#define SCNdMAX "d"
#define SCNiMAX "i"
#define SCNoMAX "o"
#define SCNuMAX "u"
#define SCNxMAX "x"
#endif

#ifdef __SMALLER_C_32__
#define SCNd32 "d"
#define SCNdLEAST32 "d"
#define SCNdFAST32 "d"
#define SCNi32 "i"
#define SCNiLEAST32 "i"
#define SCNiFAST32 "i"
#define SCNo32 "o"
#define SCNoLEAST32 "o"
#define SCNoFAST32 "o"
#define SCNu32 "u"
#define SCNuLEAST32 "u"
#define SCNuFAST32 "u"
#define SCNx32 "x"
#define SCNxLEAST32 "x"
#define SCNxFAST32 "x"

#define SCNdMAX "ld"
#define SCNiMAX "li"
#define SCNoMAX "lo"
#define SCNuMAX "lu"
#define SCNxMAX "lx"
#endif

#define SCNdPTR "d"
#define SCNiPTR "i"
#define SCNoPTR "o"
#define SCNuPTR "u"
#define SCNxPTR "x"

#ifdef __SMALLER_C_16__
typedef struct { int quot, rem; } imaxdiv_t;
#endif

#ifdef __SMALLER_C_32__
typedef struct { long quot, rem; } imaxdiv_t;
#endif

// TBD!!! imaxabs(), imaxdiv(), strtoimax(), strtoumax()

#endif
