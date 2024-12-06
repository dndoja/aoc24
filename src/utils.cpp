#include "utils.h"
#include <iostream>

namespace utils {

int Pt::hash() { return x ^ y; }

int Pt::i_in_grid(int grid_size) { return y * grid_size + x; }

bool Pt::off_grid(int grid_size) {
    return x < 0 || x >= grid_size || y < 0 || y >= grid_size;
}

Pt Pt::from_index(int i, int grid_size) {
    return {i % grid_size, i / grid_size};
}

Pt dir_offset(Dir dir) {
    constexpr Pt direction_offsets[8] = {
        {0, 1},   // North
        {1, 1},   // North-East
        {1, 0},   // East
        {1, -1},  // South-East
        {0, -1},  // South
        {-1, -1}, // South-West
        {-1, 0},  // West
        {-1, 1},  // North-West
    };

    return direction_offsets[dir];
}

void print_ints(std::vector<int> const *vec) {
    for (int i : *vec) {
        std::cout << i << " ";
    }
    std::cout << "\n";
}

std::vector<std::string> split(std::string str, std::string delimiter) {
    std::vector<std::string> split = std::vector<std::string>();

    if (delimiter.length() == 0) {
        split.push_back(str);
        return split;
    }

    std::string buffer;
    int i = 0;
    while (i < str.length()) {
        char ch = str[i];

        if (ch != delimiter[0]) {
            buffer += ch;
            i++;
            continue;
        }

        std::string lookahead_buf;
        int offset = 0;
        while (offset < delimiter.length()) {
            char ch = str[i + offset];
            if (ch == delimiter[offset]) {
                lookahead_buf += ch;
                offset++;
            } else {
                offset++;
                break;
            }
        }

        if (lookahead_buf.length() == delimiter.length()) {
            if (buffer.length() > 0) {
                split.push_back(buffer);
                buffer = "";
            }
        } else {
            buffer += lookahead_buf;
            buffer += str[i + offset - 1];
        }

        i += offset;
    }

    if (buffer.length() > 0) {
        split.push_back(buffer);
    }

    return split;
}
} // namespace utils
