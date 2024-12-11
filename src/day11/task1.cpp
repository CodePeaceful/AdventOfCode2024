#include <iostream>
#include <ranges>

#include "..\utility.hpp"

int solve(std::vector<std::string>);
int getDigtes(long long num);

int main() {
    std::cout << solve(load()) << '\n';
}

int solve(std::vector<std::string> data) {
    std::vector<long long> stones = split(data.front(), ' ')
        | std::views::transform([] (std::string s) {return std::stoll(s);})
        | std::ranges::to<std::vector<long long>>();
    for (int i = 0; i < 25; ++i) {
        int end = stones.size();
        for (int j = 0; j < end; ++j) {
            if (stones[j] == 0) {
                stones[j] = 1;
            }
            else if (int digtes = getDigtes(stones[j]); digtes % 2 == 0) {
                long long mul = 1;
                for (int k = 0; k < digtes / 2;++k) {
                    mul *= 10;
                }
                stones.push_back(stones[j] % mul);
                stones[j] /= mul;
            }
            else {
                stones[j] *= 2024;
            }
        }
    }
    return stones.size();
}

int getDigtes(long long num) {
    long long multiplier = 1;
    int digtes = 0;
    while (num >= multiplier) {
        multiplier *= 10;
        ++digtes;
    }
    return digtes;
}