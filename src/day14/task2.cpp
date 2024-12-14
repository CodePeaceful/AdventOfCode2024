#include <iostream>
#include <array>
#include <windows.h>

#include "Robot.hpp"
#include "..\utility.hpp"

int solve(std::vector<std::string>);

int main() {
    std::cout << solve(load()) << '\n';
}

int solve(std::vector<std::string> data) {
    std::vector<Robot> r;
    for (const auto& line : data) {
        auto s = split(line, ' ');
        auto p = split(split(s[0], '=')[1], ',');
        auto v = split(split(s[1], '=')[1], ',');
        r.emplace_back(std::stoi(p[0]), std::stoi(p[1]), std::stoi(v[0]), std::stoi(v[1]));
    }
    std::array<std::array<char, 103>, 101> field;
    int i = 0;
    while (true) {
        for (auto& line : field) {
            for (auto& c : line) {
                c = ' ';
            }
        }
        for (auto& m : r) {
            field[m.getx()][m.gety()] = 'X';
            m.moveCycles(1);
        }
        for (auto& line : field) {
            for (auto c : line) {
                std::cout << c;
            }
            std::cout << '\n';
        }
        std::cout << i << '\n';
        ++i;
        std::string _;
        std::cin >> _;
    }

    return 0;
}
