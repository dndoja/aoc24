#include "utils.h"
#include <climits>
#include <iostream>
#include <queue>

namespace day_21 {
using utils::Dir;
using utils::Pt;

// clang-format off
constexpr int _ = INT_MAX;
constexpr Dir PUSH = Dir::SOUTH_WEST;
constexpr char width = 3;
constexpr char numpad[12] = {
    '7', '8', '9', 
    '4', '5', '6',
    '1', '2', '3',
    ' ', '0', 'A',
};
constexpr char keypad[6] = {
    ' ', '^', 'A', 
    '<', 'v', '>',
};
constexpr std::array<int,6>keypad_l = {
    _, 2, 3, 
    0, 1, 2,
};
constexpr std::array<int,6>keypad_r = {
    _, 2, 1, 
    3, 1, 0,
};
constexpr std::array<int,6>keypad_t = {
    _, 0, 1, 
    2, 1, 2,
};
constexpr std::array<int,6>keypad_b = {
    _, 1, 2, 
    1, 0, 1,
};
constexpr std::array<int,6> keypad_a = {
    _, 1, 0, 
    3, 2, 1,
};

enum KeypadButton {
    L='<',
    R='>',
    T='^',
    B='v',
    A='A',
};
// clang-format on

bool valid_keypad_pos(Pt const &pt) {
    return !pt.off_grid(3, 2) && !(pt.x == 2 && pt.y == 0);
}

std::array<int, 6> const &keypad_dists(KeypadButton to) {
    switch (to) {
    case L:
        return keypad_l;
    case R:
        return keypad_r;
    case T:
        return keypad_t;
    case B:
        return keypad_b;
    case A:
        return keypad_a;
    }
}

int keypad_dist(KeypadButton from, KeypadButton to) {
    if (from == to) return 0;
    if (from == '^') {
        switch (to) {
        case 'A':
        case 'v':
            return 1;
        case '<':
        case '>':
            return 2;
        case '^':
            return 0;
        };
    }

    if (from == '<') {
        switch (to) {
        case 'v':
            return 1;
        case '^':
        case '>':
            return 2;
        case 'A':
            return 3;
        case '<':
            return 0;
        };
    }

    if (from == '>') {
        switch (to) {
        case 'v':
        case 'A':
            return 1;
        case '^':
        case '<':
            return 2;
        case '>':
            return 0;
        };
    }

    if (from == 'A') {
        switch (to) {
        case '^':
        case '>':
            return 1;
        case 'v':
            return 2;
        case '<':
            return 3;
        case 'A':
            return 0;
        };
    }

    return 0;
}

Pt button_loc(KeypadButton button) {
    switch (button) {
    case L:
        return {0, 1};
    case R:
        return {2, 1};
    case T:
        return {1, 0};
    case B:
        return {1, 1};
    case A:
        return {2, 0};
    };
};

KeypadButton button_from_loc(Pt loc) {
    return (KeypadButton)keypad[loc.flat(3)];
}

KeypadButton dir_button(Dir dir) {
    switch (dir) {
    case utils::NORTH:
        return KeypadButton::B;
    case utils::EAST:
        return KeypadButton::R;
    case utils::SOUTH:
        return KeypadButton::T;
    case utils::WEST:
        return KeypadButton::L;
    case PUSH:
        return KeypadButton::A;
    default:
        throw "Invalid direction passed";
    }
}

void print_numpad(Pt &loc, bool pressing) {
    char arm1 = numpad[loc.flat(3)];
    auto a = [arm1, pressing](char ch) {
        return arm1 == ch ? pressing ? "# " : "^ " : "  ";
    };

    // clang-format off
    std::cout <<   "7 " <<   "8 "   << "9 " << std::endl;
    std::cout << a('7') << a('8') << a('9') << std::endl;

    std::cout <<   "4 " <<   "5 " <<   "6 " << std::endl;
    std::cout << a('4') << a('5') << a('6') << std::endl;

    std::cout <<   "1 " <<   "2 " <<   "3 " << std::endl;
    std::cout << a('1') << a('2') << a('3') << std::endl;

    std::cout <<   "  " <<   "0 " <<   "A " << std::endl;
    std::cout <<   "  " << a('0') << a('A') << std::endl;
    // clang-format on
}

void print_keypad(KeypadButton curr, bool pressing) {
    auto a = [curr, pressing](char ch) {
        return curr == ch ? pressing ? "# " : "^ " : "  ";
    };

    // clang-format off
    std::cout <<   "  " <<   "^ "   << "A " << std::endl;
    std::cout << a(' ') << a('^') << a('A') << std::endl;

    std::cout <<   "< " <<   "v " <<   "> " << std::endl;
    std::cout << a('<') << a('v') << a('>') << std::endl;
    // clang-format on
}

struct KeypadPaths {
    std::vector<KeypadButton> p1 = {};
    std::vector<KeypadButton> p2 = {};
    std::vector<KeypadButton> p3 = {};

    std::vector<KeypadButton> &of(int level) {
        switch (level) {
        case 1:
            return p1;
        case 2:
            return p2;
        case 3:
            return p3;
        default:
            throw "invalid level";
        }
    }

    void append(KeypadPaths &paths) {
        for (int i = 1; i <= 3; i++) {
            append(paths.of(i), i);
        }
    }

    void append(std::vector<KeypadButton> &paths, int level) {
        std::vector<KeypadButton> &target = of(level);
        target.insert(target.end(), paths.begin(), paths.end());
    }

    void push_back(KeypadButton button, int level) {
        of(level).push_back(button);
    }

    void print() {
        for (int i = 1; i <= 3; i++) {
            for (KeypadButton move : of(i)) {
                std::cout << char(move);
            }
            std::cout << " (" << of(i).size() << ")" << std::endl;
        }
        std::cout << std::endl;
    }
};

struct KeypadState {
    KeypadButton b1 = KeypadButton::A;
    KeypadButton b2 = KeypadButton::A;
    KeypadButton b3 = KeypadButton::A;

    KeypadButton *of(int level) {
        switch (level) {
        case 1:
            return &b1;
        case 2:
            return &b2;
        case 3:
            return &b3;
        default:
            throw "invalid level";
        }
    }

    void update(KeypadPaths &paths) {
        for (int i = 1; i <= 3; i++) {
            auto path = paths.of(i);
            if (path.empty()) continue;
            *of(i) = path.back();
        }
    }
};

KeypadPaths expand(KeypadButton next, KeypadState& state, int level = 1) {
    constexpr Dir NO_DIR = PUSH;
    KeypadPaths expanded = {};
    std::array<int, 6> dists = keypad_dists(next);

    if (level == 1) std::cout << char(state.b1) << std::endl;

    while (*state.of(level) != next) {
        Pt curr = button_loc(*state.of(level));
        int curr_dist = dists[curr.flat(3)];
        Dir best_dir = NO_DIR;
        KeypadPaths best_paths = {};

        for (Dir dir : utils::directions_cartesian) {
            Pt next = curr + utils::dir_offset(dir);
            if (next.off_grid(3, 2) || dists[next.flat(3)] >= curr_dist) {
                continue;
            }

            if (level == 3) {
                best_dir = dir;
                break;
            }

            auto paths = expand(button_from_loc(next), state, level + 1);
            if (best_dir == NO_DIR ||
                paths.of(level + 1).size() < best_paths.of(level + 1).size()) {
                best_dir = dir;
                best_paths = paths;
            }
        }

        if (best_dir == NO_DIR) break;
        // std::cout << curr.to_string() << std::endl;
        // std::cout << char(dir_button(best_dir)) << std::endl;
        // utils::wait_for_input();

        auto next = curr + utils::dir_offset(best_dir);
        expanded.append(best_paths);
        expanded.push_back(dir_button(best_dir), level);

        // if (level == 1) {
        //     std::cout << char(dir_button(best_dir)) << std::endl;
        //     std::cout << char(state.b1) << " " << char(state.b2) << " "
        //               << char(state.b3) << std::endl;
        //     expanded.print();
        //     utils::wait_for_input();
        // }

        *state.of(level) = button_from_loc(next);
        // state.update(expanded);
    }

    if (level < 3) {
        auto press_path = expand(KeypadButton::A, state, level + 1);
        expanded.append(press_path);
    } else {
        expanded.push_back(KeypadButton::A, level);
    }


    return expanded;
}

KeypadPaths get_path(KeypadState &state, char from, char to) {
    Pt from_pt;
    Pt to_pt;
    for (int i = 0; i < 12; i++) {
        if (numpad[i] == from) from_pt = Pt::from_index(i, 3);
        if (numpad[i] == to) to_pt = Pt::from_index(i, 3);
    }

    // std::cout << char(from) << " " << from_pt.to_string() << std::endl;

    Pt curr_pt = from_pt;
    auto moves = std::vector<std::tuple<Pt, KeypadButton>>();
    KeypadPaths big_path = {};

    while (curr_pt.hash() != to_pt.hash()) {
        int dist = utils::manhattan(curr_pt, to_pt);
        auto valid_dirs = std::vector<Dir>();
        for (Dir dir : utils::directions_cartesian) {
            Pt next = curr_pt + utils::dir_offset(dir);
            if (next.off_grid(3, 4) || numpad[next.flat(3)] == ' ' ||
                utils::manhattan(next, to_pt) >= dist) {
                continue;
            }

            valid_dirs.push_back(dir);
            break;
        }

        if (valid_dirs.empty()) continue;

        Dir best_dir = PUSH;
        KeypadPaths best_paths = {};
        for (Dir dir : valid_dirs) {
            KeypadButton button = dir_button(dir);
            auto path = expand(button, state);
            if (best_dir == PUSH ||
                path.of(3).size() < best_paths.of(3).size()) {
                best_paths = path;
                best_dir = dir;
            }
        }

        std::cout << curr_pt.to_string() << " " << best_dir << std::endl;
        Pt next = curr_pt + utils::dir_offset(best_dir);
        big_path.append(best_paths);
        state.update(big_path);
        curr_pt = next;

        // print_numpad(curr_pt, false);
        // std::cout << "____________" << std::endl;
        // print_keypad(state.b1, false);
        // std::cout << "____________" << std::endl;
        // print_keypad(state.b2, false);
        // std::cout << "____________" << std::endl;
        // print_keypad(state.b3, false);
        // utils::wait_for_input();
    }

    return big_path;
}

int run(std::vector<std::string> &lines, bool is_part1) {
    int total = 0;

    KeypadState state = {};

    for (auto line : lines) {
        char curr = 'A';
        KeypadPaths paths = {};
        auto numpad_locs = std::vector<Pt>();
        for (char next : line) {
            auto path = get_path(state, curr, next);
            paths.append(path);
            curr = next;
        }

        std::cout << line << std::endl;
        paths.print();
        std::cout << paths.of(3).size() << std::endl << std::endl;
        total += paths.of(3).size() * std::stoi(line.substr(0, 3));
    }

    std::cout << total << std::endl;

    return total;
}
} // namespace day_21
