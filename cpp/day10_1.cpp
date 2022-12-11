#include <iostream>
#include <string>

using namespace std;

int main() {

    string inp;
    int cycle = 0;
    int x = 1;
    int res = 0;

    while (cin >> inp) {
        cycle++;
        if (cycle % 40 == 20) res += cycle * x;
        try {
            int val = stoi(inp);
            x += val;
        } catch (invalid_argument &e) {}
    }

    cout << res << endl;

    return 0;
}