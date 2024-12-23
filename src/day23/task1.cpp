#include <iostream>
#include <unordered_map>
#include <set>
#include <array>

#include "..\utility.hpp"

int solve(std::vector<std::string>);

int main() {
    std::cout << solve(load()) << '\n';
}

int solve(std::vector<std::string> data) {
    std::unordered_map<std::string, std::vector<std::string>> userConnections;
    for (const auto& line : data) {
        auto pcs = split(line, '-');
        userConnections[pcs[0]].push_back(pcs[1]);
        userConnections[pcs[1]].push_back(pcs[0]);
    }
    std::set<std::array<std::string, 3>> trios;
    for (const auto& [base, connections] : userConnections) {
        for (int i = 0; i < connections.size(); ++i) {
            for (int j = i + 1; j < connections.size(); ++j) {
                auto search = connections[j];
                if (std::any_of(userConnections[connections[i]].begin(), userConnections[connections[i]].end(),
                    [search] (std::string s) {return s == search;})) {
                    std::array trio { base, connections[i], search };
                    std::sort(trio.begin(), trio.end());
                    if (std::any_of(trio.begin(), trio.end(), [] (std::string s) {return s[0] == 't';}))
                        trios.insert(trio);
                }
            }
        }
    }
    return trios.size();
}
