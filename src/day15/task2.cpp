#include <iostream>
#include <ranges>

#include "..\utility.hpp"

int solve(std::vector<std::string>);
bool tryGolr(std::vector<std::string>& field, std::pair<int, int> pos, bool left);
bool tryGoud(std::vector<std::string>& field, std::pair<int, int> pos, bool up);
void goud(std::vector<std::string>& field, std::pair<int, int> pos, bool up);

int main() {
    std::cout << solve(load()) << '\n';
}

int solve(std::vector<std::string> data) {
    std::vector<std::string> field;

    for (auto& line : data | std::views::take_while([] (std::string s) {return s.size() > 0;})) {
        field.emplace_back();
        for (char c : line) {
            switch (c) {
            case '\n':
                field.back().append("\n");
                break;
            case '#':
                field.back().append("##");
                break;
            case '.':
                field.back().append("..");
                break;
            case 'O':
                field.back().append("[]");
                break;
            case '@':
                field.back().append("@.");
                break;
            default:
                throw std::exception();
            }
        }
    }

    std::pair<int, int> robotpos;
    for (int y = 0; y < field.size(); ++y) {
        for (int x = 0; x < field[y].size(); ++x) {
            if (field[y][x] == '@') {
                robotpos = std::make_pair(y, x);
                y = field.size();
                break;
            }
        }
    }
    for (const auto& line : data | std::views::drop(field.size() + 1)) {
        for (char c : line) {
            switch (c) {
            case '<':
                if (tryGolr(field, robotpos, true))
                    --robotpos.second;
                break;
            case 'v':
                if (tryGoud(field, robotpos, false)) {
                    goud(field, robotpos, false);
                    ++robotpos.first;
                }
                break;
            case '>':
                if (tryGolr(field, robotpos, false))
                    ++robotpos.second;
                break;
            case '^':
                if (tryGoud(field, robotpos, true)) {
                    goud(field, robotpos, true);
                    --robotpos.first;
                }
                break;
            default:
                break;
            }
        }
    }
    int value = 0;
    for (int y = 0; y < field.size(); ++y) {
        for (int x = 0; x < field[y].size(); ++x) {
            if (field[y][x] == '[') {
                value += (y * 100 + x);
            }
        }
    }
    return value;
}

bool tryGolr(std::vector<std::string>& field, std::pair<int, int> pos, bool left) {
    int second = left ? -1 : 1;
    switch (field[pos.first][pos.second + second]) {
    case '#':
        return false;
    case '.':
        std::swap(field[pos.first][pos.second + second], field[pos.first][pos.second]);
        return true;
    case '[':
    case ']':
        if (tryGolr(field, { pos.first, pos.second + second }, left)) {
            std::swap(field[pos.first][pos.second + second], field[pos.first][pos.second]);
            return true;
        }
        return false;
    default:
        throw std::exception();
    }
}

bool tryGoud(std::vector<std::string>& field, std::pair<int, int> pos, bool up) {
    int first = up ? -1 : 1;
    switch (field[pos.first + first][pos.second]) {
    case '#':
        return false;
    case '.':
        return true;
    case '[':
        if (tryGoud(field, { pos.first + first, pos.second }, up) && tryGoud(field, { pos.first + first, pos.second + 1 }, up)) {
            return true;
        }
        return false;
    case ']':
        if (tryGoud(field, { pos.first + first, pos.second }, up) && tryGoud(field, { pos.first + first, pos.second - 1 }, up)) {
            return true;
        }
        return false;
    default:
        throw std::exception();
    }
}

void goud(std::vector<std::string>& field, std::pair<int, int> pos, bool up) {
    int first = up ? -1 : 1;
    switch (field[pos.first + first][pos.second]) {
    case '.':
        std::swap(field[pos.first + first][pos.second], field[pos.first][pos.second]);
        break;
    case '[':
        goud(field, { pos.first + first, pos.second }, up);
        goud(field, { pos.first + first, pos.second + 1 }, up);
        std::swap(field[pos.first + first][pos.second], field[pos.first][pos.second]);
        break;
    case ']':
        goud(field, { pos.first + first, pos.second }, up);
        goud(field, { pos.first + first, pos.second - 1 }, up);
        std::swap(field[pos.first + first][pos.second], field[pos.first][pos.second]);
        break;
    default:
        break;
    }
}
