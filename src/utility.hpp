#pragma once
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

std::vector<std::string> split(const std::string& line, char seperator) {
    std::vector<std::string> splitString;
    std::string stringPart;
    std::stringstream input(line);
    while (std::getline(input, stringPart, seperator)) {
        if (stringPart != "") {
            splitString.push_back(stringPart);
        }
    }
    return splitString;
}

std::vector<std::string> load() {
    std::ifstream in("data.txt");
    std::vector<std::string> data;
    std::string line;
    while (std::getline(in, line)) {
        data.push_back(line);
    }
    return data;
}

inline void ltrim(std::string& s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [] (unsigned char ch) {
        return !std::isspace(ch);
        }));
}

inline void rtrim(std::string& s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [] (unsigned char ch) {
        return !std::isspace(ch);
        }).base(), s.end());
}

int findIndex(std::vector<int>& v, int val) {
    for (int i = 0; i < v.size(); ++i) {

          // When the element is found
        if (v[i] == val) {
            return i;
        }
    }

      // When the element is not found
    return -1;
}