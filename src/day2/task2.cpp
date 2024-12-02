#include <iostream>
#include <ranges>
#include <algorithm>

#include "..\utility.hpp"

int solve(std::vector<std::string>);

int main() {
    std::cout << solve(load()) << '\n';
}


bool increase2(std::vector<int>& level) {
    for (auto i = 0ull; i < level.size() - 1; ++i) {
        int difference = level[i + 1] - level[i];
        if (difference < 1 || difference>3) {
            return false;
        }
    }
    return true;
}

bool decrease2(std::vector<int>& level) {
    for (auto i = 0ull; i < level.size() - 1; ++i) {
        int difference = level[i] - level[i + 1];
        if (difference < 1 || difference>3) {
            return false;
        }
    }
    return true;
}

bool increase(std::vector<int>& level) {
    for (auto i = 0ull; i < level.size() - 1; ++i) {
        int difference = level[i + 1] - level[i];
        if (difference < 1 || difference>3) {
            auto vec1 = level;
            auto vec2 = level;
            auto vec3 = level;
            vec1.erase(vec1.begin() + i);
            vec2.erase(vec2.begin() + i + 1);
            if (i < 0)
                vec3.erase(vec3.begin() + i - 1);
            return increase2(vec1) || increase2(vec2) || increase2(vec3);
        }
    }
    return true;
}

bool decrease(std::vector<int>& level) {
    for (auto i = 0ull; i < level.size() - 1; ++i) {
        int difference = level[i] - level[i + 1];
        if (difference < 1 || difference>3) {
            auto vec1 = level;
            auto vec2 = level;
            auto vec3 = level;
            vec1.erase(vec1.begin() + i);
            vec2.erase(vec2.begin() + i + 1);
            if (i < 0)
                vec3.erase(vec3.begin() + i - 1);
            return decrease2(vec1) || decrease2(vec2) || decrease2(vec3);
        }
    }
    return true;
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
