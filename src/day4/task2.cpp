#include <iostream>

#include "..\utility.hpp"

int solve(std::vector<std::string>);

int main() {
    std::cout << solve(load()) << '\n';
}

int solve(std::vector<std::string> data) {
    int counter = 0;
    const int lineLength = data[0].size();
    for (auto i = 1ull; i < data.size() - 1; ++i) {
        int linepos = 0;
        while (linepos != -1) {
            linepos = data[i].find("A", linepos + 1);
            if (linepos > 0 && linepos < lineLength - 1) {
                bool downright = data[i - 1][linepos - 1] == 'M' && data[i + 1][linepos + 1] == 'S';
                bool upleft = data[i - 1][linepos - 1] == 'S' && data[i + 1][linepos + 1] == 'M';
                bool downleft = data[i - 1][linepos + 1] == 'M' && data[i + 1][linepos - 1] == 'S';
                bool upright = data[i - 1][linepos + 1] == 'S' && data[i + 1][linepos - 1] == 'M';
                if ((downright && downleft) || (downright && upright) || (upleft && downleft) || (upleft && upright)) {
                    ++counter;
                }
            }
        }
    }
    return counter;
}
