#include <SFML/Graphics.hpp>

#include <iostream>

#include "Robot.hpp"
#include "../utility.hpp"

int solve(std::vector<std::string>);

int main() {
    std::cout << solve(load()) << '\n';
}

int solve(std::vector<std::string> data) {
    std::vector<Robot> r;
    for (const auto& line : data) {
        auto s = split(line, ' ');
        auto p = split(split(s[0], '=')[1], ',');
        auto v = split(split(s[1], '=')[1], ',');
        r.emplace_back(std::stoi(p[0]), std::stoi(p[1]), std::stoi(v[0]), std::stoi(v[1]));
    }

    int i = 0;
    while (i < 10000) {
        sf::Image im;
        im.create(101, 103);
        for (auto& t : r) {
            im.setPixel(t.getx(), t.gety(), sf::Color(255, 255, 255));
            t.moveCycles(1);
        }
        im.saveToFile("pics\\cycle" + std::to_string(i) + ".png");
        ++i;
    }

    return 0;
}
