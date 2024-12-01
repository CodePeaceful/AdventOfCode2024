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
    return std::accumulate(list1.begin(), list1.end(), 0, [&list2] (int in, int listelem) -> int {
        return in + std::count(list2.begin(), list2.end(), listelem) * listelem;
        });
}
