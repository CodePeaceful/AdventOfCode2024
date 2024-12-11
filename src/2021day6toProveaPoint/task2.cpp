#include <iostream>
#include <array>
#include <numeric>
#include <chrono>

#include "..\utility.hpp"

long long solve(std::string);

int main() {
    std::cout << solve(load().front()) << '\n';
}

long long solve(std::string data) {
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    std::array<long long, 9> lanterfish { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    for (char c : data) {
        if (std::isdigit(c));
        ++lanterfish[c - '0'];
    }
    for (int i = 0; i < 256; ++i) {
        long long reproducing = lanterfish[0];
        for (int j = 0; j < 8; ++j) {
            lanterfish[j] = lanterfish[j + 1];
        }
        lanterfish[8] = reproducing;
        lanterfish[6] += reproducing;
    }
    long long sum = std::accumulate(lanterfish.begin(), lanterfish.end(), 0ll);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]\n";
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() << "[ns]\n";
    return sum;
}
