#include <iostream>
#include <map>
#include <cctype>

#include "..\utility.hpp"

int solve(std::vector<std::string>);
bool checkOrder(const std::vector<int>& order);
void fixOrder(std::vector<int>& order);

int main() {
    std::cout << solve(load()) << '\n';
}

std::vector<int> buildOrder(std::vector<std::string> textOrder) {
    std::vector<int> order;
    for (auto& page : textOrder) {
        order.push_back(std::stoi(page));
    }
    return order;
}

std::map<int, std::vector<int>> rules;

int solve(std::vector<std::string> data) {
    std::vector<std::vector<int>> orders;
    auto it = data.begin();
    for (; std::isalnum((*it)[0]); ++it) {
        auto rule = split(*it, '|');
        rules[std::stoi(rule[0])].push_back(std::stoi(rule[1]));
    }
    for (; it < data.end(); ++it) {
        if (!std::isalnum((*it)[0])) {
            continue;
        }
        auto order = split(*it, ',');
        orders.push_back(buildOrder(order));
    }
    int sum = 0;
    for (auto& order : orders) {
        if (!checkOrder(order)) {
            fixOrder(order);
            int index = (order.size() - 1) / 2;
            sum += order[index];
        }
    }
    return sum;
}

bool checkOrder(const std::vector<int>& order) {
    for (auto i = order.rbegin(); i < order.rend(); ++i) {
        auto rule = rules[*i];
        for (auto r : rule) {
            if (std::any_of(i, order.rend(), [r] (int i) {return i == r;})) {
                return false;
            }
        }
    }
    return true;
}

void fixOrder(std::vector<int>& order) {
    bool changed = false;
    do {
        changed = false;
        for (auto i = order.rbegin(); i < order.rend(); ++i) {
            auto rule = rules[*i];
            for (auto r : rule) {
                if (std::any_of(i, order.rend(), [r] (int i) {return i == r;})) {
                    auto toSwap = std::find(i, order.rend(), r);
                    std::swap(*toSwap, *i);
                    changed = true;
                }
            }
        }
    } while (changed);
}
