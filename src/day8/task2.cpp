#include <iostream>
#include <map>
#include <set>

#include "Vec2d.hpp"
#include "..\utility.hpp"

int solve(std::vector<std::string>);

int main() {
    std::cout << solve(load()) << '\n';
}

int solve(std::vector<std::string> data) {
    std::map<char, std::vector<Vec2d>> antenas;
    int height = data.size();
    int width = data.front().size();
    for (int top = 0; top < height; ++top) {
        for (int left = 0; left < width; ++left) {
            if (std::isalnum(data[top][left])) {
                antenas[data[top][left]].push_back(Vec2d(top, left));
            }
        }
    }
    std::set<Vec2d> antinodes;
    for (const auto& node : antenas) {
        const auto& vec = node.second;
        for (int i = 0; i < vec.size(); ++i) {
            if (vec.size() > 1)
                antinodes.insert(vec[i]);
            for (int j = i + 1; j < vec.size(); j++) {
                Vec2d difference = vec[i].dif(vec[j]);
                difference.setSmalestCommon(); //not needed be task design
                Vec2d anti1 = vec[i].add(difference);
                Vec2d anti2 = vec[j].subtract(difference);
                Vec2d anti3 = vec[i].subtract(difference);
                while (anti3 != vec[j]) { //not needed be task design
                    antinodes.insert(anti3);
                    anti3 = anti3.subtract(difference);
                }
                while (anti1.inBound(height, width)) {
                    antinodes.insert(anti1);
                    anti1 = anti1.add(difference);
                }
                while (anti2.inBound(height, width)) {
                    antinodes.insert(anti2);
                    anti2 = anti2.subtract(difference);
                }
            }
        }
    }
    return antinodes.size();
}
