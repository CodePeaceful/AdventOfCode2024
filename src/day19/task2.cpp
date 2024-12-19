#include <iostream>
#include <ranges>
#include <unordered_map>
#include <numeric>

#include "..\utility.hpp"

long long solve(std::vector<std::string>);
long long isSolvable(const std::vector<std::string>& types, const std::string& wish);
std::unordered_map<std::string, long long> memo;

int main() {
    std::cout << solve(load()) << '\n';
}

long long solve(std::vector<std::string> data) {
    auto types = split(data[0], ',') |
        std::views::transform([] (std::string s) {ltrim(s); return s;}) |
        std::ranges::to<std::vector<std::string>>();

    auto wishes = data | std::views::drop(2) | std::ranges::to<std::vector<std::string>>();

    return std::accumulate(wishes.begin(), wishes.end(), 0ll, [&types] (long long i, std::string& s) {return isSolvable(types, s) + i;});
}

long long isSolvable(const std::vector<std::string>& types, const std::string& wish) {
    if (memo.contains(wish)) {
        return memo[wish];
    }
    long long counter = 0;
    auto options = types |
        std::views::filter([wish] (const std::string& s) {return wish.starts_with(s);});
    for (const auto& type : options) {
        if (type == wish) {
            ++counter;
        }
        std::string subwish = wish.substr(type.size(), wish.size());
        counter += isSolvable(types, subwish);
    }
    memo[wish] = counter;
    return counter;
}
