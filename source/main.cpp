#include <map>
#include <string>
#include <cstring>

// SA:MP SDK includes
#include "amx/amx.h"
#include "plugincommon.h"

// self includes for the handler class
#include "handler.hpp"
#include "constants.hpp"

// self includes for the native functions (our plugin development)
#include "natives.hpp"

logprintf_t logprintf;

const AMX_NATIVE_INFO NATIVES[] = {
    {"INI_Open", Natives::Native_INI_Open},
    {"INI_Close", Natives::Native_INI_Close},
    {"INI_ReadString", Natives::Native_INI_ReadString},
    {"INI_ReadInt", Natives::Native_INI_ReadInt},
    {"INI_ReadFloat", Natives::Native_INI_ReadFloat},
    {"INI_WriteString", Natives::Native_INI_WriteString},
    {"INI_WriteInt", Natives::Native_INI_WriteInt},
    {"INI_WriteFloat", Natives::Native_INI_WriteFloat},
    {"INI_DeleteKey", Natives::Native_INI_DeleteKey},
    {"INI_DeleteSection", Natives::Native_INI_DeleteSection},
    {"INI_SectionExists", Natives::Native_INI_SectionExists},
    {"INI_KeyExists", Natives::Native_INI_KeyExists},
    {0, 0}};

PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports()
{
    return SUPPORTS_VERSION | SUPPORTS_AMX_NATIVES;
}

PLUGIN_EXPORT bool PLUGIN_CALL Load(void **ppData)
{
    logprintf = (logprintf_t)ppData[PLUGIN_DATA_LOGPRINTF];
    logprintf("[pawn-ini | Info] Plugin has been loaded successfully: %s", VERSION_SHORT);
    return true;
}

PLUGIN_EXPORT void PLUGIN_CALL Unload()
{
    logprintf("[pawn-ini | Info] Plugin has been unloaded");
}

PLUGIN_EXPORT int PLUGIN_CALL AmxLoad(AMX *amx)
{
    return amx_Register(amx, NATIVES, -1);
}

PLUGIN_EXPORT int PLUGIN_CALL AmxUnload(AMX *amx)
{
    return AMX_ERR_NONE;
}