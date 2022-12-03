#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
    int score = 0;
    string first, second, third;
    while (cin >> first >> second >> third) {
        vector<char> temp;
        vector<char> res;
        sort(first.begin(), first.end());
        sort(second.begin(), second.end());
        sort(third.begin(), third.end());

        set_intersection(first.begin(), first.end(), second.begin(), second.end(), back_inserter(temp));
        set_intersection(temp.begin(), temp.end(), third.begin(), third.end(), back_inserter(res));
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