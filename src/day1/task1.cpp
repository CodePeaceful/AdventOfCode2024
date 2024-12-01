#include <iostream>
#include <algorithm>
#include <ranges>
#include <numeric>

#include "..\utility.hpp"

int solve(std::vector<std::string>);

int main() {
    std::cout << solve(load()) << '\n';
}

int solve(std::vector<std::string> data) {
    std::vector<int> list1;
    std::vector<int> list2;
    for (auto& line : data) {
        auto content = split(line, ' ');
        list1.push_back(std::stoi(content.front()));
        list2.push_back(std::stoi(content.back()));
    }
    std::sort(list1.begin(), list1.end());
    std::sort(list2.begin(), list2.end());
    auto zip = std::views::zip(list1, list2);
    return std::accumulate(zip.begin(), zip.end(), 0, [] (int in, auto pair) {
        auto [x, y] = pair;
        return in + std::abs(x - y);
        });
}
