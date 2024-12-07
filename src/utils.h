#ifndef AOC_UTILS_H_
#define AOC_UTILS_H_

#include <string>
#include <vector>

namespace utils {
struct Pt {
    int x, y;

    int hash();
    int i_in_grid(int grid_size);
    bool off_grid(int grid_size);
    Pt operator+(const Pt &other);

    static Pt from_index(int i, int grid_size);
};

enum Dir {
    NORTH,
    NORTH_EAST,
    EAST,
    SOUTH_EAST,
    SOUTH,
    SOUTH_WEST,
    WEST,
    NORTH_WEST,
};

constexpr Dir directions[8] = {
    NORTH, NORTH_EAST, EAST, SOUTH_EAST, SOUTH, SOUTH_WEST, WEST, NORTH_WEST,
};

Pt dir_offset(Dir dir);
Dir rot90(Dir dir, bool clockwise = true);

void print_ints(std::vector<int> const *vec);
std::vector<std::string> split(std::string str, std::string delimiter);
} // namespace utils
#endif
