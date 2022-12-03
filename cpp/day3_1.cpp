#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
    int score = 0;
    string line;
    while (cin >> line) {
        vector<char> res;
        auto middle = line.begin() + line.size() / 2;
        sort(line.begin(), middle);
        sort(middle, line.end());
        set_intersection(line.begin(), middle, middle, line.end(), back_inserter(res));
        char common = res[0];
        if (common > 'Z') {
            // 1..26
            score += common - 'a' + 1;
        } else {
            // 27..52
            score += common - 'A' + 27;
        }
    }
    cout << score << endl;

    return 0;
}