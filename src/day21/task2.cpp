#include <iostream>
#include <map>

#include "..\utility.hpp"

long long solve(std::vector<std::string>);
std::string stepOneStep(std::string outPart, std::string input, char pos);
std::string stepTwoStep(std::string outPart, std::string input, char pos);
std::string stepOneSolve(const std::string& out);
std::string stepTwoSolve(const std::string& out);
std::vector<std::string> getParts(std::string s);

std::vector<std::pair<char, char>> keypadOne { { 'A', '1' }, { 'A', '4' }, { 'A', '7' }, { '0', '1' }, { '0', '4' }, { '0', '7' } };
std::vector<std::pair<char, char>> controlerOne { { '^', '<' }, { 'A', '<' } };
std::vector<std::string> controlerPaths { "A", "<<vA", ">>^A", "<A", ">A", "vA", "^A", "<vA", ">^A", ">vA", "<^A" };

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

long long solve(std::vector<std::string> data) {
    const int padBots = 25;
    long long result = 0;
    std::map<std::string, std::string> four;
    for (auto part : controlerPaths) {
        auto bot = part;
        for (int i = 0; i < 4; ++i) {
            bot = stepTwoSolve(bot);
        }
        four[part] = bot;
        long long total = 0;
        std::cout << bot.size() << '\n';
    }
    std::map<std::string, std::string> five;
    for (auto part : controlerPaths) {
        auto bot = part;
        for (int i = 0; i < 5; ++i) {
            bot = stepTwoSolve(bot);
        }
        five[part] = bot;
        long long total = 0;
        std::cout << bot.size() << '\n';
    }
    std::map<std::string, long long> partlenghs24;
    for (auto [part, expansion] : four) {
        long long length = 0;
        for (auto p5 : getParts(expansion)) {
            for (auto p10 : getParts(four[p5])) {
                for (auto p15 : getParts(four[p10])) {
                    for (auto p20 : getParts(four[p15])) {
                        length += four[p20].size();
                    }
                }
            }
        }
        std::cout << part << '\n';
        partlenghs24[part] = length;
    }
    for (const auto& code : data) {
        auto bot = stepOneSolve(code);
        long long sum = 0;
        bot = stepTwoSolve(bot);
        for (auto p : getParts(bot)) {
            sum += partlenghs24[p];
        }
        result += sum * std::stoll(code.substr(0, code.size() - 1));
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

std::map<std::string, std::vector<std::string>> getPartsMemo;

std::vector<std::string> getParts(std::string s) {
    if (getPartsMemo.contains(s)) {
        return getPartsMemo[s];
    }
    std::vector<std::string> parts;
    bool success = false;
    while (s.size()) {
        success = false;
        for (const auto& part : controlerPaths) {
            if (s.starts_with(part)) {
                parts.push_back(part);
                s = s.substr(part.size(), s.size());
                success = true;
                break;
            }
        }
        if (!success) {
            std::cout << s;
            throw std::exception();
        }
    }
    getPartsMemo[s] = parts;
    return parts;
}
