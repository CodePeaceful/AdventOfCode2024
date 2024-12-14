#include <iostream>
#include <array>

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
    std::array<int, 4> quad { 0, 0, 0, 0 };
    for (auto& i : r) {
        i.moveCycles(100);
        int q = i.getQuadrant();
        if (q != -1) {
            ++quad[q];
        }
    }
    return quad[0] * quad[1] * quad[2] * quad[3];
}
