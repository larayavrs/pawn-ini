#ifndef NATIVES_HPP
#define NATIVES_HPP

#include "../common/SDK/amx.h"

/**
 * @file natives.hpp
 * @brief AMX native function declarations for INI file operations.
 *
 * @details
 * This header declares the C++ wrapper class Natives which exposes a set of
 * static functions that follow the AMX native calling convention (AMX_NATIVE_CALL).
 * These functions are intended to be registered as natives in the Pawn/AMX runtime
 * and provide basic INI file manipulation: opening/closing files, reading and writing
 * values (string/int/float), and checking/removing keys and sections.
 *
 * Each native receives the usual AMX parameters: an AMX pointer and a params array.
 * The exact parameter layout (number and meaning of params) is defined by the
 * corresponding implementation and should be documented in the runtime/native registration.
 *
 * The class is non-instantiable; all functions are static.
 */
class Natives
{
public:
    /**
     * @brief Open or create an INI file and return a handle (or error code).
     *
     * @param amx Pointer to the AMX instance.
     * @param params Pointer to the native call parameters (AMX convention).
     * @return AMX cell containing the file handle on success or a negative/error code.
     */
    static cell AMX_NATIVE_CALL Native_INI_Open(AMX *amx, cell *params);

    /**
     * @brief Close a previously opened INI handle.
     *
     * @param amx Pointer to the AMX instance.
     * @param params Pointer to the native call parameters. Expected to contain the handle.
     * @return AMX cell indicating success (non-zero) or failure (zero / error code).
     */
    static cell AMX_NATIVE_CALL Native_INI_Close(AMX *amx, cell *params);

    /**
     * @brief Read a string value from a section/key.
     *
     * @details Expected params typically include: file handle, section name, key name,
     *          a destination buffer and its length, and a default string.
     *
     * @param amx AMX instance pointer.
     * @param params AMX native parameters array.
     * @return Number of characters written to the buffer or an error code.
     */
    static cell AMX_NATIVE_CALL Native_INI_ReadString(AMX *amx, cell *params);

    /**
     * @brief Read an integer value from a section/key.
     *
     * @details Expected params typically include: file handle, section name, key name,
     *          and a default integer value.
     *
     * @param amx AMX instance pointer.
     * @param params AMX native parameters array.
     * @return The integer value read or the default on error.
     */
    static cell AMX_NATIVE_CALL Native_INI_ReadInt(AMX *amx, cell *params);

    /**
     * @brief Read a floating-point value from a section/key.
     *
     * @details Expected params typically include: file handle, section name, key name,
     *          and a default float value.
     *
     * @param amx AMX instance pointer.
     * @param params AMX native parameters array.
     * @return The float value read (as AMX cell) or the default on error.
     */
    static cell AMX_NATIVE_CALL Native_INI_ReadFloat(AMX *amx, cell *params);

    /**
     * @brief Write or update a string value under a section/key.
     *
     * @param amx AMX instance pointer.
     * @param params AMX native parameters array (expected: handle, section, key, value).
     * @return Non-zero on success, zero or negative on failure.
     */
    static cell AMX_NATIVE_CALL Native_INI_WriteString(AMX *amx, cell *params);

    /**
     * @brief Write or update an integer value under a section/key.
     *
     * @param amx AMX instance pointer.
     * @param params AMX native parameters array (expected: handle, section, key, integer).
     * @return Non-zero on success, zero or negative on failure.
     */
    static cell AMX_NATIVE_CALL Native_INI_WriteInt(AMX *amx, cell *params);

    /**
     * @brief Write or update a float value under a section/key.
     *
     * @param amx AMX instance pointer.
     * @param params AMX native parameters array (expected: handle, section, key, float).
     * @return Non-zero on success, zero or negative on failure.
     */
    static cell AMX_NATIVE_CALL Native_INI_WriteFloat(AMX *amx, cell *params);

    /**
     * @brief Delete a whole section from the INI.
     *
     * @param amx AMX instance pointer.
     * @param params AMX native parameters (expected: handle, section).
     * @return Non-zero if the section was removed, zero otherwise.
     */
    static cell AMX_NATIVE_CALL Native_INI_DeleteSection(AMX *amx, cell *params);

    /**
     * @brief Delete a specific key from a section.
     *
     * @param amx AMX instance pointer.
     * @param params AMX native parameters (expected: handle, section, key).
     * @return Non-zero if the key was removed, zero otherwise.
     */
    static cell AMX_NATIVE_CALL Native_INI_DeleteKey(AMX *amx, cell *params);

    /**
     * @brief Check whether a section exists in the INI.
     *
     * @param amx AMX instance pointer.
     * @param params AMX native parameters (expected: handle, section).
     * @return Non-zero if the section exists, zero otherwise.
     */
    static cell AMX_NATIVE_CALL Native_INI_SectionExists(AMX *amx, cell *params);

    /**
     * @brief Check whether a key exists within a section.
     *
     * @param amx AMX instance pointer.
     * @param params AMX native parameters (expected: handle, section, key).
     * @return Non-zero if the key exists, zero otherwise.
     */
    static cell AMX_NATIVE_CALL Native_INI_KeyExists(AMX *amx, cell *params);

private:
    /**
     * @brief Private constructor to prevent instantiation.
     *
     * @details All methods are static and the class is used only as a namespace.
     */
    Natives();

    /**
     * @brief Private destructor to prevent instantiation.
     */
    ~Natives();
};

#endif