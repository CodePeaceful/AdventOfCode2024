#include <iostream>
#include <ranges>

#include "CPU.hpp"
#include "..\utility.hpp"

int solve(std::vector<std::string>);

int main() {
    std::cout << solve(load()) << '\n';
}

int solve(std::vector<std::string> data) {

    auto B = std::stoi(split(data[1], ' ').back());
    auto C = std::stoi(split(data[2], ' ').back());
    std::vector<int> pr = split(split(data[4], ' ').back(), ',') | std::views::transform([] (std::string s) {return std::stoi(s);}) | std::ranges::to<std::vector<int>>();
    long long A = std::pow(3, pr.size());
    while (true) {
        CPU cpu(A, B, C, pr);

        while (cpu.step()) {}

        auto n = cpu.getOut();
        if (n.size() < pr.size()) {
            A *= 2;
            std::cout << "more\n";
        }
        else {
            A /= 2;
            break;
        }
    }
    while (true) {
        CPU cpu(A, B, C, pr);
        while (cpu.step2()) {}
        if (cpu.getOut() == pr) {
            return A;
        }
        else ++A;
    }



    return 0;
}
