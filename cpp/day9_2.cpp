#include <iostream>
#include <set>
#include <vector>

using namespace std;

int main() {
    int x = 0;
    int y = 0;
    int tx[9] = {0};
    int ty[9] = {0};

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
                dy = -1;
                break;
            case 'D':
                dy = 1;
                break;
        }

        for (int i = 0; i < amount; i++) {
            x += dx;
            y += dy;

            int last_x = x;
            int last_y = y;
            for (int j = 0; j < 9; j++) {
                int dx2 = 0;
                int dy2 = 0;
                if (tx[j] < last_x - 1) dx2 = 1;
                if (tx[j] > last_x + 1) dx2 = -1;
                if (ty[j] < last_y - 1) dy2 = 1;
                if (ty[j] > last_y + 1) dy2= -1;
                if (dx2 && !dy2) {tx[j] += dx2; ty[j] = last_y;}
                else if (dy2 && !dx2) {tx[j] = last_x; ty[j] += dy2;}
                else {tx[j] += dx2; ty[j] += dy2;}
                last_x = tx[j];
                last_y = ty[j];
            }
            visited.insert(make_pair(tx[8], ty[8]));
        

        // int minx = x;
        // int maxx = x;
        // int miny = y;
        // int maxy = y;
        // for (auto posx: tx) {
        //     minx = min(minx, posx);
        //     maxx = max(maxx, posx);
        // }
        // for (auto posy: ty) {
        //     miny = min(miny, posy);
        //     maxy = max(maxy, posy);
        // }
        // cout << minx << " " << maxx << " " << miny << " " << maxy << endl;
        // vector<vector<char>> map(maxy-miny+1, vector<char>(maxx-minx+1, '.'));
        // for (int i = 9; i >= 0; i--) map[ty[i]-miny][tx[i]-minx] = '1' + i;
        // map[y-miny][x-minx] = 'H';
        // for (auto l: map) {
        //     for (auto c: l) cout << c;
        //     cout << endl;
        // }
        // cout << endl;
        }
    }

    // for (auto p: visited) cout << p.first << " " << p.second << endl;
    cout << visited.size() << endl;

    return 0;
}