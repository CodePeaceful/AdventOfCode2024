#pragma once

class ClawMachine
{
private:
    long long _ax;
    long long _ay;
    long long _bx;
    long long _by;
    long long _px;
    long long _py;
public:
    ClawMachine(long long ax, long long ay, long long bx, long long by, long long px, long long py) : _ax { ax }, _ay { ay }, _bx { bx }, _by { by }, _px { px }, _py { py } {}

    long long requiredTokens() const {
        long long axCycle = 1;
        long long bxCycle = 1;
        {
            long long a = _ax;
            long long b = _bx;
            while (a != b) {
                if (a < b) {
                    a += _ax;
                    ++axCycle;
                }
                else {
                    b += _bx;
                    ++bxCycle;
                }
            }
        }
        long long yOffset = axCycle * _ay - bxCycle * _by;
        long long tokens = _px / _bx + 1;
        long long curx = tokens * _bx;
        long long cury = tokens * _by;
        long long tries = 0;
        long long as = 0;
        long long bs = tokens;
        while (curx != _px && tries < axCycle * bxCycle) {
            while (curx > _px) {
                --tokens;
                --bs;
                curx -= _bx;
                cury -= _by;
                if (bs < 0) {
                    std::cout << "no\n";
                    return 0;
                }
            }
            while (curx < _px) {
                tokens += 3;
                ++as;
                curx += _ax;
                cury += _ay;
            }
            ++tries;
        }
        long long ydiff = _py - cury;

        if (ydiff == 0) {
            return tokens;
        }
        long long shift = ydiff / yOffset;
        if (shift == 0) {
            std::cout << "no\n";
            return 0;
        }
        if (ydiff % shift) {
            std::cout << "no\n";
            return 0;
        }
        tokens += (3 * shift * axCycle);
        as += (shift * axCycle);
        tokens -= (shift * bxCycle);
        bs -= (shift * bxCycle);
        if (bs < 0 || as < 0) {
            std::cout << "no\n";
            return 0;
        }
        if (!(as * _ax + bs * _bx == _px && as * _ay + bs * _by == _py)) {
            std::cout << "no\n";
            return 0;
        }
        std::cout << "yes\n";
        return tokens;
    }
};
