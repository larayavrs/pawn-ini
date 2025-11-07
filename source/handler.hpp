#ifndef HANDLER_H
#define HANDLER_H

#include <string>
#include <iostream>
#include <fstream>
#include <map>

/**
 * @file handler.h
 * @brief Simple INI file handler interface.
 *
 * @details
 * The Handler class provides basic read/write access to INI-style files.
 * It keeps the file contents in memory as a map of sections to key/value maps:
 * data[section][key] = value.
 *
 * The class supports reading strings, integers and floats, writing values
 * (stored as strings), deleting keys/sections and persisting changes back
 * to the original file path via save().
 *
 * This header documents the public API and the main private helpers.
 *
 * @note This implementation does not guarantee thread-safety.
 */
class Handler
{
public:
    /**
     * @brief Construct a Handler and attempt to load the INI file at path.
     *
     * @param fpath Path to the INI file to load. If the file cannot be opened
     *              or parsed, is_valid() will return false.
     *
     * @details The constructor calls load() to populate the internal data map.
     *          No automatic saving is performed on destruction.
     */
    Handler(const std::string &fpath);

    /**
     * @brief Destructor.
     *
     * @details Does not automatically write changes to disk. Call save()
     *          explicitly to persist modifications before destruction.
     */
    ~Handler();

    /**
     * @brief Return whether the INI file was successfully loaded and is usable.
     *
     * @return true if the file was loaded and the internal structure is valid,
     *         false otherwise.
     */
    bool is_valid() const { return valid; }

    /**
     * @brief Read a string value from a section/key.
     *
     * @param section Section name (without square brackets).
     * @param key Key name inside the section.
     * @param defval Default value returned if the section or key does not exist.
     * @return The stored value as a string, or defval if not found.
     */
    std::string read_string(const std::string &section, const std::string &key, const std::string &defval = "");

    /**
     * @brief Read an integer value from a section/key.
     *
     * @param section Section name.
     * @param key Key name.
     * @param defval Default integer returned if the key is missing or conversion fails.
     * @return The integer value parsed from the stored string, or defval on error.
     *
     * @note Parsing follows standard stoi-like behavior; non-numeric content yields defval.
     */
    int read_int(const std::string &section, const std::string &key, int defval = 0);

    /**
     * @brief Read a floating-point value from a section/key.
     *
     * @param section Section name.
     * @param key Key name.
     * @param defval Default float returned if the key is missing or conversion fails.
     * @return The float value parsed from the stored string, or defval on error.
     */
    float read_float(const std::string &section, const std::string &key, float defval = 0.0f);

    /**
     * @brief Write or update a string value in memory.
     *
     * @param section Section name.
     * @param key Key name.
     * @param value Value to store (will be stored exactly as provided).
     * @return true if the in-memory data was changed, false if the stored value was identical.
     *
     * @note Call save() to persist changes to disk.
     */
    bool write_string(const std::string &section, const std::string &key, const std::string &value);

    /**
     * @brief Write or update an integer value in memory.
     *
     * @param section Section name.
     * @param key Key name.
     * @param value Integer value to store (converted to string).
     * @return true if the in-memory data was changed.
     */
    bool write_int(const std::string &section, const std::string &key, int value);

    /**
     * @brief Write or update a float value in memory.
     *
     * @param section Section name.
     * @param key Key name.
     * @param value Float value to store (converted to string).
     * @return true if the in-memory data was changed.
     */
    bool write_float(const std::string &section, const std::string &key, float value);

    /**
     * @brief Remove a key from a section in memory.
     *
     * @param section Section name.
     * @param key Key name to remove.
     * @return true if the key existed and was removed, false if the key was not present.
     *
     * @note Removing the last key does not automatically remove the section.
     */
    bool delete_key(const std::string &section, const std::string &key);

    /**
     * @brief Remove an entire section and all its keys from memory.
     *
     * @param section Section name to remove.
     * @return true if the section existed and was erased, false otherwise.
     */
    bool delete_section(const std::string &section);

    /**
     * @brief Check whether a section exists in memory.
     *
     * @param section Section name.
     * @return true if the section exists, false otherwise.
     */
    bool section_exists(const std::string &section) const;

    /**
     * @brief Check whether a key exists within a given section.
     *
     * @param section Section name.
     * @param key Key name.
     * @return true if the key exists inside the section, false otherwise.
     */
    bool key_exists(const std::string &section, const std::string &key) const;

    /**
     * @brief Persist in-memory changes back to the original file path.
     *
     * @return true if the file was written successfully, false on I/O error.
     *
     * @note This operation typically overwrites the original file. Ensure you
     *       have backups if needed.
     */
    bool save();

private:
    /**
     * @brief Path to the INI file used to load/save content.
     *
     * @details Stored during construction and used by save() to write the file.
     */
    std::string file_path;

    /**
     * @brief Flag indicating whether the INI file was successfully loaded.
     *
     * @details true if load() completed without critical errors. If false,
     *          other operations may be no-ops or return default values.
     */
    bool valid;

    /**
     * @brief Flag indicating whether in-memory data has been modified since load/save.
     *
     * @details When true, callers may want to call save() to persist changes.
     */
    bool modified;

    /**
     * @brief In-memory representation of the INI file:
     *        outer map -> section name, inner map -> key/value pairs.
     *
     * @note Values are stored as strings; conversion helpers are used for numeric reads/writes.
     */
    std::map<std::string, std::map<std::string, std::string>> data;

    /**
     * @brief Load the INI file referenced by file_path into data.
     *
     * @details Parses sections of the form [section] and lines of the form key=value.
     *          Empty lines and comments (if supported) are ignored.
     *          On parse error, valid may be set to false.
     */
    void load();

    /**
     * @brief Trim leading and trailing whitespace from a string (in-place).
     *
     * @param s String to trim.
     *
     * @details Removes space and tab characters at both ends. Implementations may
     *          also remove carriage return and newline characters.
     */
    void trim(std::string &s);

    /**
     * @brief Return a lowercase copy of the given string.
     *
     * @param s Input string.
     * @return Lowercased copy of s (ASCII-only).
     *
     * @note This helper is intended for simple case-insensitive comparisons of keys/sections.
     */
    std::string to_lower(const std::string &s);
};

#endif