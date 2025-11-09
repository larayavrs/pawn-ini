/*
 * pawn-ini v0.1.0
 * 
 * Plugin for reading and writing INI files without scriptfiles restrictions
 * 
 * Features:
 * - Full filesystem access (not limited to scriptfiles)
 * - Support for absolute and relative paths
 * - Read/write functions for string, int and float
 * - Section and key management
 */

#if defined _pawn_ini_included
    #endinput
#endif
#define _pawn_ini_included

// Invalid handle
#define INVALID_INI_HANDLE (INI:0)

// Custom tag for handles
#define INI: INI_

/**
 * Opens or creates an INI file
 * 
 * @param path   File path (can be absolute or relative, not restricted to scriptfiles)
 * @return       File handle or INVALID_INI_HANDLE if fails
 * 
 * Examples:
 *   INI_Open("C:/config/server.ini")           // Windows - Absolute path
 *   INI_Open("/etc/samp/config.ini")           // Linux - Absolute path
 *   INI_Open("../configs/settings.ini")        // Relative path (parent folder)
 *   INI_Open("data/users.ini")                 // Relative path (subfolder)
 */
native INI:INI_Open(const path[]);

/**
 * Closes the handle and saves changes
 * 
 * @param handle    File handle
 * @return          1 on success, 0 on failure
 */
native INI_Close(INI:handle);

/**
 * Reads a string from the INI file
 * 
 * @param handle        File handle
 * @param section       Section name
 * @param key          Key name
 * @param dest         Buffer where the result will be stored
 * @param size         Maximum buffer size
 * @return             1 on success, 0 on failure
 */
native INI_ReadString(INI:handle, const section[], const key[], dest[], size = sizeof(dest));

/**
 * Reads an integer from the INI file
 * 
 * @param handle        File handle
 * @param section       Section name
 * @param key          Key name
 * @param defaultValue Default value if key doesn't exist
 * @return             Read value or defaultValue if not found
 */
native INI_ReadInt(INI:handle, const section[], const key[], defaultValue = 0);

/**
 * Reads a float from the INI file
 * 
 * @param handle        File handle
 * @param section       Section name
 * @param key          Key name
 * @param defaultValue Default value if key doesn't exist
 * @return             Read value or defaultValue if not found
 */
native Float:INI_ReadFloat(INI:handle, const section[], const key[], Float:defaultValue = 0.0);

/**
 * Writes a string to the INI file
 * 
 * @param handle    File handle
 * @param section   Section name
 * @param key       Key name
 * @param value     Value to write
 * @return          1 on success, 0 on failure
 */
native INI_WriteString(INI:handle, const section[], const key[], const value[]);

/**
 * Writes an integer to the INI file
 * 
 * @param handle    File handle
 * @param section   Section name
 * @param key       Key name
 * @param value     Value to write
 * @return          1 on success, 0 on failure
 */
native INI_WriteInt(INI:handle, const section[], const key[], value);

/**
 * Writes a float to the INI file
 * 
 * @param handle    File handle
 * @param section   Section name
 * @param key       Key name
 * @param value     Value to write
 * @return          1 on success, 0 on failure
 */
native INI_WriteFloat(INI:handle, const section[], const key[], Float:value);

/**
 * Deletes a key from the INI file
 * 
 * @param handle    File handle
 * @param section   Section name
 * @param key       Key name
 * @return          1 on success, 0 on failure
 */
native INI_DeleteKey(INI:handle, const section[], const key[]);

/**
 * Deletes an entire section from the INI file
 * 
 * @param handle    File handle
 * @param section   Section name
 * @return          1 on success, 0 on failure
 */
native INI_DeleteSection(INI:handle, const section[]);

/**
 * Checks if a section exists
 * 
 * @param handle    File handle
 * @param section   Section name
 * @return          1 if exists, 0 if not
 */
native INI_SectionExists(INI:handle, const section[]);

/**
 * Checks if a key exists within a section
 * 
 * @param handle    File handle
 * @param section   Section name
 * @param key       Key name
 * @return          1 if exists, 0 if not
 */
native INI_KeyExists(INI:handle, const section[], const key[]);