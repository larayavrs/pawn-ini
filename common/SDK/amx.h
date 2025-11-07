/*  Abstract Machine for the Pawn compiler
 *
 *  Copyright (c) ITB CompuPhase, 1997-2005
 *
 *  This software is provided "as-is", without any express or implied warranty.
 *  In no event will the authors be held liable for any damages arising from
 *  the use of this software.
 */

#ifndef AMX_H_INCLUDED
#define AMX_H_INCLUDED

#include <stddef.h>
#include <stdint.h>

#if defined(__cplusplus)
extern "C" {
#endif

#if defined(_WIN32)
  #if !defined AMX_NATIVE_CALL
    #define AMX_NATIVE_CALL __stdcall
  #endif
  #if !defined AMXAPI
    #define AMXAPI __stdcall
  #endif
#else
  #if !defined AMX_NATIVE_CALL
    #define AMX_NATIVE_CALL
  #endif
  #if !defined AMXAPI
    #define AMXAPI
  #endif
#endif

#if defined(__LCC__) || defined(__DMC__) || defined(LINUX) || defined(__GNUC__)
  #if defined(__64BIT__) || defined(__LP64__) || defined(_LP64)
    #if !defined __PAWNW64
      #define __PAWNW64
    #endif
  #endif
#endif

#if defined(__PAWNW64)
  typedef uint64_t cell;
  typedef int64_t  ucell;
#else
  typedef int32_t  cell;
  typedef uint32_t ucell;
#endif

struct tagAMX;
typedef cell (AMX_NATIVE_CALL *AMX_NATIVE)(struct tagAMX *amx, cell *params);
typedef int (AMXAPI *AMX_CALLBACK)(struct tagAMX *amx, cell index, cell *result, cell *params);
typedef int (AMXAPI *AMX_DEBUG)(struct tagAMX *amx);

#if !defined _FAR
  #define _FAR
#endif

#if defined _MSC_VER
  #pragma warning(disable:4103)  /* disable warning message 4103 that complains about pragma pack in a header file */
  #pragma warning(disable:4100)  /* "'%$S' : unreferenced formal parameter" */
#endif

#if defined __GNUC__
  #define PACKED        __attribute__((packed))
#else
  #define PACKED
#endif

#if defined __TURBOC__
  #pragma option -a-            /* "pack" pragma for Turbo C */
#elif defined(_MSC_VER)
  #pragma pack(1)               /* "pack" pragma for Microsoft C */
#endif

typedef struct tagAMX_NATIVE_INFO {
  const char _FAR *name;
  AMX_NATIVE func;
} AMX_NATIVE_INFO;

#define AMX_USERNUM     4

#define AMX_FLAG_DEBUG      0x02
#define AMX_FLAG_COMPACT    0x04
#define AMX_FLAG_BYTEOPC    0x08
#define AMX_FLAG_NOCHECKS   0x10
#define AMX_FLAG_BROWSE     0x4000
#define AMX_FLAG_RELOC      0x8000

typedef struct tagAMX_FUNCSTUB {
  ucell address;
  const char name[1];
} AMX_FUNCSTUB;

typedef struct tagFUNCSTUBNT {
  ucell address;
  uint32_t nameofs;
} AMX_FUNCSTUBNT;

#define AMX_EXEC_MAIN   (-1)
#define AMX_EXEC_CONT   (-2)

#define AMX_ERR_NONE      0
#define AMX_ERR_EXIT      1
#define AMX_ERR_ASSERT    2
#define AMX_ERR_STACKERR  3
#define AMX_ERR_BOUNDS    4
#define AMX_ERR_MEMACCESS 5
#define AMX_ERR_INVINSTR  6
#define AMX_ERR_STACKLOW  7
#define AMX_ERR_HEAPLOW   8
#define AMX_ERR_CALLBACK  9
#define AMX_ERR_NATIVE    10
#define AMX_ERR_DIVIDE    11
#define AMX_ERR_SLEEP     12
#define AMX_ERR_MEMORY    16
#define AMX_ERR_FORMAT    17
#define AMX_ERR_VERSION   18
#define AMX_ERR_NOTFOUND  19
#define AMX_ERR_INDEX     20
#define AMX_ERR_DEBUG     21
#define AMX_ERR_INIT      22
#define AMX_ERR_USERDATA  23
#define AMX_ERR_INIT_JIT  24
#define AMX_ERR_PARAMS    25
#define AMX_ERR_DOMAIN    26
#define AMX_ERR_GENERAL   27

typedef struct tagAMX_HEADER {
  int32_t size;
  uint16_t magic;
  char    file_version;
  char    amx_version;
  int16_t flags;
  int16_t defsize;
  int32_t cod;
  int32_t dat;
  int32_t hea;
  int32_t stp;
  int32_t cip;
  int32_t publics;
  int32_t natives;
  int32_t libraries;
  int32_t pubvars;
  int32_t tags;
  int32_t nametable;
} AMX_HEADER;

#define AMX_MAGIC       0xf1e0

typedef struct tagAMX {
  unsigned char _FAR *base;
  unsigned char _FAR *data;
  AMX_CALLBACK callback;
  AMX_DEBUG debug;
  cell cip;
  cell frm;
  cell hea;
  cell hlw;
  cell stk;
  cell stp;
  int flags;
  long usertags[AMX_USERNUM];
  void _FAR *userdata[AMX_USERNUM];
  int error;
  int paramcount;
  cell pri;
  cell alt;
  cell reset_stk;
  cell reset_hea;
  cell sysreq_d;
#if defined __GNUC__ || defined __ICC || defined __POCC__
} __attribute__((packed)) AMX;
#else
  #if defined _MSC_VER
    #pragma pack(1)
  #endif
} AMX;
#endif

int AMXAPI amx_Allot(AMX *amx, int cells, cell *amx_addr, cell **phys_addr);
int AMXAPI amx_Exec(AMX *amx, cell *retval, int index);
int AMXAPI amx_Flags(AMX *amx,uint16_t *flags);
int AMXAPI amx_GetAddr(AMX *amx,cell amx_addr,cell **phys_addr);
int AMXAPI amx_GetString(char *dest,const cell *source, int use_wchar, size_t size);
int AMXAPI amx_SetString(cell *dest, const char *source, int pack, int use_wchar, size_t size);
int AMXAPI amx_StrLen(const cell *cstring, int *length);
int AMXAPI amx_Register(AMX *amx, const AMX_NATIVE_INFO *nativelist, int number);

// Float conversion macros
#define amx_ftoc(f)   ( * ((cell*)&f) )   /* float to cell */
#define amx_ctof(c)   ( * ((float*)&c) )  /* cell to float */

#if defined __cplusplus
}
#endif

#endif /* AMX_H_INCLUDED */
