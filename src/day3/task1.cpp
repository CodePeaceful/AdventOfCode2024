#include <iostream>
#include <regex>

#include "..\utility.hpp"

int solve(std::vector<std::string>);
std::vector<std::string> match(const std::string& text, const std::regex& pattern);

int main() {
    std::cout << solve(load()) << '\n';
}

int solve(std::vector<std::string> data) {
    std::regex pattern("mul\\([0-9]{1,3},[0-9]{1,3}\\)");
    int sum = 0;
    for (auto& line : data) {
        auto matches = match(line, pattern);
        for (auto mul : matches) {
            auto step1 = split(mul, '(');
            auto step2 = split(step1[1], ')');
            auto step3 = split(step2[0], ',');
            sum += std::stoi(step3[0]) * std::stoi(step3[1]);
        }
    }
    return sum;
}

std::vector<std::string> match(const std::string& text, const std::regex& pattern) {
    std::vector<std::string> matches;
    std::sregex_iterator it(text.begin(), text.end(), pattern), it_end;
    for (; it != it_end; ++it) {
        const std::smatch& match = *it;
        matches.push_back(match.str());
    }
    return matches;
}
