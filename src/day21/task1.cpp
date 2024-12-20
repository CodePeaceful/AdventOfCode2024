#include <iostream>
#include <map>

#include "..\utility.hpp"

int solve(std::vector<std::string>);
std::string stepOneStep(std::string outPart, std::string input, char pos);
std::string stepTwoStep(std::string outPart, std::string input, char pos);
std::string stepOneSolve(const std::string& out);
std::string stepTwoSolve(const std::string& out);

std::vector<std::pair<int, int>> keypadOne { { 'A', '1' }, { 'A', '4' }, { 'A', '7' }, { '0', '1' }, { '0', '4' }, { '0', '7' } };
std::vector<std::pair<int, int>> controlerOne { { '^', '<' }, { 'A', '<' } };

std::map<char, std::pair<int, int>> keypad {
    { 'A', { 0, 0 } },
    { '0', { 1, 0 } },
    { '1', { 2, 1 } },
    { '2', { 1, 1 } },
    { '3', { 0, 1 } },
    { '4', { 2, 2 } },
    { '5', { 1, 2 } },
    { '6', { 0, 2 } },
    { '7', { 2, 3 } },
    { '8', { 1, 3 } },
    { '9', { 0, 3 } }
};

std::map<char, std::pair<int, int>> controler {
    { 'A', { 0, 0 } },
    { '^', { 1, 0 } },
    { '>', { 0, -1 } },
    { 'v', { 1, -1 } },
    { '<', { 2, -1 } }
};

int main() {
    std::cout << solve(load()) << '\n';
}

int solve(std::vector<std::string> data) {
    const int padBots = 2;
    int result = 0;
    for (const auto& code : data) {
        auto bot = stepOneSolve(code);
        for (int i = 0; i < padBots; ++i) {
            bot = stepTwoSolve(bot);
        }
        result += bot.size() * std::stoi(code.substr(0, code.size() - 1));
    }
    return result;
}


std::string stepOneSolve(const std::string& out) {
    char pos = 'A';
    std::string input;
    return stepOneStep(out, input, pos);
}

std::string stepOneStep(std::string outPart, std::string input, char pos) {
    char c = outPart.front();
    auto target = keypad[c];
    auto origin = keypad[pos];
    if (std::any_of(keypadOne.begin(), keypadOne.end(), [pos, c] (std::pair<char, char> p) {return p.first == c && p.second == pos;})) {
        for (int i = target.first - origin.first; i < 0; ++i) {
            input += '>';
        }
        for (int i = target.second - origin.second; i < 0; ++i) {
            input += 'v';
        }
    }
    else if (std::any_of(keypadOne.begin(), keypadOne.end(), [pos, c] (std::pair<char, char> p) {return p.first == pos && p.second == c;})) {
        for (int i = 0; i < target.second - origin.second; ++i) {
            input += '^';
        }
        for (int i = 0; i < target.first - origin.first; ++i) {
            input += '<';
        }
    }
    else {
        for (int i = 0; i < target.first - origin.first; ++i) {
            input += '<';
        }
        for (int i = target.second - origin.second; i < 0; ++i) {
            input += 'v';
        }
        for (int i = target.first - origin.first; i < 0; ++i) {
            input += '>';
        }
        for (int i = 0; i < target.second - origin.second; ++i) {
            input += '^';
        }
    }
    input += 'A';
    pos = c;
    outPart.erase(outPart.begin());
    if (outPart.size() == 0) {
        return input;
    }
    return stepOneStep(outPart, input, pos);
}

std::string stepTwoStep(std::string outPart, std::string input, char pos) {
    char c = outPart.front();
    auto target = controler[c];
    auto origin = controler[pos];
    if (std::any_of(controlerOne.begin(), controlerOne.end(), [pos, c] (std::pair<char, char> p) {return p.first == c && p.second == pos;})) {
        for (int i = target.first - origin.first; i < 0; ++i) {
            input += '>';
        }
        for (int i = 0; i < target.second - origin.second; ++i) {
            input += '^';
        }
    }
    else if (std::any_of(keypadOne.begin(), keypadOne.end(), [pos, c] (std::pair<char, char> p) {return p.first == pos && p.second == c;})) {
        for (int i = target.second - origin.second; i < 0; ++i) {
            input += 'v';
        }
        for (int i = 0; i < target.first - origin.first; ++i) {
            input += '<';
        }
    }
    else {
        for (int i = 0; i < target.first - origin.first; ++i) {
            input += '<';
        }
        for (int i = target.second - origin.second; i < 0; ++i) {
            input += 'v';
        }
        for (int i = target.first - origin.first; i < 0; ++i) {
            input += '>';
        }
        for (int i = 0; i < target.second - origin.second; ++i) {
            input += '^';
        }
    }
    input += 'A';
    pos = c;
    outPart.erase(outPart.begin());
    if (outPart.size() == 0) {
        return input;
    }
    return stepTwoStep(outPart, input, pos);
}

std::string stepTwoSolve(const std::string& out) {
    char pos = 'A';
    std::string input;
    return  stepTwoStep(out, input, pos);
}
