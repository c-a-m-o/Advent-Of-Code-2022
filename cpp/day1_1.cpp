#include <iostream>
#include <string>
using namespace std;

int main() {
    string line;
    int current_sum = 0;
    int best_sum = 0;
    while (getline(cin, line)) {
        if (line == "") {
            best_sum = max(best_sum, current_sum);
            current_sum = 0;
        } else {
            current_sum += atoi(line.c_str());
        }
    }

    cout << best_sum << endl;
    return 0;
}