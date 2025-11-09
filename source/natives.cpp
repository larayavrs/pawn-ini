#include <map>
#include <string>
#include <cstring>

#include "handler.hpp"
#include "natives.hpp"
#include "constants.hpp"

// so we storage the the INI file handles
std::map<int, Handler *> handlers; /** A map of file handles to Handler objects. */
int next_handle = 1;               /** The next available handle, incremented for each new handler. */

std::string GetStringFromAMX(AMX *amx, cell param)
{
    cell *addr = NULL;
    int len = 0;
    amx_GetAddr(amx, param, &addr);
    amx_StrLen(addr, &len);
    if (len > 0)
    {
        char *str = new char[len + 1];
        amx_GetString(str, addr, 0, len + 1);
        std::string result(str);
        delete[] str;
        return result;
    }
    return "";
}

void SetStringToAMX(AMX *amx, cell param, const std::string &str, int maxlen)
{
    cell *addr = NULL;
    amx_GetAddr(amx, param, &addr);
    amx_SetString(addr, str.c_str(), 0, 0, maxlen);
}

cell AMX_NATIVE_CALL Natives::Native_INI_Open(AMX *amx, cell *params)
{
    std::string path = GetStringFromAMX(amx, params[1]);
    if (path.empty())
    {
        logprintf("[pawn-ini | Error] Empty path provided for INI_Open");
        return 0;
    }
    Handler *handler = new Handler(path);
    if (!handler->is_valid())
    {
        logprintf("[path-ini | Error] Failed to open INI file at %s", path.c_str());
        delete handler;
        return 0;
    }
    int handle = next_handle++;
    handlers[handle] = handler;
    logprintf("[pawn-ini | Info] Opened INI file at %s with handle %d", path.c_str(), handle);
    return handle;
}

cell AMX_NATIVE_CALL Natives::Native_INI_Close(AMX *amx, cell *params)
{
    int handle = params[1];
    // TODO: check if handle is valid?
    auto it = handlers.find(handle);
    if (it == handlers.end())
    {
        logprintf("[pawn-ini | Error] Invalid handle %d provided for INI_Close", handle);
        return 0;
    }
    delete it->second;
    handlers.erase(it);
    return 1;
}

cell AMX_NATIVE_CALL Natives::Native_INI_ReadString(AMX *amx, cell *params)
{
    int handle = params[1];
    auto it = handlers.find(handle);
    if (it == handlers.end())
    {
        logprintf("[pawn-ini | Error] Invalid handle %d provided for INI_ReadString", handle);
        return 0;
    }
    std::string section = GetStringFromAMX(amx, params[2]);
    std::string key = GetStringFromAMX(amx, params[3]);
    int maxlen = params[5];
    std::string value = it->second->read_string(section, key, "");
    SetStringToAMX(amx, params[4], value, maxlen);
    return 1;
}

cell AMX_NATIVE_CALL Natives::Native_INI_ReadInt(AMX *amx, cell *params)
{
    int handle = params[1];
    auto it = handlers.find(handle);
    if (it == handlers.end())
    {
        logprintf("[pawn-ini | Error] Invalid handle %d provided for INI_ReadInt", handle);
        return 0;
    }
    std::string section = GetStringFromAMX(amx, params[2]);
    std::string key = GetStringFromAMX(amx, params[3]);
    int defval = params[4];
    return it->second->read_int(section, key, defval);
}

cell AMX_NATIVE_CALL Natives::Native_INI_ReadFloat(AMX *amx, cell *params)
{
    int handle = params[1];
    auto it = handlers.find(handle);
    if (it == handlers.end())
    {
        logprintf("[pawn-ini | Error] Invalid handle %d provided for INI_ReadFloat", handle);
        return 0;
    }
    std::string section = GetStringFromAMX(amx, params[2]);
    std::string key = GetStringFromAMX(amx, params[3]);
    float defval = amx_ctof(params[4]); // cell to float wow!
    float value = it->second->read_float(section, key, defval);
    return amx_ftoc(value);
}

cell AMX_NATIVE_CALL Natives::Native_INI_WriteString(AMX *amx, cell *params)
{
    int handle = params[1];
    auto it = handlers.find(handle);
    if (it == handlers.end())
    {
        logprintf("[pawn-ini | Error] Invalid handle %d provided for INI_WriteString", handle);
        return 0;
    }
    std::string section = GetStringFromAMX(amx, params[2]);
    std::string key = GetStringFromAMX(amx, params[3]);
    std::string value = GetStringFromAMX(amx, params[4]);
    return it->second->write_string(section, key, value) ? 1 : 0;
}