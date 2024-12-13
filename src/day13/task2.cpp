#include <iostream>
#include <numeric>

#include "ClawMachine.hpp"
#include "..\utility.hpp"

long long solve(std::vector<std::string>);

int main() {
    std::cout << solve(load()) << '\n';
}

long long solve(std::vector<std::string> data) {
    std::vector<ClawMachine> cms;
    for (long long i = 0; i < data.size(); i += 4) {
        auto A = split(split(data[i], ':')[1], ',');
        auto B = split(split(data[i + 1], ':')[1], ',');
        auto P = split(split(data[i + 2], ':')[1], ',');
        long long ax = std::stoi(split(A[0], '+')[1]);
        long long ay = std::stoi(split(A[1], '+')[1]);
        long long bx = std::stoi(split(B[0], '+')[1]);
        long long by = std::stoi(split(B[1], '+')[1]);
        long long px = std::stoi(split(P[0], '=')[1]) + 10000000000000;
        long long py = std::stoi(split(P[1], '=')[1]) + 10000000000000;
        cms.emplace_back(ax, ay, bx, by, px, py);
    }

    return std::accumulate(cms.begin(), cms.end(), 0ll, [] (long long i, ClawMachine c) {return i + c.requiredTokens();});
}
