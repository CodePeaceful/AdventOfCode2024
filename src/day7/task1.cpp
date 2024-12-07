#include <iostream>

#include "Eqation.hpp"
#include "..\utility.hpp"

unsigned long long solve(std::vector<std::string>);

int main() {
    std::cout << solve(load()) << '\n';
}

unsigned long long solve(std::vector<std::string> data) {
    unsigned long long result = 0;
    for (const auto& line : data) {
        Eqation e(line);
        if (e.isSolvable()) {
            result += e.getResult();
        }
    }
    return result;
}
