#include <iostream>

#include "..\utility.hpp"

int solve(std::vector<std::string>);
bool outOfBounds(int top, int left);
void walk(std::vector<std::string>& map);
void findStart(const std::vector<std::string>& map, int& top, int& left);

static int width, height;

int main() {
    std::cout << solve(load()) << '\n';
}

int solve(std::vector<std::string> data) {
    height = data.size();
    width = data.front().size();

    walk(data);
    int visited = 0;
    for (const auto& line : data) {
        visited += std::count(line.begin(), line.end(), 'X');
    }
    return visited;
}

bool outOfBounds(int top, int left) {
    return top < 0 || left < 0 || top >= height || left >= width;
}

void walk(std::vector<std::string>& map) {
    enum direction
    {
        UP,
        RIGHT,
        DOWN,
        LEFT
    };
    int top = 0;
    int left = 0;
    findStart(map, top, left);

    direction d = UP;
    while (!outOfBounds(top, left)) {
        map[top][left] = 'X';
        switch (d) {
        case UP:
            --top;
            while (!outOfBounds(top, left) && map[top][left] != '#') {
                map[top][left] = 'X';
                --top;
            }
            if (outOfBounds(top, left))
                return;
            ++top;
            d = RIGHT;
            break;
        case RIGHT:
            ++left;
            while (!outOfBounds(top, left) && map[top][left] != '#') {
                map[top][left] = 'X';
                ++left;
            }
            if (outOfBounds(top, left))
                return;
            --left;
            d = DOWN;
            break;
        case DOWN:
            ++top;
            while (!outOfBounds(top, left) && map[top][left] != '#') {
                map[top][left] = 'X';
                ++top;
            }
            if (outOfBounds(top, left))
                return;
            --top;
            d = LEFT;
            break;
        case LEFT:
            --left;
            while (!outOfBounds(top, left) && map[top][left] != '#') {
                map[top][left] = 'X';
                --left;
            }
            if (outOfBounds(top, left))
                return;
            ++left;
            d = UP;
            break;
        }
    }
}

void findStart(const std::vector<std::string>& map, int& top, int& left) {
    for (top = 0; top < height; ++top) {
        for (left = 0; left < width; ++left) {
            if (map[top][left] == '^') {
                return;
            }
        }
    }
}
