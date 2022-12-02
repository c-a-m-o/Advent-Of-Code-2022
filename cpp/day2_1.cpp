#include <iostream>
#include <string>

using namespace std;

int main() {
    string line;
    int score = 0;
    while (getline(cin, line)) {
        char choice = line[2] - 'X' + 4; // 4, 5 or 6
        char opp_choice = line[0] - 'A'; // 0, 1 or 2
        score += choice - 3; // Score from played selection
        // choice - opp_choice : 4 if tie, 3 or 6 if loss, 2 or 5 if win
        // mod 3 : 1 if tie, 0 if loss, 2 if win
        score += 3 * ((choice - opp_choice) % 3);
        cout << score << " " << (int)choice << " " << (int)opp_choice << endl;
    }
    cout << score << endl;

    return 0;
}