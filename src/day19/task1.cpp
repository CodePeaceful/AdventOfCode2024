#include <iostream>
#include <ranges>
#include <unordered_map>

#include "..\utility.hpp"

int solve(std::vector<std::string>);
bool isSolvable(const std::vector<std::string>& types, const std::string& wish);
std::unordered_map<std::string, bool> memo;

int main() {
    std::cout << solve(load()) << '\n';
}

int solve(std::vector<std::string> data) {
    auto types = split(data.front(), ',') |
        std::views::transform([] (std::string s) {ltrim(s); return s;}) |
        std::ranges::to<std::vector<std::string>>();

    auto wishes = data | std::views::drop(2) | std::ranges::to<std::vector<std::string>>();

    return std::count_if(wishes.begin(), wishes.end(), [&types] (std::string& s) {return isSolvable(types, s);});
}

bool isSolvable(const std::vector<std::string>& types, const std::string& wish) {
    if (memo.contains(wish)) {
        return memo[wish];
    }
    auto options = types |
        std::views::filter([wish] (const std::string& s) {return wish.starts_with(s);});
    for (const auto& type : options) {
        if (type == wish) {
            std::cout << "done\n";
            memo[wish] = true;
            return true;
        }
        std::string subwish = wish.substr(type.size(), wish.size());
        if (isSolvable(types, subwish)) {
            memo[wish] = true;
            return true;
        }
    }
    memo[wish] = false;
    return false;
}
