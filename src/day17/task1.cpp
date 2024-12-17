#include <iostream>
#include <ranges>

#include "CPU.hpp"
#include "..\utility.hpp"

int solve(std::vector<std::string>);

int main() {
    std::cout << solve(load()) << '\n';
}

int solve(std::vector<std::string> data) {
    auto A = std::stoi(split(data[0], ' ').back());
    auto B = std::stoi(split(data[1], ' ').back());
    auto C = std::stoi(split(data[2], ' ').back());
    std::vector<int> pr = split(split(data[4], ' ').back(), ',') | std::views::transform([] (std::string s) {return std::stoi(s);}) | std::ranges::to<std::vector<int>>();
    CPU cpu(A, B, C, pr);

    while (cpu.step()) {}

    for (const auto& i : cpu.getOut()) {
        std::cout << i << ',';
    }
    std::cout << '\n';

    return 0;
}
