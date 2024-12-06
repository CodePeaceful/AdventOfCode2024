#include <iostream>

#include "..\utility.hpp"

void solve(std::vector<std::string>);
bool outOfBounds(int top, int left);
void checkForPotentials(std::vector<std::string>& map);
void findStart(const std::vector<std::string>& map, int& top, int& left);
void test(std::vector<std::string> map);

static int width, height, startleft, starttop, blocker;
int counter = 0;

int main() {
    solve(load());
    std::cout << counter << '\n';
}

void solve(std::vector<std::string> data) {
    height = data.size();
    width = data.front().size();

    checkForPotentials(data);
    blocker = 0;
    for (const auto& line : data) {
        blocker += std::count(line.begin(), line.end(), '#');
    }
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (data[i][j] == 'P') {
                data[i][j] = '#';
                test(data);
                data[i][j] = '.';
            }
        }
    }
}

void test(std::vector<std::string> map) {
    enum direction
    {
        UP,
        RIGHT,
        DOWN,
        LEFT
    };
    int top = starttop;
    int left = startleft;
    int upBlocked = 0;
    direction d = UP;
    while (!outOfBounds(top, left)) {
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
            ++upBlocked;
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
        if (upBlocked > blocker + 1) {
            ++counter;
            return;
        }
    }
}

bool outOfBounds(int top, int left) {
    return top < 0 || left < 0 || top >= height || left >= width;
}

void checkForPotentials(std::vector<std::string>& map) {
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
    startleft = left;
    starttop = top;
    direction d = UP;
    while (!outOfBounds(top, left)) {
        if (map[top][left] != 'S')
            map[top][left] = 'P';
        switch (d) {
        case UP:
            --top;
            while (!outOfBounds(top, left) && map[top][left] != '#') {
                if (map[top][left] != 'S')
                    map[top][left] = 'P';
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
                if (map[top][left] != 'S')
                    map[top][left] = 'P';
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
                if (map[top][left] != 'S')
                    map[top][left] = 'P';
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
                if (map[top][left] != 'S')
                    map[top][left] = 'P';
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

