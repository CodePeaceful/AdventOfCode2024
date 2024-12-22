#include <iostream>
#include <numeric>
#include <ranges>

#include "..\utility.hpp"

long long solve(std::vector<std::string>);
long long getSecret(long long number, int iterations);

int main() {
    std::cout << solve(load()) << '\n';
}

long long solve(std::vector<std::string> data) {
    auto nums = data | std::views::transform([] (std::string s) {return getSecret(std::stoll(s), 2000);});
    return std::reduce(nums.begin(), nums.end(), 0ll);
}

long long getSecret(long long number, int iterations) {
    for (int i = 0; i < iterations; ++i) {
        long long temp = number * 64ll;
        number ^= temp;
        number %= 16777216;
        temp = number / 32ll;
        number ^= temp;
        number %= 16777216;
        temp = number * 2048ll;
        number ^= temp;
        number %= 16777216;
    }
    return number;
}
