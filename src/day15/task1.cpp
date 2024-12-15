#include <iostream>
#include <ranges>

#include "..\utility.hpp"

int solve(std::vector<std::string>);
bool tryGolr(std::vector<std::string>& field, std::pair<int, int> pos, std::pair<int, int> direction);

int main() {
    std::cout << solve(load()) << '\n';
}

int solve(std::vector<std::string> data) {
    auto field = data | std::views::take_while([] (std::string s) {return s.size() > 0;}) | std::ranges::to<std::vector<std::string>>();

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
                if (tryGolr(field, robotpos, { 0, -1 }))
                    --robotpos.second;
                break;
            case 'v':
                if (tryGolr(field, robotpos, { 1, 0 }))
                    ++robotpos.first;
                break;
            case '>':
                if (tryGolr(field, robotpos, { 0, 1 }))
                    ++robotpos.second;
                break;
            case '^':
                if (tryGolr(field, robotpos, { -1, 0 }))
                    --robotpos.first;
                break;
            default:
                break;
            }
        }
    }
    int value = 0;
    for (int y = 0; y < field.size(); ++y) {
        for (int x = 0; x < field[y].size(); ++x) {
            if (field[y][x] == 'O') {
                value += (y * 100 + x);
            }
        }
    }
    return value;
}

bool tryGolr(std::vector<std::string>& field, std::pair<int, int> pos, std::pair<int, int> direction) {
    switch (field[pos.first + direction.first][pos.second + direction.second]) {
    case '#':
        return false;
    case '.':
        std::swap(field[pos.first + direction.first][pos.second + direction.second], field[pos.first][pos.second]);
        return true;
    case 'O':
        if (tryGolr(field, { pos.first + direction.first, pos.second + direction.second }, direction)) {
            std::swap(field[pos.first + direction.first][pos.second + direction.second], field[pos.first][pos.second]);
            return true;
        }
        return false;
    default:
        throw std::exception();
    }
}
