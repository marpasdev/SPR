#include <iostream>
#include <vector>

class Field {
    size_t n = 0;
    size_t m = 0;
    std::vector<char> grid;

public:

    Field(size_t n, size_t m) : n(n), m(m) {
        grid.reserve(n * m);
    }

    char at(size_t x, size_t y) const {
        return grid.at(y * m + x);
    }

    void push(char c) {
        grid.push_back(c);
    }

    char getHintAt(size_t x, size_t y) const {
        char c = at(x, y);

        if (c == '*') { 
            return '*'; 
        } else {
            size_t adjacentMineCount = 0;
            for (int ry = -1; ry <= 1; ++ry) {
                for (int rx = -1; rx <= 1; ++rx) {
                    if (rx == 0 && ry == 0) { continue; }

                    int checkedX = static_cast<int>(x) + rx;
                    int checkedY = static_cast<int>(y) + ry;

                    if (checkedX < 0 || checkedY < 0 || checkedX >= m || checkedY >= n) { continue;}

                    if (at(checkedX, checkedY) == '*') { ++adjacentMineCount; }
                }
            }

            return static_cast<char>('0' + adjacentMineCount);
        }
    }

    Field getUncovered() const {
        Field uncovered(n, m);

        for (size_t y = 0; y < n; ++y) {
            for (size_t x = 0; x < m; ++x) {
                uncovered.push(getHintAt(x, y));
            }
        }

        return uncovered;
    }

    size_t getN() const { return n; }

    size_t getM() const { return m; }
};

// Minesweeper
int main() {

    std::vector<Field> fields;

    int rows = 0;
    int cols = 0;
    do {
        std::cin >> rows;
        std::cin >> cols;

        if (rows == 0 && cols == 0) { break; }

        Field f = Field(rows, cols);

        std::string row = "";
        for (size_t i = 0; i < rows; ++i) {

            std::cin >> row;
            for (char c : row) {
                if (c == '*' || c == '.') { f.push(c); }
            }
        }

        fields.push_back(f);

    } while (rows != 0 && cols != 0);

    for (size_t i = 0; i < fields.size(); ++i) {
        std::cout << "Field #" << (i + 1) << ":" << '\n';

        Field current = fields[i];

        Field uncovered = current.getUncovered();

        for (size_t y = 0; y < current.getN(); ++y) {
            for (size_t x = 0; x < current.getM(); ++x) {
                std::cout << uncovered.at(x, y);
            }
            std::cout << '\n';
        }

        if (i != fields.size() - 1) {
            std::cout << '\n';
        }
    }

    return 0;
}