#include <iostream>
#include <ranges>
#include <set>

#include "..\utility.hpp"

unsigned long long solve(std::vector<std::string>);
int getDigtes(unsigned long long num);
void blink(std::vector<unsigned long long>& stones);

int main() {
    std::cout << solve(load()) << '\n';
}

unsigned long long solve(std::vector<std::string> data) {
    std::vector<unsigned long long> stones = split(data.front(), ' ')
        | std::views::transform([] (std::string s) {return std::stoll(s);})
        | std::ranges::to<std::vector<unsigned long long>>();
    for (int i = 0; i < 45; ++i) {
        std::cout << i << '\n';
        blink(stones);
    }
    std::cout << "got to sort now:\t" << stones.size() << " stones\n";
    std::sort(stones.begin(), stones.end());
    unsigned long long sum;
    for (int l = 0; l < stones.size(); ++l) {
        std::cout << l << '\t' << stones[l] << '\n';
        unsigned long long count = 1;
        unsigned long long num = stones[l];
        while (num == stones[l + 1]) {
            ++count;
            ++l;
        }
        std::vector<unsigned long long> someStones { num };
        for (int i = 0; i < 30; ++i) {
            blink(someStones);
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

void blink(std::vector<unsigned long long>& stones) {
    int end = stones.size();
    for (int j = 0; j < end; ++j) {
        if (stones[j] == 0) {
            stones[j] = 1;
        }
        else if (int digtes = getDigtes(stones[j]); digtes % 2 == 0) {
            unsigned long long mul = 1;
            for (int k = 0; k < digtes / 2; ++k) {
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
