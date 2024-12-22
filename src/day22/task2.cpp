#include <iostream>
#include <numeric>
#include <ranges>
#include <array>

#include "..\utility.hpp"

int solve(std::vector<std::string>);
std::vector<std::pair<int, int>> getSecret(long long number);
int getBananas(const std::vector<long long>& monkeys, const std::array<int, 4>& line);

int main() {
    std::cout << solve(load()) << '\n';
}

int solve(std::vector<std::string> data) {
    std::array<int, 4> bestLine;
    int bestValue = 0;
    auto monkeys = data | std::views::transform([] (std::string s) {return std::stoll(s);}) | std::ranges::to<std::vector<long long>>();
    for (int i = -9; i < 10; ++i) {
        for (int j = -9; j < 10; ++j) {
            for (int k = -9; k < 10; ++k) {
                for (int l = -9; l < 10; ++l) {
                    if (i + j < 10 && i + j > -10 && i + j + k <10 && i + j + k > -10 && i + j + k + l < 10 && i + j + k + l > -1 && j + k <10 && j + k > -10 && k + l<10 && k + l>-10 && j + k + l < 10 && j + k + l > -10) {
                        std::array testLine { i, j, k, l };
                        int bananas = getBananas(monkeys, testLine);
                        if (bestValue < bananas) {
                            bestValue = bananas;
                            bestLine = { i, j, k, l };
                        }
                    }
                }
            }
        }
    }
    return bestValue;
}

std::vector<std::pair<int, int>> getSecret(long long number) {
    std::vector<std::pair<int, int>> changes;
    for (int i = 0; i < 2000; ++i) {
        long long prev = number;
        long long temp = number * 64ll;
        number ^= temp;
        number %= 16777216;
        temp = number / 32ll;
        number ^= temp;
        number %= 16777216;
        temp = number * 2048ll;
        number ^= temp;
        number %= 16777216;
        changes.push_back({ number % 10 - prev % 10, number % 10 });
    }
    return changes;
}

int getBananas(const std::vector<long long>& monkeys, const std::array<int, 4>& line) {
    int bananas = 0;
    for (const auto& monkey : monkeys) {
        auto secret = getSecret(monkey);
        auto lineMatch = std::ranges::search(secret, line, [] (std::pair<int, int> p, int i) {return i == p.first;});
        if (lineMatch.end() != secret.end()) {
            bananas += lineMatch.back().second;
        }
    }
    std::cout << bananas << '\n';
    return bananas;
}
