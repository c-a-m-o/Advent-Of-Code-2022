#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    string line;
    int current_sum = 0;
    vector<int> sums;
    while (getline(cin, line)) {
        if (line == "") {
            sums.push_back(current_sum);
            current_sum = 0;
        } else {
            current_sum += atoi(line.c_str());
        }
    }

    sort(sums.begin(), sums.end());
    int length = sums.size();
    cout << sums[length - 3] + sums[length - 2] + sums[length - 1] << endl;

    return 0;
}