#pragma once

class Robot
{
private:
    int curx;
    int cury;
    int xv;
    int yv;
public:
    Robot(int x, int y, int xv, int yv) : curx { x }, cury { y }, xv { xv }, yv { yv } {}

    void moveCycles(int cycles) {
        curx += (xv * cycles);
        curx %= 101;
        cury += (yv * cycles);
        cury %= 103;
        if (curx < 0) {
            curx += 101;
        }
        if (cury < 0) {
            cury += 103;
        }
    }

    int getQuadrant() {
        if (curx == 50 || cury == 51) {
            return -1;
        }
        int q = 0;
        if (curx > 50) {
            q += 1;
        }
        if (cury > 51) {
            q += 2;
        }
        return q;
    }

    int getx() const {
        return curx;
    }

    int gety() const {
        return cury;
    }
};


