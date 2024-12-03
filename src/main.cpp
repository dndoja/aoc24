#include <fstream>
#include <iostream>
#include <string>

#include "day_1.cpp"
#include "day_2.cpp"
#include "day_3.cpp"

using namespace std;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        cout << "error: no day number passed!\n";
        return 1;
    }

    int day_nr = atoi(argv[1]);
    bool isPart1 = true;
    if (argc > 2) isPart1 = strcmp(argv[2], "b") != 0;

    bool test_file = false;
    if (argc > 3) test_file = strcmp(argv[3], "test") == 0;

    string filename =
        "data/day" + to_string(day_nr) + (test_file ? "_test.txt" : ".txt");
    ifstream file(filename);
    vector<string> lines = vector<string>();
    string curr_line;
    while (getline(file, curr_line)) {
        lines.push_back(curr_line);
    }

    int result;
    switch (day_nr) {
    case 1:
        result = day_1::run(lines, isPart1);
        break;
    case 2:
        result = day_2::run(lines, isPart1);
        break;
    case 3:
        result = day_3::run(lines, isPart1);
        break;
    default:
        cout << "error: not implemented yet!\n";
        return 1;
    }

    cout << "Result: " << result << "\n";

    return 0;
}
