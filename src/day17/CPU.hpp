#pragma once
#include <vector>
#include <cmath>
#include <stdint.h>


class CPU
{
private:
    long long A;
    long long B;
    long long C;
    int counter = 0;
    std::vector<int> programm;
    std::vector<int> out;
    long long getCombo() {
        int value = programm[counter + 1];
        switch (value) {
        case 0:
        case 1:
        case 2:
        case 3:
            return value;
        case 4:
            return A;
        case 5:
            return B;
        case 6:
            return C;
        default:
            throw std::exception();
        }
    }
public:
    CPU(long long A, long long B, long long C, std::vector<int> programm) : A { A }, B { B }, C { C }, programm { programm } {}
    bool step() {
        if (counter >= programm.size()) {
            return false;
        }
        switch (programm[counter]) {
        case 0:
            A /= (long long)std::pow(2, getCombo());
            break;
        case 1:
            B = B ^ programm[counter + 1];
            break;
        case 2:
            B = getCombo() % 8;
            break;
        case 3:
            if (A == 0) {
                break;
            }
            counter = programm[counter + 1];
            return true;
        case 4:
            B = B ^ C;
            break;
        case 5:
            out.push_back(getCombo() % 8);
        case 6:
            B = A / (long long)std::pow(2, getCombo());
            break;
        case 7:
            C = A / (long long)std::pow(2, getCombo());
            break;
        default:
            throw std::exception();
        }
        counter += 2;
        return true;
    }
    bool step2() {
        if (counter >= programm.size()) {
            return false;
        }
        int num = getCombo() % 8;
        switch (programm[counter]) {
        case 0:
            A /= (long long)std::pow(2, getCombo());
            break;
        case 1:
            B = B ^ programm[counter + 1];
            break;
        case 2:
            B = num;
            break;
        case 3:
            if (A == 0) {
                break;
            }
            counter = programm[counter + 1];
            return true;
        case 4:
            B = B ^ C;
            break;
        case 5:
            if (num != programm[out.size()]) {
                return false;
            }
            out.push_back(num);
            break;
        case 6:
            B = A / (long long)std::pow(2, getCombo());
            break;
        case 7:
            C = A / (long long)std::pow(2, getCombo());
            break;
        default:
            throw std::exception();
        }
        counter += 2;
        return true;
    }
    const std::vector<int>& getOut() {
        return out;
    }
};
