#include <iostream>
#include <string>

using namespace std;

int main() {
    string line;
    int score = 0;
    while (getline(cin, line)) {
        char opp_choice = line[0] - 'A' + 3; // 3, 4 or 5
        // -1, 0 or 1 for the delta, add it to the opponent choice
        // + 3 then % 3 to get rid of negative values and have values in {0,1,2}
        char choice = (opp_choice + line[2] - 'Y') % 3;
        score += choice +1; // Score from played selection
        // choice - opp_choice : 4 if tie, 3 or 6 if loss, 2 or 5 if win
        // mod 3 : 1 if tie, 0 if loss, 2 if win
        score += 3 * (line[2] - 'X');
    }
    cout << score << endl;

    return 0;
}