#include <iostream>
#include <map>

#include "..\utility.hpp"

int solve(std::vector<std::string>);

std::map<char, std::pair<int, int>> keypad {
    { 'A', { 0, 0 } },
    { '0', { 1, 0 } },
    { '1', { 2, 1 } },
    { '2', { 1, 1 } },
    { '3', { 0, 1 } },
    { '4', { 2, 2 } },
    { '5', { 1, 2 } },
    { '6', { 0, 2 } },
    { '7', { 2, 3 } },
    { '8', { 1, 3 } },
    { '9', { 0, 3 } }
};

std::map<char, std::pair<int, int>> controler {
    { 'A', { 0, 0 } },
    { '^', { 1, 0 } },
    { '>', { 0, -1 } },
    { 'v', { 1, -1 } },
    { '<', { 2, -1 } }
};

int main() {
    std::cout << solve(load()) << '\n';
}

int solve(std::vector<std::string> data) {
    const int robotcount = 3;
    int cost = 0;
    for (auto input : data) {
        auto num = std::stoi(input.substr(0, input.size() - 1));
        char pos = 'A';
        auto out = input;
        input.clear();
        for (char c : out) {
            auto target = keypad[c];
            auto origin = keypad[pos];
            for (int i = target.second - origin.second; i < 0; ++i) {
                input += 'v';
            }
            for (int i = 0; i < target.second - origin.second; ++i) {
                input += '^';
            }
            for (int i = target.first - origin.first; i < 0; ++i) {
                input += '>';
            }
            for (int i = 0; i < target.first - origin.first; ++i) {
                input += '<';
            }
            input += 'A';
            pos = c;
        }
        for (int i = 1; i < robotcount; ++i) {
            pos = 'A';
            out = input;
            input.clear();
            for (char c : out) {
                auto target = controler[c];
                auto origin = controler[pos];
                for (int i = target.second - origin.second; i < 0; ++i) {
                    input += 'v';
                }
                for (int i = 0; i < target.second - origin.second; ++i) {
                    input += '^';
                }
                for (int i = target.first - origin.first; i < 0; ++i) {
                    input += '>';
                }
                for (int i = 0; i < target.first - origin.first; ++i) {
                    input += '<';
                }
                input += 'A';
                pos = c;
            }
        }
        cost += input.size() * num;
    }
    return cost;
}

