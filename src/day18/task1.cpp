#include <iostream>
#include <array>

#include "..\utility.hpp"

int solve(std::vector<std::string>);
void fillDeadEnds(std::array<std::array<char, 73>, 73>& field);

int main() {
    std::cout << solve(load()) << '\n';
}

int solve(std::vector<std::string> data) {
    std::array<std::array<char, 73>, 73> field;
    for (int i = 0; i < field.size(); ++i) {
        for (int j = 0; j < field[i].size(); ++j) {
            if (i == 0 || j == 0 || i == 72 || j == 72) {
                field[i][j] = '#';
            }
            else {
                field[i][j] = '.';
            }
        }
    }
    for (int i = 0; i < 1024;++i) {
        auto pos = split(data[i], ',');
        field[std::stoi(pos[0]) + 1][std::stoi(pos[1]) + 1] = '#';
    }
    field[1][1] = 'S';
    field[71][71] = 'E';
    fillDeadEnds(field);
    for (const auto& line : field) {
        for (char c : line) {
            std::cout << c;
        }
        std::cout << '\n';
    }
    // solve this by hand
    return 0;
}



void fillDeadEnds(std::array<std::array<char, 73>, 73>& field) {
    bool changed = false;
    do {
        changed = false;
        for (int i = 0; i < field.size(); ++i) {
            for (int j = 0; j < field[i].size(); ++j) {
                if (field[i][j] == '.') {
                    int k = 0;
                    k += field[i + 1][j] == '#';
                    k += field[i - 1][j] == '#';
                    k += field[i][j + 1] == '#';
                    k += field[i][j - 1] == '#';
                    if (k == 3) {
                        changed = true;
                        field[i][j] = '#';
                    }
                }
            }
        }
    } while (changed);
}

