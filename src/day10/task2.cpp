#include <iostream>
#include <ranges>
#include <set>

#include "..\utility.hpp"

int solve(std::vector<std::string>);
int calculateRoutes(const std::vector<std::vector<int>>& map, int i, int j);

int main() {
    std::cout << solve(load()) << '\n';
}

int solve(std::vector<std::string> data) {
    std::vector<std::vector<int>> map;
    for (const auto& s : data) {
        map.push_back(s | std::views::transform([] (char c) -> int {return c - '0';}) | std::ranges::to<std::vector<int>>());
    }
    int sum = 0;
    for (int i = 0; i < map.size(); ++i) {
        for (int j = 0; j < map.front().size(); ++j) {
            if (map[i][j] == 0) {
                sum += calculateRoutes(map, i, j);
            }
        }
    }
    return sum;
}

int calculateRoutes(const std::vector<std::vector<int>>& map, int i, int j) {
    int ilimit = map.size();
    int jlimit = map.front().size();
    std::vector<std::pair<int, int>> thisStep;
    std::vector<std::pair<int, int>> nextStep;
    thisStep.push_back(std::pair(i, j));
    for (int k = 1; k < 10; ++k) {
        for (auto [top, left] : thisStep) {
            if (top - 1 >= 0 && map[top - 1][left] == k) {
                nextStep.push_back(std::pair(top - 1, left));
            }
            if (top + 1 < ilimit && map[top + 1][left] == k) {
                nextStep.push_back(std::pair(top + 1, left));
            }
            if (left - 1 >= 0 && map[top][left - 1] == k) {
                nextStep.push_back(std::pair(top, left - 1));
            }
            if (left + 1 < jlimit && map[top][left + 1] == k) {
                nextStep.push_back(std::pair(top, left + 1));
            }
        }
        thisStep = nextStep;
        nextStep.clear();
    }
    return thisStep.size();
}
