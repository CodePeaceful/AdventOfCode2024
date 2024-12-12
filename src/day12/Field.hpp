#pragma once
#include <set>
#include <vector>

class Field
{
private:
    std::set<std::pair<int, int>> _cells;
    char _type;
    int scanx(const std::vector<std::vector<std::pair<int, int>>>& xsames) const {
        int sum = 0;
        for (const auto& xsame : xsames) {
            for (int i = 0; i < xsame.size(); ++i) {
                std::vector<std::pair<int, int>> line;
                line.push_back(xsame[i]);
                while (i < xsame.size() + 1 && line.back().second + 1 == xsame[i + 1].second) {
                    ++i;
                    line.push_back(xsame[i]);
                }
                if (std::any_of(line.begin(), line.end(), [this] (std::pair<int, int> pair) {
                    std::pair<int, int> maybe { pair.first + 1, pair.second };
                    return this->contains(maybe);})) {
                    ++sum;
                }
                if (std::any_of(line.begin(), line.end(), [this] (std::pair<int, int> pair) {
                    std::pair<int, int> maybe { pair.first - 1, pair.second };
                    return this->contains(maybe);})) {
                    ++sum;
                }
            }
        }
        return sum;
    }

    int scany(const std::vector<std::vector<std::pair<int, int>>>& ysames) const {
        int sum = 0;
        for (const auto& ysame : ysames) {
            for (int i = 0; i < ysame.size(); ++i) {
                std::vector<std::pair<int, int>> line;
                line.push_back(ysame[i]);
                while (i < ysame.size() + 1 && line.back().first + 1 == ysame[i + 1].first) {
                    ++i;
                    line.push_back(ysame[i]);
                }
                if (std::any_of(line.begin(), line.end(), [this] (std::pair<int, int> pair) {
                    std::pair<int, int> maybe { pair.first, pair.second - 1 };
                    return this->contains(maybe);})) {
                    ++sum;
                }
                if (std::any_of(line.begin(), line.end(), [this] (std::pair<int, int> pair) {
                    std::pair<int, int> maybe { pair.first, pair.second + 1 };
                    return this->contains(maybe);})) {
                    ++sum;
                }
            }
        }
        return sum;
    }
public:
    Field(char type, int x, int y) : _type { type } {
        _cells.insert({ x, y });
    }

    bool contains(std::pair<int, int> pair) const {
        return _cells.contains(pair);
    }

    bool isSame(char type) const {
        return type == _type;
    }

    bool tryInsert(int x, int y) {
        if (_cells.contains({ x + 1, y }) || _cells.contains({ x, y + 1 }) || _cells.contains({ x - 1, y }) || _cells.contains({ x, y - 1 })) {
            _cells.insert({ x, y });
            return true;
        }
        return false;
    }

    void fuse(Field& other) {
        for (auto& pair : other._cells) {
            _cells.insert(pair);
        }
        other._cells.clear();
    }

    int getCosts() const {
        int sum = 0;
        for (const auto& [x, y] : _cells) {
            if (!_cells.contains({ x + 1, y })) {
                ++sum;
            }
            if (!_cells.contains({ x, y + 1 })) {
                ++sum;
            }
            if (!_cells.contains({ x - 1, y })) {
                ++sum;
            }
            if (!_cells.contains({ x, y - 1 })) {
                ++sum;
            }
        }
        return sum * _cells.size();
    }

    int getCosts2() const {
        std::set<std::pair<int, int>> justOutside;
        for (const auto& [x, y] : _cells) {
            if (!_cells.contains({ x + 1, y })) {
                justOutside.insert({ x + 1, y });
            }
            if (!_cells.contains({ x, y + 1 })) {
                justOutside.insert({ x, y + 1 });
            }
            if (!_cells.contains({ x - 1, y })) {
                justOutside.insert({ x - 1, y });
            }
            if (!_cells.contains({ x, y - 1 })) {
                justOutside.insert({ x, y - 1 });
            }
        }
        std::vector<std::vector<std::pair<int, int>>> xsames;
        std::vector<std::vector<std::pair<int, int>>> ysames;
        for (const auto& p : justOutside) {
            for (int i = 0; ; ++i) {
                if (i == xsames.size()) {
                    xsames.emplace_back();
                    xsames.back().emplace_back(p);
                    break;
                }
                if (xsames[i].front().first == p.first) {
                    xsames[i].push_back(p);
                    break;
                }
            }
            for (int i = 0; ; ++i) {
                if (i == ysames.size()) {
                    ysames.emplace_back();
                    ysames.back().emplace_back(p);
                    break;
                }
                if (ysames[i].front().second == p.second) {
                    ysames[i].push_back(p);
                    break;
                }
            }
        }
        for (auto& xsame : xsames) {
            std::sort(xsame.begin(), xsame.end());
        }
        for (auto& ysame : ysames) {
            std::sort(ysame.begin(), ysame.end());
        }
        int sum = scanx(xsames) * 2;
        int altsum = 2 * scany(ysames);
        if (sum < altsum)
            sum = altsum;
        return sum * _cells.size();
    }
};

