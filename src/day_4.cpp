#include <iostream>
#include <string>
#include <tuple>
#include <vector>

#include "utils.h"

namespace day_4 {
struct Point {
    int x, y;

    int i_in_grid(int grid_size) { return y * grid_size + x; }

    bool off_grid(int grid_size) {
        return x < 0 || x >= grid_size || y < 0 || y >= grid_size;
    }

    static Point from_index(int i, int grid_size) {
        return {i % grid_size, i / grid_size};
    }
};

int run_pt_1_(std::string input, int size) {
    const char valid_chars[] = {'X', 'M', 'A', 'S'};
    const Point dir_offsets[] = {
        {0, 1},   // North
        {1, 1},   // North-East
        {1, 0},   // East
        {1, -1},  // South-East
        {0, -1},  // South
        {-1, -1}, // South-West
        {-1, 0},  // West
        {-1, 1},  // North-West
    };

    int count = 0;

    for (int i = 0; i < input.length(); i++) {
        char ch = input[i];
        if (ch != 'X') continue;

        Point point = Point::from_index(i, size);

        for (Point dir : dir_offsets) {
            Point extent = {point.x + 3 * dir.x, point.y + 3 * dir.y};
            if (extent.off_grid(size)) continue;

            bool is_valid = true;

            for (int offset = 1; offset <= 3; offset++) {
                Point offset_pt = {
                    point.x + offset * dir.x,
                    point.y + offset * dir.y,
                };
                char ch = input[offset_pt.i_in_grid(size)];

                if (valid_chars[offset] != ch) {
                    is_valid = false;
                    break;
                }
            }

            if (is_valid) count++;
        }
    }

    return count;
}

int run_pt_2_(std::string input, int size) {
    int count = 0;

    for (int i = 0; i < input.length(); i++) {
        char ch = input[i];
        if (ch != 'A') continue;

        Point center = Point::from_index(i, size);

        Point tl = {center.x - 1, center.y + 1};
        if (tl.off_grid(size)) continue;
        char ch_tl = input[tl.i_in_grid(size)];

        Point tr = {center.x + 1, center.y + 1};
        if (tr.off_grid(size)) continue;
        char ch_tr = input[tr.i_in_grid(size)];

        Point bl = {center.x - 1, center.y - 1};
        if (bl.off_grid(size)) continue;
        char ch_bl = input[bl.i_in_grid(size)];

        Point br = {center.x + 1, center.y - 1};
        if (br.off_grid(size)) continue;
        char ch_br = input[br.i_in_grid(size)];

        bool valid =
            (ch_tl == 'S' && ch_br == 'M') || (ch_tl == 'M' && ch_br == 'S');
        valid &=
            (ch_tr == 'S' && ch_bl == 'M') || (ch_tr == 'M' && ch_bl == 'S');
        if (valid) count++;
    }

    return count;
}

int run(std::vector<std::string> const *lines, bool is_part1) {
    int size = lines[0].size();
    std::string full = "";
    for (std::string line : *lines) {
        full += line;
    }

    if (is_part1) {
        return run_pt_1_(full, size);
    } else {
        return run_pt_2_(full, size);
    }
}
} // namespace day_4
