#include <iostream>

using namespace std;

int main(int argc, char* argv[]){
    if (argc < 2) {
        cout << "error: no day number passed!\n";
        return 1;
    }

    int day_nr = atoi(argv[1]);
    cout << day_nr << "\n";

    return 0;
}
