#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<string> grid;
    string line;
    while (cin >> line) grid.push_back(line);
    int height = grid.size();
    int width = grid[0].size();

    vector<vector<bool>> visible(height, vector<bool>(width, false));

    int res = 0;

    for (int j = 0; j < height; j++){
        int i = 0;
        // From the left
        char max_height = 0;
        while(i < width) {
            char height = grid[j][i];
            if (height > max_height) {
                max_height = height;
                res += !visible[j][i];
                visible[j][i] = true;
            }
            i++;
        }
        // From the right
        max_height = 0;
        while(i--) {
            char height = grid[j][i];
            if (height > max_height) {
                max_height = height;
                res += !visible[j][i];
                visible[j][i] = true;
            }
        }
    }

    for (int i = 0; i < width; i++){
        int j = 0;
        // From the left
        char max_height = 0;
        while(j < width) {
            char height = grid[j][i];
            if (height > max_height) {
                max_height = height;
                res += !visible[j][i];
                visible[j][i] = true;
            }
            j++;
        }
        // From the right
        max_height = 0;
        while(j--) {
            char height = grid[j][i];
            if (height > max_height) {
                max_height = height;
                res += !visible[j][i];
                visible[j][i] = true;
            }
        }
    }

    // for(auto l: visible) {
    //     for (auto x : l) cout << (x? 'x': ' ');
    //     cout << endl;
    // }

    cout << res << endl;

    return 0;
}