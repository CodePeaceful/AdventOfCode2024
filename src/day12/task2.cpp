#include <iostream>
#include <numeric>

#include "Field.hpp"
#include "..\utility.hpp"


int solve(std::vector<std::string>);

int main() {
    std::cout << solve(load()) << '\n';
}

int solve(std::vector<std::string> data) {
    std::vector<Field> fields;
    for (int x = 0; x < data.size(); ++x) {
        for (int y = 0; y < data.front().size(); ++y) {
            /*if (!std::isalpha(data[x][y])) {
                continue;
            }*/
            std::vector<Field*> inserted;
            for (auto& field : fields) {
                if (field.isSame(data[x][y])) {
                    if (field.tryInsert(x, y)) {
                        inserted.push_back(&field);
                    }
                }
            }
            if (inserted.size() == 0) {
                fields.push_back(Field(data[x][y], x, y));
            }
            else if (inserted.size() > 1) {
                for (int i = 1; i < inserted.size(); ++i) {
                    inserted.front()->fuse(*(inserted.at(i)));
                }
            }
        }
    }
    return std::accumulate(fields.begin(), fields.end(), 0, [] (int i, const Field& f) {return f.getCosts2() + i;});
}
