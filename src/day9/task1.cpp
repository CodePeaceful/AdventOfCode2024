#include <iostream>
#include <ranges>

#include "..\utility.hpp"

long long solve(std::vector<std::string>);

void compactDisc(std::vector<long long>& disk);

int main() {
    std::cout << solve(load()) << '\n';
}

long long solve(std::vector<std::string> data) {
    std::vector<long long> inputAsInts;
    for (char c : data.front()) {
        inputAsInts.push_back(c - '0');
    }
    std::vector<long long> disk;
    for (long long i = 0, j = 0; i < inputAsInts.size(); ++i) {
        if (i % 2) {
            for (long long k = 0; k < inputAsInts[i];++k) {
                disk.push_back(-1);
            }
        }
        else {
            for (long long k = 0; k < inputAsInts[i];++k) {
                disk.push_back(j);
            }
            ++j;
        }
    }
    auto front = disk.begin();
    auto back = --disk.end();
    while (front < back) {
        while (*front != -1) {
            ++front;
        }
        while (*back == -1) {
            --back;
        }
        if (front < back) {
            std::swap(*front, *back);
        }
    }
    long long index = 0;
    long long sum = 0;
    for (long long val : disk | std::views::take_while([] (long long i) {return i != -1;})) {
        sum += (index * val);
        ++index;
    }
    return sum;
}
