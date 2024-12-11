#include <iostream>
#include <ranges>
#include <unordered_map>

#include "..\utility.hpp"

long long solve(std::vector<std::string>);
int getDigtes(long long num);
std::vector<long long> blink(long long stones);

int main() {
    std::cout << solve(load()) << '\n';
}

long long solve(std::vector<std::string> data) {
    std::vector<long long> stones = split(data.front(), ' ')
        | std::views::transform([] (std::string s) {return std::stoll(s);})
        | std::ranges::to<std::vector<long long>>();

    std::unordered_map<long long, long long> stonecounter;
    for (auto i : stones) {
        ++stonecounter[i];
    }
    for (int i = 0; i < 75; ++i) {
        std::unordered_map<long long, long long> tempStones;
        for (const auto& [stone, count] : stonecounter) {
            for (long long newStone : blink(stone)) {
                tempStones[newStone] += count;
            }
        }
        stonecounter = tempStones;
    }
    long long sum = 0;
    for (const auto& [stone, count] : stonecounter) {
        sum += count;
    }
    return sum;
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

std::vector<long long> blink(long long stone) {
    std::vector<long long> stones;
    if (stone == 0) {
        stones.push_back(1);
    }
    else if (int digtes = getDigtes(stone); digtes % 2 == 0) {
        long long mul = 1;
        for (int k = 0; k < digtes / 2; ++k) {
            mul *= 10;
        }
        stones.push_back(stone % mul);
        stones.push_back(stone / mul);
    }
    else {
        stones.push_back(stone * 2024);
    }
    return stones;
}
