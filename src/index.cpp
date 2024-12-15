// clang-format off
#include "day_1.cpp"
#include "day_2.cpp"
#include "day_3.cpp"
#include "day_4.cpp"
#include "day_5.cpp"
#include "day_6.cpp"
#include "day_7.cpp"
#include "day_8.cpp"
#include "day_9.cpp"
#include "day_10.cpp"
#include "day_11.cpp"
#include "day_12.cpp"
#include "day_13.cpp"
#include "day_14.cpp"

std::string run_day(int day_nr, std::vector<std::string> &lines, bool isPart1) {
    switch (day_nr) {
    case  1: return std::to_string(day_1::run(lines, isPart1));
    case  2: return std::to_string(day_2::run(lines, isPart1));
    case  3: return std::to_string(day_3::run(lines, isPart1));
    case  4: return std::to_string(day_4::run(lines, isPart1));
    case  5: return std::to_string(day_5::run(lines, isPart1));
    case  6: return std::to_string(day_6::run(lines, isPart1));
    case  7: return std::to_string(day_7::run(lines, isPart1));
    case  8: return std::to_string(day_8::run(lines, isPart1));
    case  9: return std::to_string(day_9::run(lines, isPart1));
    case 10: return std::to_string(day_10::run(lines, isPart1));
    case 11: return std::to_string(day_11::run(lines, isPart1));
    case 12: return std::to_string(day_12::run(lines, isPart1));
    case 13: return std::to_string(day_13::run(lines, isPart1));
    case 14: return std::to_string(day_14::run(lines, isPart1));
    default:
        return "error: not implemented yet!\n";
    }
}
