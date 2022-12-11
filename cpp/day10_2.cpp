#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {

    string inp;
    int cycle = 0;
    int x = 1;
    vector<string> sprite(6, string(40, ' '));

    while (cin >> inp) {
        int xpos = cycle % 40;
        int ypos = cycle / 40;
        if (abs(x - xpos) < 2) sprite[ypos][xpos] = '#';

        cycle++;
        try {
            int val = stoi(inp);
            x += val;
        } catch (invalid_argument &e) {}
    }

    for (string& s: sprite) cout << s << endl;

    return 0;
}