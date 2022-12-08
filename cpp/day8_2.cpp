#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<string> grid;
    string line;
    while (cin >> line) grid.push_back(line);
    int height = grid.size();
    int width = grid[0].size();

    int res = 0;

    for (int i = 1; i < height - 1; i++) {
        for(int j = 1; j < width - 1; j++) {
            char value = grid[i][j];
            int left = 1, right = 1, top = 1, bottom = 1;

            for (int k = j-1; k > 0 && grid[i][k] < value; k--) left++;
            for (int k = j+1; k < width-1 && grid[i][k] < value; k++) right++;
            for (int k = i-1; k > 0 && grid[k][j] < value; k--) top++;
            for (int k = i+1; k < height-1 && grid[k][j] < value; k++) bottom++;

            res = max(res, left*right*top*bottom);
        }
    }

    cout << res << endl;

    return 0;
}