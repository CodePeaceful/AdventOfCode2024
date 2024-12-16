#include <iostream>
#include <ranges>
#include <algorithm>
#include <thread>

#include "..\utility.hpp"

int solve(std::vector<std::string>);
int recurciveSplitWalk(std::vector<std::string> field, int line, int collum, int direction);
void fillThis(std::vector<std::string>& field, int line, int collum, int direction);
void fillDeadEnds(std::vector<std::string>& data);

int threadCount = 0;

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
        int cost = recurciveSplitWalk(data, is, js, dir);
        if (curdir != dir) {
            cost += 1000;
        }
        paths.push_back(cost);
    }
    return *std::min_element(paths.begin(), paths.end()) + 1;
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

int recurciveSplitWalk(std::vector<std::string> field, int line, int column, int direction) {
    int value = 1;
    std::vector<int> openings;
    field[line][column] = '#';
    fillThis(field, line, column, direction);
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
        if (openings.front() != direction) {
            direction = openings.front();
            value += 1000;
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
        return 0x10000000;
    }

    std::vector<int> paths;
    paths.reserve(4);
    {
        std::vector<std::jthread> threads;
        void threadfunc(std::vector<int>::iterator index, const std::vector<std::string>field, int line, int column, int dir, int direction);
        std::vector<int>::iterator  index;
        for (int dir : openings) {
            paths.push_back(0);
            index = --paths.end();
            if (threadCount < 16) {
                threads.push_back(std::jthread(threadfunc, index, field, line, column, dir, direction));
            }
            else {
                threadfunc(index, field, line, column, dir, direction);
            }
        }
    }
    return value + *std::min_element(paths.begin(), paths.end());
}

void threadfunc(std::vector<int>::iterator index, const std::vector<std::string> field, int line, int column, int dir, int direction) {
    int cost = recurciveSplitWalk(field, line, column, dir);
    if (direction != dir) {
        cost += 1000;
    }
    *index = cost;
}
void fillThis(std::vector<std::string>& field, int line, int collum, int direction) {
    if (direction != 0) {
        int _column = collum + 1;
        int _line = line;
        std::vector<int> openings;
        do {
            if (field[_line][_column] == '#') {
                break;
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
    if (direction != 1) {
        int _column = collum;
        int _line = line + 1;
        std::vector<int> openings;
        do {
            if (field[_line][_column] == '#') {
                break;
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
    if (direction != 2) {
        int _column = collum - 1;
        int _line = line;
        std::vector<int> openings;
        do {
            if (field[_line][_column] == '#') {
                break;
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
    if (direction != 3) {
        int _column = collum;
        int _line = line - 1;
        std::vector<int> openings;
        do {
            if (field[_line][_column] == '#') {
                break;
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
}

