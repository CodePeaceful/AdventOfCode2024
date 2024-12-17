#include <iostream>
#include <ranges>
#include <algorithm>
#include <thread>
#include <map>

#include "..\utility.hpp"

int solve(std::vector<std::string>);
void recurciveSplitWalk(std::vector<std::string> field, int line, int collum, int direction, int value);
void fillThis(std::vector<std::string>& field, int line, int collum, int direction);
void fillThisDirection(int collum, int line, std::vector<std::string>& field);
void fillDeadEnds(std::vector<std::string>& data);
void printField(const std::vector<std::string>& data);

int bestEnd = 0x10000000;
std::map<std::pair<int, int>, int> crossings;

int main() {
    std::cout << solve(load()) << '\n';
}

int solve(std::vector<std::string> data) {

    fillDeadEnds(data);

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
        int cost = 1;
        if (curdir != dir) {
            cost += 1000;
        }
        recurciveSplitWalk(data, is, js, dir, cost);
    }
    return bestEnd;
}

void fillDeadEnds(std::vector<std::string>& data) {
    bool changed = false;
    do {
        changed = false;
        for (int i = 0; i < data.size(); ++i) {
            for (int j = 0; j < data[i].size(); ++j) {
                if (data[i][j] == '.') {
                    int k = 0;
                    k += data[i + 1][j] == '#';
                    k += data[i - 1][j] == '#';
                    k += data[i][j + 1] == '#';
                    k += data[i][j - 1] == '#';
                    if (k == 3) {
                        changed = true;
                        data[i][j] = '#';
                    }
                }
            }
        }
    } while (changed);
}

void printField(const std::vector<std::string>& data) {
    for (const auto& line : data) {
        std::cout << line << '\n';
    }
}

void recurciveSplitWalk(std::vector<std::string> field, int line, int column, int direction, int value) {
    ++value;
    std::vector<int> openings;
    field[line][column] = '#';
    fillThis(field, line, column, direction);
    //printField(field);
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
            if (value < bestEnd) {
                bestEnd = value;
            }
            std::cout << "goal\n";
            return;
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
        if (openings.front() != direction) {
            direction = openings.front();
            value += 1000;
        }
        if (crossings.contains({ line, column })) {
            if (crossings[{line, column}] < value) {
                std::cout << "mapcancel\n";
                return;
            }
            else if (crossings[{line, column}] > value + 1000) {
                crossings[{line, column}] = value + 1000;
            }
        }
        else {
            crossings[{line, column}] = value + 1000;
        }
        if (value >= bestEnd) {
            std::cout << "cancel\n";
            return;
        }
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
    fillDeadEnds(field);
    field[line][column] = '#';
    if (openings.size() == 0) {
        std::cout << line << ' ' << column << " dead\n";
        return;
    }

    std::vector<int> paths;

    for (int dir : openings) {
        int cost = value;
        if (direction != dir) {
            cost += 1000;
        }
        recurciveSplitWalk(field, line, column, dir, cost);
    }
}



void fillThis(std::vector<std::string>& field, int line, int collum, int direction) {
    if (direction != 0) {
        fillThisDirection(collum + 1, line, field);
    }
    if (direction != 1) {
        fillThisDirection(collum, line + 1, field);
    }
    if (direction != 2) {
        fillThisDirection(collum - 1, line, field);
    }
    if (direction != 3) {
        fillThisDirection(collum, line - 1, field);
    }
}

void fillThisDirection(int _column, int _line, std::vector<std::string>& field) {
    std::vector<int> openings;
    do {
        if (field[_line][_column] == '#') {
            return;
        }
        openings.clear();
        if (field[_line][_column + 1] == '.') {
            openings.push_back(0);
        }
        if (field[_line][_column - 1] == '.') {
            openings.push_back(2);
        }
        if (field[_line + 1][_column] == '.') {
            openings.push_back(1);
        }
        if (field[_line - 1][_column] == '.') {
            openings.push_back(3);
        }
        if (openings.size() <= 1) {
            field[_line][_column] = '#';
            if (openings.size() == 1) {
                switch (openings.front()) {
                case 0:
                    ++_column;
                    break;
                case 1:
                    ++_line;
                    break;
                case 2:
                    --_column;
                    break;
                case 3:
                    --_line;
                    break;
                }
            }
        }
    } while (openings.size() == 1);
}

