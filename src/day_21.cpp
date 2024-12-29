#include "utils.h"
#include <_types/_uint64_t.h>
#include <climits>
#include <iostream>
#include <queue>
#include <unordered_set>

namespace day_21 {
using utils::Dir;
using utils::Pt;

// clang-format off
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

enum KeypadButton {
    L='<',
    R='>',
    T='^',
    B='v',
    A='A',
};
// clang-format on

bool valid_numpad_pos(Pt const &pt) {
    return !pt.off_grid(3, 4) && !(pt.x == 0 && pt.y == 3);
}

bool valid_keypad_pos(Pt const &pt) {
    return !pt.off_grid(3, 2) && !(pt.x == 0 && pt.y == 0);
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

    if (from == 'v') {
        switch (to) {
        case '^':
        case '<':
        case '>':
            return 1;
        case 'A':
            return 2;
        case 'v':
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

Pt button_offset(KeypadButton button) {
    switch (button) {
    case L:
        return {-1, 0};
    case R:
        return {1, 0};
    case T:
        return {0, -1};
    case B:
        return {0, 1};
    case A:
        return {0, 0};
    };
}

Pt numpad_loc(char ch) {
    switch (ch) {
    case 'A':
        return {2, 3};
    case '0':
        return {1, 3};
    case '1':
        return {0, 2};
    case '2':
        return {1, 2};
    case '3':
        return {2, 2};
    case '4':
        return {0, 1};
    case '5':
        return {1, 1};
    case '6':
        return {2, 1};
    case '7':
        return {0, 0};
    case '8':
        return {1, 0};
    case '9':
        return {2, 0};
    default:
        throw std::invalid_argument("Invalid Char");
    }
}

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
    default:
        throw std::invalid_argument("Invalid direction passed");
    }
}

void print_numpad(Pt &loc, bool pressing) {
    char arm1 = numpad[loc.flat(3)];
    auto a = [arm1, pressing](char ch) {
        return arm1 == ch ? pressing ? "# " : "* " : "  ";
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
        return curr == ch ? pressing ? "# " : "* " : "  ";
    };

    // clang-format off
    std::cout <<   "  " <<   "^ "   << "A " << std::endl;
    std::cout << a(' ') << a('^') << a('A') << std::endl;

    std::cout <<   "< " <<   "v " <<   "> " << std::endl;
    std::cout << a('<') << a('v') << a('>') << std::endl;
    // clang-format on
}

struct State {
    int score = 0;
    bool pressed_numpad = false;
    Pt numpad_curr = {2, 3};
    Pt numpad_goal = {2, 3};
    KeypadButton lvl1_curr = KeypadButton::A;
    KeypadButton lvl2_curr = KeypadButton::A;

    int hash() {
        int hash = 0;
        hash |= lvl1_curr;
        hash |= lvl2_curr << 8;
        hash |= numpad_curr.flat(3) << 16;
        hash |= pressed_numpad << 20;
        return hash;
    };

    bool numpad_on_target() {
        return !pressed_numpad && numpad_curr.hash() == numpad_goal.hash();
    };

    void print() {
        print_numpad(numpad_curr, pressed_numpad);
        std::cout << "_________" << std::endl << std::endl;
        print_keypad(lvl1_curr, false);
        std::cout << "_________" << std::endl << std::endl;
        print_keypad(lvl2_curr, false);
    }

    KeypadButton curr_btn(int level) {
        switch (level) {
        case 1:
            return lvl1_curr;
        case 2:
            return lvl2_curr;
        default:
            throw std::invalid_argument("Invalid number: " +
                                        std::to_string(level));
        }
    }

    void set_curr_btn(int level, KeypadButton button) {
        switch (level) {
        case 1:
            lvl1_curr = button;
            break;
        case 2:
            lvl2_curr = button;
            break;
        }
    }

    State *move(utils::DynamicArena<State> &arena, int level, KeypadButton by) {
        State *new_state = arena.make({*this});
        Pt new_loc = button_loc(curr_btn(level)) + button_offset(by);
        new_state->set_curr_btn(level, button_from_loc(new_loc));
        new_state->score++;
        return new_state;
    }

    State *press(utils::DynamicArena<State> &arena, int level = 3) {
        if (level == 3) return press(arena, level - 1);

        if (level == 0) {
            if (!numpad_on_target()) {
                throw std::invalid_argument("Numpad misfire!");
            }

            State *new_state = arena.make(*this);
            new_state->pressed_numpad = true;
            new_state->score++;
            return new_state;
        }

        KeypadButton btn = curr_btn(level);

        if (btn == KeypadButton::A) return press(arena, level - 1);

        State *new_state = arena.make(*this);

        if (level == 1) {
            new_state->numpad_curr = numpad_curr + button_offset(btn);
        } else {
            auto new_loc = button_loc(curr_btn(level - 1)) + button_offset(btn);
            new_state->set_curr_btn(level - 1, button_from_loc(new_loc));
        }

        new_state->score++;
        return new_state;
    }

    /*
        7 8 9
        4 5 6
        3 2 1
          0 A


          ^ A    1
        < v >
            *


          ^ A    2
        < v >
        *


          ^ A    3
        < v >
    */
    std::vector<KeypadButton> get_candidates(int level = 3) {
        if (level == 3) return get_candidates(level - 1);

        if (level == 0) {
            if (numpad_on_target()) return {A};

            int dist_to_goal = utils::manhattan(numpad_curr, numpad_goal);
            std::vector<KeypadButton> intents = {};

            for (Dir dir : utils::directions_cartesian) {
                Pt next = numpad_curr + utils::dir_offset(dir);
                if (!valid_numpad_pos(next)) continue;

                if (utils::manhattan(next, numpad_goal) < dist_to_goal) {
                    intents.push_back(dir_button(dir));
                }
            }

            return intents;
        }

        KeypadButton curr = curr_btn(level);
        Pt curr_loc = button_loc(curr);
        std::vector<KeypadButton> child_candidates = get_candidates(level - 1);
        std::vector<KeypadButton> candidates = {};

        for (KeypadButton child : child_candidates) {
            int dist_to_child = keypad_dist(curr, child);
            if (dist_to_child == 0) {
                candidates.push_back(A);
                continue;
            }

            for (Dir dir : utils::directions_cartesian) {
                Pt next = curr_loc + utils::dir_offset(dir);
                if (!valid_keypad_pos(next)) continue;

                int dist = keypad_dist(button_from_loc(next), child);
                if (dist < dist_to_child) {
                    candidates.push_back(dir_button(dir));
                }
            }
        }

        return candidates;
    }
};

struct StateCmp {
    bool operator()(State const *a, State const *b) {
        return a->score > b->score;
    }
};

int get_op_count(std::array<char, 4> const &numpad_goals) {
    State state = {};
    auto arena = utils::DynamicArena<State>(20000);

    for (int i = 0; i < 4; i++) {
        state.numpad_goal = numpad_loc(numpad_goals[i]);
        state.pressed_numpad = false;

        std::priority_queue<State *, std::vector<State *>, StateCmp> queue = {};
        std::unordered_set<int> visited = {};
        std::unordered_map<int, int> scores = {};
        queue.push(&state);

        while (!queue.empty()) {
            State *curr = queue.top();
            queue.pop();

            if (visited.contains(curr->hash())) continue;
            visited.insert(curr->hash());

            // system("clear");
            // curr->print();

            if (curr->pressed_numpad) {
                state = *curr;
                break;
            }

            auto candidates = curr->get_candidates();
            for (KeypadButton candidate : candidates) {
                State *next;
                if (candidate == KeypadButton::A) {
                    next = curr->press(arena);
                } else {
                    next = curr->move(arena, 2, candidate);
                }

                auto prev_score = scores.find(next->hash());
                if (prev_score == scores.end() ||
                    next->score < prev_score->second) {
                    queue.push(next);
                    scores[next->hash()] = next->score;
                }
            }

            // utils::wait_for_input();
        }
    }

    return state.score;
}

int run(std::vector<std::string> &lines, bool is_part1) {
    int total = 0;

    for (auto line : lines) {
        int count = get_op_count({line[0], line[1], line[2], line[3]});
        total += count * std::stoi(line.substr(0, 3));
        std::cout << count << std::endl;
    }

    return total;
}
} // namespace day_21
