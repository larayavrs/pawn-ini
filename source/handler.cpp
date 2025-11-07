#include <algorithm>
#include <sstream>
#include <cctype>

#include "handler.h"

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