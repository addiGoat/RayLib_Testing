#pragma once
#include <fstream>
#include <string>
#include <vector>

static std::vector<std::string> LoadTextFileLines(const std::string& path)
{
    std::vector<std::string> lines;
    std::ifstream file(path);

    if (!file.is_open())
    {
        lines.push_back("ERROR: Could not open rules file:");
        lines.push_back(path);
        lines.push_back("");
        lines.push_back("Make sure rules.txt is in the same folder as the .exe");
        return lines;
    }

    std::string line;
    while (std::getline(file, line))
    {
        // Optional: strip Windows CR if the file has \r\n line endings
        if (!line.empty() && line.back() == '\r')
            line.pop_back();

        lines.push_back(line);
    }

    if (lines.empty())
        lines.push_back("(rules file was empty)");

    return lines;
}
