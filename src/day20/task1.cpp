#include <iostream>

#include "..\utility.hpp"

int solve(std::vector<std::string>);
int recurciveSplitWalk(std::vector<std::string> field, int line, int column, int direction, int value);
int cheat(std::vector<std::string> field, int line, int column);

int main() {
    std::cout << solve(load()) << '\n';
}

int solve(std::vector<std::string> data) {
    int is;
    int js;
    for (int i = 0; i < data.size(); ++i) {
        for (int j = 0; j < data[i].size(); ++j) {
            if (data[i][j] == 'S') {
                is = i;
                js = j;
                i = data.size();
                break;
            }
        }
    }

    int curdir = 0;
    std::vector<int> openings;
    if (data[is][js + 1] == '.') {
        openings.push_back(0);
    }
    if (data[is][js - 1] == '.') {
        openings.push_back(2);
    }
    if (data[is + 1][js] == '.') {
        openings.push_back(1);
    }
    if (data[is - 1][js] == '.') {
        openings.push_back(3);
    }
    std::vector<int> paths;
    for (int dir : openings) {
        paths.push_back(recurciveSplitWalk(data, is, js, dir, 1));
    }
    int baseline = *std::min_element(paths.begin(), paths.end());
    int counter = 0;
    for (int i = 1; i < data.size() - 1; ++i) {
        for (int j = 1; j < data.front().size() - 1; ++j) {
            if (data[i][j] == '#') {
                if (baseline - cheat(data, i, j) >= 100) {
                    ++counter;
                }
            }
        }
    }
    return counter;
}

int cheat(std::vector<std::string> data, int line, int column) {
    data[line][column] = '.';
    int is;
    int js;
    for (int i = 0; i < data.size(); ++i) {
        for (int j = 0; j < data[i].size(); ++j) {
            if (data[i][j] == 'S') {
                is = i;
                js = j;
                i = data.size();
                break;
            }
        }
    }

    int curdir = 0;
    std::vector<int> openings;
    if (data[is][js + 1] == '.') {
        openings.push_back(0);
    }
    if (data[is][js - 1] == '.') {
        openings.push_back(2);
    }
    if (data[is + 1][js] == '.') {
        openings.push_back(1);
    }
    if (data[is - 1][js] == '.') {
        openings.push_back(3);
    }
    std::vector<int> paths;
    for (int dir : openings) {
        paths.push_back(recurciveSplitWalk(data, is, js, dir, 1));
    }
    return *std::min_element(paths.begin(), paths.end());
}

int recurciveSplitWalk(std::vector<std::string> field, int line, int column, int direction, int value) {
    ++value;
    std::vector<int> openings;
    field[line][column] = '#';
    switch (direction) {
    case 0:
        ++column;
        break;
    case 1:
        ++line;
        break;
    case 2:
        --column;
        break;
    case 3:
        --line;
        break;
    default:
        throw std::exception();
    }
    while (true) {
        openings.clear();
        if (field[line][column + 1] == 'E' || field[line][column - 1] == 'E' || field[line + 1][column] == 'E' || field[line - 1][column] == 'E') {
            std::cout << "goal\n";
            return value;
        }
        field[line][column] = '#';
        if (field[line][column + 1] == '.') {
            openings.push_back(0);
        }
        if (field[line][column - 1] == '.') {
            openings.push_back(2);
        }
        if (field[line + 1][column] == '.') {
            openings.push_back(1);
        }
        if (field[line - 1][column] == '.') {
            openings.push_back(3);
        }
        if (openings.size() != 1) {
            break;
        }
        ++value;
        field[line][column] = '#';
        switch (openings.front()) {
        case 0:
            ++column;
            break;
        case 1:
            ++line;
            break;
        case 2:
            --column;
            break;
        case 3:
            --line;
            break;
        default:
            throw std::exception();
        }
    }
    field[line][column] = '.';
    field[line][column] = '#';
    if (openings.size() == 0) {
        std::cout << line << ' ' << column << " dead\n";
        return 0x10000000;
    }

    std::vector<int> paths;

    for (int dir : openings) {
        paths.push_back(recurciveSplitWalk(field, line, column, dir, value));
    }
    return *std::min_element(paths.begin(), paths.end());
}