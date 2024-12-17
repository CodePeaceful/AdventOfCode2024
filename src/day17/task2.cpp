#include <iostream>
#include <ranges>

#include "CPU.hpp"
#include "..\utility.hpp"

long long solve(std::vector<std::string>);

int main() {
    std::cout << solve(load()) << '\n';
}


long long solve(std::vector<std::string> data) {
    auto B = std::stoi(split(data[1], ' ').back());
    auto C = std::stoi(split(data[2], ' ').back());
    std::vector<int> pr = split(split(data[4], ' ').back(), ',') | std::views::transform([] (std::string s) {return std::stoi(s);}) | std::ranges::to<std::vector<int>>();
    std::vector<long long> As { 1, 2, 3, 4, 5, 6, 7 };
    for (int i = 0; i < pr.size();++i) {
        std::vector<long long> newAs;
        for (auto A : As) {
            CPU cpu(A, B, C, pr);
            while (cpu.step()) {}
            auto& cupO = cpu.getOut();
            if (cupO == pr) {
                for (const auto& i : cpu.getOut()) {
                    std::cout << i << ',';
                }
                std::cout << '\n';
                return A;
            }
            if (cupO.size() != i + 1) {
                throw std::exception();
            }
            auto prIt = pr.crbegin();
            auto cpuIt = cupO.crbegin();
            bool todo = true;
            for (int j = 0; j <= i; ++j) {
                if (*prIt != *cpuIt) {
                    todo = false;
                    break;
                }
                ++prIt;
                ++cpuIt;
            }
            if (todo && i < pr.size() - 1) {
                long long newA = 8 * A;
                newAs.push_back(newA);
                newAs.push_back(newA + 1);
                newAs.push_back(newA + 2);
                newAs.push_back(newA + 3);
                newAs.push_back(newA + 4);
                newAs.push_back(newA + 5);
                newAs.push_back(newA + 6);
                newAs.push_back(newA + 7);
            }
        }
        if (i < pr.size() - 1) {
            std::swap(As, newAs);
        }
    }
    return 0;
}
