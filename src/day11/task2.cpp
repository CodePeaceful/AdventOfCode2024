#include <iostream>
#include <ranges>
#include <set>

#include "..\utility.hpp"

unsigned long long solve(std::vector<std::string>);
int getDigtes(unsigned long long num);

int main() {
    std::cout << solve(load()) << '\n';
}

unsigned long long solve(std::vector<std::string> data) {
    std::vector<unsigned long long> stones = split(data.front(), ' ')
        | std::views::transform([] (std::string s) {return std::stoll(s);})
        | std::ranges::to<std::vector<unsigned long long>>();
    for (int i = 0; i < 45; ++i) {
        std::cout << i << '\n';
        int end = stones.size();
        for (int j = 0; j < end; ++j) {
            if (stones[j] == 0) {
                stones[j] = 1;
            }
            else if (int digtes = getDigtes(stones[j]); digtes % 2 == 0) {
                unsigned long long mul = 1;
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
    std::cout << "got to sort now" << '\n';
    std::sort(stones.begin(), stones.end());
    unsigned long long sum;
    for (int l = 0; l < stones.size(); ++l) {
        std::cout << l << '\n';
        unsigned long long count = 1;
        unsigned long long num = stones[l];
        while (num == stones[l + 1]) {
            ++count;
            ++l;
        }
        std::vector<unsigned long long> someStones { num };
        for (int i = 0; i < 30; ++i) {

            int end = someStones.size();
            for (int j = 0; j < end; ++j) {
                if (someStones[j] == 0) {
                    someStones[j] = 1;
                }
                else if (int digtes = getDigtes(someStones[j]); digtes % 2 == 0) {
                    unsigned long long mul = 1;
                    for (int k = 0; k < digtes / 2;++k) {
                        mul *= 10;
                    }
                    someStones.push_back(someStones[j] % mul);
                    someStones[j] /= mul;
                }
                else {
                    someStones[j] *= 2024;
                }
            }
        }
        sum += (someStones.size() * count);
    }
    return sum;
}

int getDigtes(unsigned long long num) {
    long long multiplier = 1;
    int digtes = 0;
    while (num >= multiplier) {
        multiplier *= 10;
        ++digtes;
    }
    return digtes;
}