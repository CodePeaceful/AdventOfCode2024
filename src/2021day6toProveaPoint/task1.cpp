#include <iostream>
#include <array>
#include <ranges>
#include <numeric>

#include "..\utility.hpp"

long long solve(std::vector<std::string>);

int main() {
    std::cout << solve(load()) << '\n';
}

long long solve(std::vector<std::string> data) {
    std::array<long long, 9> lanterfish { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    for (char c : data.front()) {
        if (std::isdigit(c));
        ++lanterfish[c - '0'];
    }
    for (int i = 0; i < 80; ++i) {
        long long reproducing = lanterfish[0];
        for (int j = 0; j < 8; ++j) {
            lanterfish[j] = lanterfish[j + 1];
        }
        lanterfish[8] = reproducing;
        lanterfish[6] += reproducing;
    }
    return std::accumulate(lanterfish.begin(), lanterfish.end(), 0ll);
}
