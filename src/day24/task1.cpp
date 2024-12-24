#include <iostream>
#include <functional>
#include <map>
#include <ranges>

#include "..\utility.hpp"

long long solve(std::vector<std::string>);

int main() {
    std::cout << solve(load()) << '\n';
}

long long solve(std::vector<std::string> data) {
    auto inputs = data | std::views::take_while([] (std::string s) {return s.size() > 1;});
    auto gates = data | std::views::drop_while([] (std::string s) {return s.size() > 1;}) | std::views::drop(1);
    std::map<std::string, bool> values;
    for (const auto& input : inputs) {
        auto parts = split(input, ':');
        values[parts[0]] = parts[1][1] == '1';
    }
    std::vector<std::tuple<std::string, std::string, std::string, std::function<bool(bool, bool)>>> funcs;
    for (const auto& func : gates) {
        auto parts = split(func, ' ');
        std::function<bool(bool, bool)> f;
        switch (parts[1][0]) {
        case 'X':
            f = [] (bool a, bool b) {return a ^ b;};
            break;
        case 'A':
            f = [] (bool a, bool b) {return a && b;};
            break;
        case 'O':
            f = [] (bool a, bool b) {return a || b;};
            break;
        }
        funcs.push_back(std::make_tuple(parts[0], parts[2], parts[4], f));
    }
    bool change = true;
    while (change) {
        change = false;
        for (const auto& func : funcs) {
            if (values.contains(std::get<2>(func))) {
                continue;
            }
            if (values.contains(std::get<0>(func)) && values.contains(std::get<1>(func))) {
                values[std::get<2>(func)] = std::get<3>(func)(values[std::get<1>(func)], values[std::get<0>(func)]);
                change = true;
            }
        }
    }
    auto zs = values
        | std::views::filter([] (std::pair<const std::string, bool> p) {return p.first[0] == 'z';})
        | std::views::transform([] (std::pair<const std::string, bool> p) {return p.second;})
        | std::ranges::to<std::vector<bool>>();
    long long result = 0;
    for (long long i = 0, j = 1; i < zs.size(); ++i, j *= 2) {
        if (zs[i]) {
            result += j;
        }
    }

    return result;
}
