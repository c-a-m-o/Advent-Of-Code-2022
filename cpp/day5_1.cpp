#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdio.h>

using namespace std;

int main() {

    string line;

    vector<vector<char>> piles;
    // Piles
    while(getline(cin, line)) {
        // End of the piles
        if (line[1] == '1') break;
        // Init
        if (piles.size() == 0) for (int i = (line.size()+1 / 4); i > 0; i--) piles.push_back(vector<char>());
        // Append the crate on top
        for(int i = 1; i < piles.size(); i += 4) 
            if (line[i] != ' ') piles[i/4].push_back(line[i]);
    }
    // Blank line
    getline(cin, line);
    // Reverse the piles
    for (auto& v: piles) reverse(v.begin(), v.end());

    // Instructions
    int qty, from, to;
    while(cin >> line >> qty >> line >> from >> line >> to) {
        // 1-based index to 0-based index
        from--;
        to--;
        // qty times, move the top pile of from to to
        while (qty--) {
            piles[to].push_back(piles[from].back());
            piles[from].pop_back();
        }
    }

    for (auto& v: piles) cout << v.back();
    cout << endl;

    return 0;
}