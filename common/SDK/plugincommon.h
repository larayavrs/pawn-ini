/*
 * SA:MP Plugin SDK
 */

#ifndef PLUGINCOMMON_H
#define PLUGINCOMMON_H

#define SAMP_PLUGIN_VERSION 0x0200

#ifdef __cplusplus
  #define PLUGIN_EXTERN_C extern "C"
#else
  #define PLUGIN_EXTERN_C 
#endif

#if defined(LINUX) || defined(FREEBSD) || defined(__FreeBSD__) || defined(__OpenBSD__)
  #define PLUGIN_CALL 
  #ifndef __GNUC__
    #define PLUGIN_EXPORT PLUGIN_EXTERN_C 
  #else
    #define PLUGIN_EXPORT PLUGIN_EXTERN_C __attribute__((visibility("default")))
  #endif
#elif defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
  #define PLUGIN_CALL __stdcall
  #define PLUGIN_EXPORT PLUGIN_EXTERN_C __declspec(dllexport)
#endif

enum SUPPORTS_FLAGS
{
  SUPPORTS_VERSION = SAMP_PLUGIN_VERSION,
  SUPPORTS_VERSION_MASK = 0xffff,
  SUPPORTS_AMX_NATIVES = 0x10000,
  SUPPORTS_PROCESS_TICK = 0x20000
};

enum PLUGIN_DATA_TYPE
{
  PLUGIN_DATA_LOGPRINTF = 0x00,
  PLUGIN_DATA_AMX_EXPORTS = 0x10,
  PLUGIN_DATA_CALLPUBLIC_FS = 0x11,
  PLUGIN_DATA_CALLPUBLIC_GM = 0x12,
};

typedef void (*logprintf_t)(char* format, ...);

#endif // PLUGINCOMMON_H
