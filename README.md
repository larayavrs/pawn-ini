# pawn-ini

A SA:MP plugin that allows manipulating `.ini` files from any location on the filesystem, **without scriptfiles restrictions**.

## Features

- Access INI files from any path (absolute or relative)
- No scriptfiles restrictions
- High performance (native C++ code)
- Cross-platform (Windows/Linux)
- Safe path and error handling
- Simple and easy-to-use API

## Installation

### Copy files

**Windows:**
```powershell
copy pawn-ini.dll plugins/
copy pawn-ini.inc pawno/include/
```

**Linux:**
```bash
cp pawn-ini.so plugins/
cp pawn-ini.inc pawno/include/
```

### Configure server.cfg

**Windows:**
```
plugins pawn-ini
```

**Linux:**
```
plugins pawn-ini.so
```

### Include in your gamemode

```pawn
#include <a_samp>
#include <pawn-ini>
// ...rest of your gamemode
```

## Usage

### Basic example

```pawn
public OnGameModeInit()
{
    // Open file from any location (no scriptfiles restriction)
    new INI:config = INI_Open("C:/config/server.ini");
    
    if(config != INVALID_INI_HANDLE)
    {
        // Write data
        INI_WriteString(config, "Server", "hostname", "My Server");
        INI_WriteInt(config, "Server", "maxplayers", 100);
        INI_WriteFloat(config, "World", "gravity", 0.008);
        
        // Read data
        new hostname[128];
        INI_ReadString(config, "Server", "hostname", hostname);
        printf("Hostname: %s", hostname);
        
        new maxplayers = INI_ReadInt(config, "Server", "maxplayers", 50);
        printf("Max Players: %d", maxplayers);
        
        // Close (saves automatically)
        INI_Close(config);
    }
    
    return 1;
}
```

### Path examples

```pawn
// Windows - Absolute path
INI_Open("C:/GameServers/SAMP/config.ini");

// Linux - Absolute path
INI_Open("/home/samp/server/config.ini");

// Relative path - Parent folder
INI_Open("../configs/settings.ini");

// Relative path - Subfolder
INI_Open("data/users.ini");
```

## 📋 Available Functions

##### `INI:INI_Open(const path[])`
Opens or creates an INI file.
- **Parameters:** `path` - File path (absolute or relative)
- **Returns:** File handle or `INVALID_INI_HANDLE` on failure

##### `INI_Close(INI:handle)`
Closes the file and saves changes.
- **Parameters:** `handle` - File handle
- **Returns:** 1 on success, 0 on failure

##### `INI_ReadString(INI:handle, const section[], const key[], dest[], size = sizeof(dest))`
Reads a string from the INI file.
- **Parameters:**
  - `handle` - File handle
  - `section` - Section name
  - `key` - Key name
  - `dest` - Destination buffer
  - `size` - Buffer size
- **Returns:** 1 on success, 0 on failure

##### `INI_ReadInt(INI:handle, const section[], const key[], defaultValue = 0)`
Reads an integer from the INI file.
- **Parameters:**
  - `handle` - File handle
  - `section` - Section name
  - `key` - Key name
  - `defaultValue` - Default value if key doesn't exist
- **Returns:** Read value or defaultValue

##### `Float:INI_ReadFloat(INI:handle, const section[], const key[], Float:defaultValue = 0.0)`
Reads a float from the INI file.

##### `INI_WriteString(INI:handle, const section[], const key[], const value[])`
Writes a string to the INI file.

##### `INI_WriteInt(INI:handle, const section[], const key[], value)`
Writes an integer to the INI file.

##### `INI_WriteFloat(INI:handle, const section[], const key[], Float:value)`
Writes a float to the INI file.

##### `INI_DeleteKey(INI:handle, const section[], const key[])`
Deletes a key from the INI file.

##### `INI_DeleteSection(INI:handle, const section[])`
Deletes an entire section from the INI file.

##### `INI_SectionExists(INI:handle, const section[])`
Checks if a section exists.

##### `INI_KeyExists(INI:handle, const section[], const key[])`
Checks if a key exists within a section.

## Building from Source

### Quick Start (Recommended)

Use the provided compilation scripts for easy building:

**Windows:**
```cmd
compile.bat
```

**Linux:**
```bash
chmod +x compile.sh
./compile.sh
```

**Options:**
- `compile.bat clean` - Clean build before compiling (Windows)
- `./compile.sh clean` - Clean build before compiling (Linux)
- `./compile.sh debug` - Build in Debug mode (Linux)

### Requirements

**Windows:**
- Visual Studio 2019 or newer (Community Edition works)
- CMake 3.10 or newer

**Linux:**
- GCC/G++ with 32-bit support
- CMake 3.10 or newer

### Manual Build

**Windows:**
```powershell
mkdir build
cd build
cmake .. -G "Visual Studio 17 2022"
cmake --build . --config Release
```

**Linux:**
```bash
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make
```

Compiled files will be in the `output/` directory.

## Important Notes
- The plugin allows full filesystem access - be careful with the paths you use
- Always close files with `INI_Close()` to save changes
- Changes are saved automatically when closing or when the handler is destroyed
- Compatible with Windows (32-bit) and Linux (32-bit)
- SA:MP servers are 32-bit applications, so the plugin must be compiled as 32-bit

## Contributing
Contributions are welcome! Please open an issue or pull request.