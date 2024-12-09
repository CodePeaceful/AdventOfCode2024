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

    compactDisc(disk);

    long long index = 0;
    long long sum = 0;
    for (long long val : disk) {
        if (val != -1)
            sum += (index * val);
        ++index;
    }
    return sum;
}

void compactDisc(std::vector<long long>& disk) {
    for (auto back = --disk.end(); back > disk.begin(); --back) {
        while (*back == -1) {
            --back;
        }
        long long backBlock = 0;
        long long backNumber = *back;
        while (*back == backNumber) {
            --back;
            ++backBlock;
        }
        ++back;
        auto front = disk.begin();
        for (long long gap = 0; front < back; ++front) {
            while (*front != -1) {
                ++front;
            }
            bool bigEnough = true;
            for (long long i = 0; i < backBlock; ++i) {
                if (*(front + i) != -1) {
                    bigEnough = false;
                }
            }
            if (bigEnough) {
                break;
            }
        }
        for (long long i = 0; i < backBlock && front < back; ++i) {
            std::swap(*(front + i), *(back + i));
        }
    }
}
