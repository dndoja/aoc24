#include <fstream>
#include <iostream>
#include <string>

#include "index.cpp"

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

    std::string result = run_day(day_nr, lines, isPart1);
    cout << "Result: " << result << "\n";

    return 0;
}
