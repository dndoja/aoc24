// clang-format off
#include "day_1.cpp"
#include "day_2.cpp"
#include "day_3.cpp"
#include "day_4.cpp"
#include "day_5.cpp"
#include "day_6.cpp"
#include "day_7.cpp"

int run_day(int day_nr, std::vector<std::string> &lines, bool isPart1) {
    switch (day_nr) {
    case 1: return day_1::run(lines, isPart1);
    case 2: return day_2::run(lines, isPart1);
    case 3: return day_3::run(lines, isPart1);
    case 4: return day_4::run(lines, isPart1);
    case 5: return day_5::run(lines, isPart1);
    case 6: return day_6::run(lines, isPart1);
    case 7: return day_7::run(lines, isPart1);
    default:
        std::cout << "error: not implemented yet!\n";
        return 1;
    }
}
