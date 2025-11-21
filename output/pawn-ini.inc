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
#define INVALID_INI_HANDLE (PawnINIFile:0)

/**
 * Opens or creates an INI file
 * 
 * @param path   File path (can be absolute or relative, not restricted to scriptfiles)
 * @return       File handle or INVALID_INI_HANDLE if fails
 * 
 * Examples:
 *   PawnINI_Open("C:/config/server.ini")           // Windows - Absolute path
 *   PawnINI_Open("/etc/samp/config.ini")           // Linux - Absolute path
 *   PawnINI_Open("../configs/settings.ini")        // Relative path (parent folder)
 *   PawnINI_Open("data/users.ini")                 // Relative path (subfolder)
 */
native PawnINIFile:PawnINI_Open(const path[]);

/**
 * Closes the handle and saves changes
 * 
 * @param handle    File handle
 * @return          1 on success, 0 on failure
 */
native PawnINI_Close(PawnINIFile:handle);

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
native PawnINI_ReadString(PawnINIFile:handle, const section[], const key[], dest[], size = sizeof(dest));

/**
 * Reads an integer from the INI file
 * 
 * @param handle        File handle
 * @param section       Section name
 * @param key          Key name
 * @param defaultValue Default value if key doesn't exist
 * @return             Read value or defaultValue if not found
 */
native PawnINI_ReadInt(PawnINIFile:handle, const section[], const key[], defaultValue = 0);

/**
 * Reads a float from the INI file
 * 
 * @param handle        File handle
 * @param section       Section name
 * @param key          Key name
 * @param defaultValue Default value if key doesn't exist
 * @return             Read value or defaultValue if not found
 */
native Float:PawnINI_ReadFloat(PawnINIFile:handle, const section[], const key[], Float:defaultValue = 0.0);

/**
 * Writes a string to the INI file
 * 
 * @param handle    File handle
 * @param section   Section name
 * @param key       Key name
 * @param value     Value to write
 * @return          1 on success, 0 on failure
 */
native PawnINI_WriteString(PawnINIFile:handle, const section[], const key[], const value[]);

/**
 * Writes an integer to the INI file
 * 
 * @param handle    File handle
 * @param section   Section name
 * @param key       Key name
 * @param value     Value to write
 * @return          1 on success, 0 on failure
 */
native PawnINI_WriteInt(PawnINIFile:handle, const section[], const key[], value);

/**
 * Writes a float to the INI file
 * 
 * @param handle    File handle
 * @param section   Section name
 * @param key       Key name
 * @param value     Value to write
 * @return          1 on success, 0 on failure
 */
native PawnINI_WriteFloat(PawnINIFile:handle, const section[], const key[], Float:value);

/**
 * Deletes a key from the INI file
 * 
 * @param handle    File handle
 * @param section   Section name
 * @param key       Key name
 * @return          1 on success, 0 on failure
 */
native PawnINI_DeleteKey(PawnINIFile:handle, const section[], const key[]);

/**
 * Deletes an entire section from the INI file
 * 
 * @param handle    File handle
 * @param section   Section name
 * @return          1 on success, 0 on failure
 */
native PawnINI_DeleteSection(PawnINIFile:handle, const section[]);

/**
 * Checks if a section exists
 * 
 * @param handle    File handle
 * @param section   Section name
 * @return          1 if exists, 0 if not
 */
native PawnINI_SectionExists(PawnINIFile:handle, const section[]);

/**
 * Checks if a key exists within a section
 * 
 * @param handle    File handle
 * @param section   Section name
 * @param key       Key name
 * @return          1 if exists, 0 if not
 */
native PawnINI_KeyExists(PawnINIFile:handle, const section[], const key[]);
