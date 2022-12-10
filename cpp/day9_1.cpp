#include <iostream>
#include <set>

using namespace std;

int main() {
    int x = 0;
    int y = 0;
    int tx = 0;
    int ty = 0;

    set<pair<int, int>> visited = {{0, 0}};

    string direction;
    int amount;

    while (cin >> direction >> amount) {
        int dx = 0;
        int dy = 0;
        switch (direction[0]) {
            case 'L':
                dx = -1;
                break;
            case 'R':
                dx = 1;
                break;
            case 'U':
                dy = 1;
                break;
            case 'D':
                dy = -1;
                break;
        }

        for (int i = 0; i < amount; i++) {
            x += dx;
            y += dy;
            if (tx < x - 1) {tx++; ty = y;}
            if (tx > x + 1) {tx--; ty = y;}
            if (ty < y - 1) {ty++; tx = x;}
            if (ty > y + 1) {ty--; tx = x;}
            visited.insert(make_pair(tx, ty));
        }
    }

    // for (auto p: visited) cout << p.first << " " << p.second << endl;
    cout << visited.size() << endl;

    return 0;
}