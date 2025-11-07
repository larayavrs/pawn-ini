#include <map>
#include <string>
#include <cstring>

// SA:MP SDK includes
#include "../common/SDK/amx.h"
#include "../common/SDK/plugincommon.h"

// self includes for the handler class
#include "handler.hpp"

logprintf_t logprintf;

// so we storage the the INI file handles
std::map<int, Handler *> handlers; /** A map of file handles to Handler objects. */
int next_handle = 1;               /** The next available handle, incremented for each new handler. */

// TODO: do the rest of natives and AMX functions