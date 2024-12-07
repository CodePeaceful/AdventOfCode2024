#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <ranges>

#include "../utility.hpp"

class Eqation
{
private:
    std::vector<unsigned long long> values;
    unsigned long long result;
public:
    Eqation(const std::string& data);
    bool isSolvable();
    bool isConcatSovable();
    unsigned long long getResult() {
        return result;
    }
};

inline Eqation::Eqation(const std::string& data) {
    auto split1 = split(data, ':');
    result = std::stoull(split1[0]);
    ltrim(split1[1]);
    auto split2 = split(split1[1], ' ');
    for (const auto& val : split2) {
        values.push_back(std::stoull(val));
    }
}

inline bool Eqation::isSolvable() {
    for (int mul = 0; mul < values.size(); ++mul) {
        std::vector<char> ops;
        int i = 0;
        for (; i < mul; ++i) {
            ops.push_back('*');
        }
        for (; i < values.size(); ++i) {
            ops.push_back('+');
        }
        do {
            unsigned long long value = values[0];
            for (int j = 0; j < values.size() - 1; ++j) {
                if (ops[j] == '*') {
                    value *= values[j + 1];
                }
                else {
                    value += values[j + 1];
                }
            }
            if (value == result) {
                return true;
            }
        } while (std::ranges::next_permutation(ops).found);
    }
    return false;
}

inline bool Eqation::isConcatSovable() {
    for (int concat = 0; concat < values.size(); ++concat) {
        for (int mul = concat; mul < values.size(); ++mul) {
            std::vector<char> ops;
            int i = 0;
            for (; i < concat; ++i) {
                ops.push_back('"');
            }
            for (; i < mul; ++i) {
                ops.push_back('*');
            }
            for (; i < values.size() - 1; ++i) {
                ops.push_back('+');
            }
            do {
                unsigned long long value = values[0];
                for (int j = 0; j < values.size() - 1; ++j) {
                    if (ops[j] == '"') {
                        unsigned long long multiplier = 10;
                        while (values[j + 1] > multiplier) {
                            multiplier *= 10;
                        }
                        value *= multiplier;
                        value += values[j + 1];
                    }
                    else if (ops[j] == '*') {
                        value *= values[j + 1];
                    }
                    else {
                        value += values[j + 1];
                    }
                }
                if (value == result) {
                    return true;
                }
            } while (std::next_permutation(ops.begin(), ops.end()));
        }
    }
    return false;
}
