#include <algorithm>
#include <sstream>
#include <cctype>

#include "handler.hpp"

Handler::Handler(const std::string &fpath) : file_path(fpath), valid(false), modified(false)
{
    load();
}

Handler::~Handler()
{
    if (modified)
        save();
}

void Handler::load()
{
    std::ifstream file(file_path);
    if (!file.is_open())
    {
        std::ofstream new_file(file_path);
        if (new_file.is_open())
        {
            valid = true;
            new_file.close();
        }
        return;
    }
    std::string line;
    std::string current_section;
    while (std::getline(file, line))
    {
        trim(line);
        // this is the case of a comment
        if (line.empty() || line[0] == ';' || line[0] == '#')
            continue;
        // this is the case of a new section
        if (line[0] == '[' && line[line.length() - 1] == ']')
        {
            current_section = line.substr(1, line.length() - 2);
            trim(current_section);
            continue;
        }
        // key=value
        size_t pos = line.find("=");
        if (pos != std::string::npos)
        {
            std::string key = line.substr(0, pos);
            std::string value = line.substr(pos + 1);
            trim(key);
            trim(value);
            if (!current_section.empty() && !key.empty())
                data[current_section][key] = value;
        }
    }
    file.close();
    valid = true;
}

bool Handler::save()
{
    std::ofstream file(file_path);
    if (!file.is_open())
        return false;
    for (const auto &section : data)
    {
        file << "[" << section.first << "]" << std::endl;
        for (const auto &pair : section.second)
            file << pair.first << "=" << pair.second << std::endl;
        file << std::endl;
    }
    file.close();
    modified = false;
    return true;
}

std::string Handler::read_string(const std::string &section, const std::string &key, const std::string &defval)
{
    if (!valid)
        return defval;
    // we need to find the section first
    auto section_it = data.find(section);
    if (section_it == data.end())
        return defval;
    // and now the key
    auto key_it = section_it->second.find(key);
    if (key_it == section_it->second.end())
        return defval;
    return key_it->second;
}

int Handler::read_int(const std::string &section, const std::string &key, int defval)
{
    std::string value = read_string(section, key, "");
    if (value.empty())
        return defval;
    try
    {
        return std::stoi(value);
    }
    catch (...)
    {
        return defval;
    }
}

float Handler::read_float(const std::string &section, const std::string &key, float defval)
{
    std::string value = read_string(section, key, "");
    if (value.empty())
        return defval;
    try
    {
        return std::stof(value);
    }
    catch (...)
    {
        return defval;
    }
}

bool Handler::write_string(const std::string &section, const std::string &key, const std::string &value)
{
    if (!valid)
        return false;
    data[section][key] = value;
    modified = true;
    return true;
}

bool Handler::write_int(const std::string &section, const std::string &key, int value)
{
    return write_string(section, key, std::to_string(value));
}

bool Handler::write_float(const std::string &section, const std::string &key, float value)
{
    return write_string(section, key, std::to_string(value));
}

bool Handler::delete_key(const std::string &section, const std::string &key)
{
    if (!valid)
        return false;
    auto section_it = data.find(section);
    if (section_it == data.end())
        return false;
    auto key_it = section_it->second.find(key);
    if (key_it == section_it->second.end())
        return false;
    section_it->second.erase(key_it);
    modified = true;
    return true;
}

bool Handler::delete_section(const std::string &section)
{
    if (!valid)
        return false;
    auto section_it = data.find(section);
    if (section_it == data.end())
        return false;
    data.erase(section_it);
    modified = true;
    return true;
}

bool Handler::section_exists(const std::string &section) const
{
    return data.find(section) != data.end();
}

bool Handler::key_exists(const std::string &section, const std::string &key) const
{
    auto section_it = data.find(section);
    if (section_it == data.end())
        return false;
    return section_it->second.find(key) != section_it->second.end();
}

void Handler::trim(std::string &s)
{
    // first left trim
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch)
                                    { return !std::isspace(ch); }));
    // then right trim
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch)
                         { return !std::isspace(ch); })
                .base(),
            s.end());
}

std::string Handler::to_lower(const std::string &s)
{
    std::string result = s;
    // we need to transform the string to lowercase for the comparison
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}