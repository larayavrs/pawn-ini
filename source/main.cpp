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
    {"PawnINI_Open", Natives::Native_PawnINI_Open},
    {"PawnINI_Close", Natives::Native_PawnINI_Close},
    {"PawnINI_ReadString", Natives::Native_PawnINI_ReadString},
    {"PawnINI_ReadInt", Natives::Native_PawnINI_ReadInt},
    {"PawnINI_ReadFloat", Natives::Native_PawnINI_ReadFloat},
    {"PawnINI_WriteString", Natives::Native_PawnINI_WriteString},
    {"PawnINI_WriteInt", Natives::Native_PawnINI_WriteInt},
    {"PawnINI_WriteFloat", Natives::Native_PawnINI_WriteFloat},
    {"PawnINI_DeleteKey", Natives::Native_PawnINI_DeleteKey},
    {"PawnINI_DeleteSection", Natives::Native_PawnINI_DeleteSection},
    {"PawnINI_SectionExists", Natives::Native_PawnINI_SectionExists},
    {"PawnINI_KeyExists", Natives::Native_PawnINI_KeyExists},
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