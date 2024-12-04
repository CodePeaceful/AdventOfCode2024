#include <iostream>
#include <regex>

#include "..\utility.hpp"

int solve(std::vector<std::string>);
std::vector<std::string> match(const std::string& text, const std::regex& pattern);

int main() {
    std::cout << solve(load()) << '\n';
}

int solve(std::vector<std::string> data) {
    int counter = 0;
    const int lineLength = data[0].size();
    //forewards
    std::regex patern("XMAS");
    for (auto& line : data) {
        counter += match(line, patern).size();
    }
    //backwards
    patern = std::regex("SAMX");
    for (auto& line : data) {
        counter += match(line, patern).size();
    }
    //down
    for (auto i = 0ull; i < data.size() - 3; ++i) {
        int linepos = -1;
        do {
            linepos = data[i].find("X", linepos + 1);
            if (linepos != -1 && data[i + 1][linepos] == 'M' && data[i + 2][linepos] == 'A' && data[i + 3][linepos] == 'S') {
                ++counter;
            }
        } while (linepos != -1);
    }
    //up
    for (auto i = 0ull; i < data.size() - 3; ++i) {
        int linepos = -1;
        do {
            linepos = data[i].find("S", linepos + 1);
            if (linepos != -1 && data[i + 1][linepos] == 'A' && data[i + 2][linepos] == 'M' && data[i + 3][linepos] == 'X') {
                ++counter;
            }
        } while (linepos != -1);
    }
    //downright
    for (auto i = 0ull; i < data.size() - 3; ++i) {
        int linepos = -1;
        do {
            linepos = data[i].find("X", linepos + 1);
            if (linepos != -1 && linepos < lineLength - 3 && data[i + 1][linepos + 1] == 'M' && data[i + 2][linepos + 2] == 'A' && data[i + 3][linepos + 3] == 'S') {
                ++counter;
            }
        } while (linepos != -1);
    }
    //upleft
    for (auto i = 0ull; i < data.size() - 3; ++i) {
        int linepos = -1;
        do {
            linepos = data[i].find("S", linepos + 1);
            if (linepos != -1 && linepos < lineLength - 3 && data[i + 1][linepos + 1] == 'A' && data[i + 2][linepos + 2] == 'M' && data[i + 3][linepos + 3] == 'X') {
                ++counter;
            }
        } while (linepos != -1);
    }
    //downleft
    for (auto i = 0ull; i < data.size() - 3; ++i) {
        int linepos = -1;
        do {
            linepos = data[i].find("X", linepos + 1);
            if (linepos != -1 && linepos >= 3 && data[i + 1][linepos - 1] == 'M' && data[i + 2][linepos - 2] == 'A' && data[i + 3][linepos - 3] == 'S') {
                ++counter;
            }
        } while (linepos != -1);
    }
    //upright
    for (auto i = 0ull; i < data.size() - 3; ++i) {
        int linepos = -1;
        do {
            linepos = data[i].find("S", linepos + 1);
            if (linepos != -1 && linepos >= 3 && data[i + 1][linepos - 1] == 'A' && data[i + 2][linepos - 2] == 'M' && data[i + 3][linepos - 3] == 'X') {
                ++counter;
            }
        } while (linepos != -1);
    }
    return counter;
}

std::vector<std::string> match(const std::string& text, const std::regex& pattern) {
    std::vector<std::string> matches;
    std::sregex_iterator it(text.begin(), text.end(), pattern), it_end;
    for (; it != it_end; ++it) {
        const std::smatch& match = *it;
        matches.push_back(match.str());
    }
    return matches;
}
