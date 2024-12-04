#include <iostream>
#include <string>
#include <tuple>
#include <vector>

#include "utils.h"

namespace day_4 {
struct Point {
    int x, y;
};

Point i_to_pt(int i, int grid_size) { return {i % grid_size, i / grid_size}; }

int pt_to_i(Point *ptr, int grid_size) {
    Point pt = *ptr;
    return pt.y * grid_size + pt.x;
}

bool pt_on_grid(Point *ptr, int grid_size) {
    Point pt = *ptr;
    return pt.x >= 0 && pt.x < grid_size && pt.y >= 0 && pt.y < grid_size;
}

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

        Point point = i_to_pt(i, size);

        for (Point dir : dir_offsets) {
            Point extent = {point.x + 3 * dir.x, point.y + 3 * dir.y};
            if (!pt_on_grid(&extent, size)) continue;

            bool is_valid = true;

            for (int offset = 1; offset <= 3; offset++) {
                Point offset_pt = {
                    point.x + offset * dir.x,
                    point.y + offset * dir.y,
                };
                char ch = input[pt_to_i(&offset_pt, size)];

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

        Point center = i_to_pt(i, size);

        Point tl = {center.x - 1, center.y + 1};
        if (!pt_on_grid(&tl, size)) continue;
        char ch_tl = input[pt_to_i(&tl, size)];

        Point tr = {center.x + 1, center.y + 1};
        if (!pt_on_grid(&tr, size)) continue;
        char ch_tr = input[pt_to_i(&tr, size)];

        Point bl = {center.x - 1, center.y - 1};
        if (!pt_on_grid(&bl, size)) continue;
        char ch_bl = input[pt_to_i(&bl, size)];

        Point br = {center.x + 1, center.y - 1};
        if (!pt_on_grid(&br, size)) continue;
        char ch_br = input[pt_to_i(&br, size)];

        bool valid =
            (ch_tl == 'S' && ch_br == 'M') || (ch_tl == 'M' && ch_br == 'S');
        valid &=
            (ch_tr == 'S' && ch_bl == 'M') || (ch_tr == 'M' && ch_bl == 'S');
        if (valid) count++;
    }

    return count;
}

int run(std::vector<std::string> lines, bool is_part1) {
    int size = lines[0].size();
    std::string full = "";
    for (std::string line : lines) {
        full += line;
    }

    if (is_part1) {
        return run_pt_1_(full, size);
    } else {
        return run_pt_2_(full, size);
    }
}
} // namespace day_4
