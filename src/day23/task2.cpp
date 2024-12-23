#include <iostream>
#include <map>

#include "..\utility.hpp"

int solve(std::vector<std::string>);
std::vector<std::vector<std::string>> getSubsets(const std::vector<std::string>& set, int subsetSize);
void fillSubsetlist(std::vector<std::vector<std::string>>& subsets, std::vector<std::string> set, std::vector<std::string> subset, int totake);


int main() {
    std::cout << solve(load()) << '\n';
}

int solve(std::vector<std::string> data) {
    std::map<std::string, std::vector<std::string>> userConnections;
    for (const auto& line : data) {
        auto pcs = split(line, '-');
        userConnections[pcs[0]].push_back(pcs[1]);
        userConnections[pcs[1]].push_back(pcs[0]);
    }
    int maxLocalConnections = 0;
    for (auto& [_, con] : userConnections) {
        std::sort(con.begin(), con.end());
        if (con.size() > maxLocalConnections) {
            maxLocalConnections = con.size();
        }
    }
    for (int i = maxLocalConnections - 1; i > 3; --i) {
        for (const auto& [base, connections] : userConnections) {
            auto subsets = getSubsets(connections, i);
            for (const auto& set : subsets) {
                if (std::all_of(set.begin(), set.end(),
                    [&userConnections, &set] (std::string s) {
                        for (const auto& test : set) {
                            if (s != test && std::find(userConnections[s].begin(), userConnections[s].end(), test) == userConnections[s].end()) {
                                return false;
                            }
                        }
                        return true;
                    })) {
                    auto result = set;
                    result.push_back(base);
                    std::sort(result.begin(), result.end());
                    for (const auto& s : result) {
                        std::cout << s << ',';
                    }
                    std::cout << '\n';
                    return 0;
                }
            }
        }
    }
    return userConnections.size();
}

std::vector<std::vector<std::string>> getSubsets(const std::vector<std::string>& set, int subsetSize) {
    if (set.size() <= subsetSize) {
        return { set };
    }
    std::vector<std::vector<std::string>> subsets;
    fillSubsetlist(subsets, set, {}, subsetSize);
    return subsets;
}

void fillSubsetlist(std::vector<std::vector<std::string>>& subsets, std::vector<std::string> set, std::vector<std::string> subset, int totake) {
    if (totake == 0) {
        subsets.push_back(subset);
        return;
    }
    if (set.size() == totake) {
        for (const auto& s : set) {
            subset.push_back(s);
        }
        subsets.push_back(subset);
        return;
    }
    std::vector<std::string> newset { set.begin() + 1, set.end() };
    fillSubsetlist(subsets, newset, subset, totake);
    subset.push_back(set.front());
    fillSubsetlist(subsets, newset, subset, totake - 1);
}

