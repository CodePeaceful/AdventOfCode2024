#pragma once
#include <compare>
#include <numeric>

class Vec2d
{
private:
    int _top;
    int _left;

public:
    Vec2d(int top, int left) : _top { top }, _left { left } {}
    Vec2d dif(const Vec2d& other) const {
        int top = _top - other._top;
        int left = _left - other._left;
        return Vec2d(top, left);
    }
    Vec2d add(const Vec2d& dif) const {
        int top = _top + dif._top;
        int left = _left + dif._left;
        return Vec2d(top, left);
    }
    Vec2d subtract(const Vec2d& dif) const {
        int top = _top - dif._top;
        int left = _left - dif._left;
        return Vec2d(top, left);
    }
    bool inBound(int height, int width) const {
        return _top >= 0 && _left >= 0 && _top < height && _left < width;
    }
    bool operator==(const Vec2d& other) {
        return _top == other._top && _left == other._left;
    }
    auto operator<=>(const Vec2d& other) const {
        if (auto cmp = _left <=> other._left; cmp != 0) {
            return cmp;
        }
        return _top <=> other._top;
    }
    void setSmalestCommon() {
        int left = std::abs(_left);
        int top = std::abs(_top);
        if (left == 0) {
            _top /= top;
            return;
        }
        if (top == 0) {
            _left /= left;
            return;
        }
        int gcd = std::gcd(left, top);
        _top /= gcd;
        _left /= gcd;
    }
};

