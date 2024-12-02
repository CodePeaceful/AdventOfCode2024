#include <iostream>
#include <ranges>
#include <algorithm>

#include "..\utility.hpp"

int solve(std::vector<std::string>);

bool increase(std::vector<int>& level) {
    for (auto i = 0ull; i < level.size() - 1; ++i) {
        int difference = level[i + 1] - level[i];
        if (difference < 1 || difference>3) {
            return false;
        }
    }
    return true;
}

bool decrease(std::vector<int>& level) {
    for (auto i = 0ull; i < level.size() - 1; ++i) {
        int difference = level[i] - level[i + 1];
        if (difference < 1 || difference>3) {
            return false;
        }
    }
    return true;
}

int main() {
    std::cout << solve(load()) << '\n';
}

int solve(std::vector<std::string> data) {
    std::vector<std::vector<int>> levels;
    for (auto& line : data) {
        levels.emplace_back();
        for (auto& value : split(line, ' ')) {
            levels.back().push_back(std::stoi(value));
        }
    }


    return std::ranges::count_if(levels, [] (std::vector<int> level) {return (increase(level) || decrease(level));});
}
