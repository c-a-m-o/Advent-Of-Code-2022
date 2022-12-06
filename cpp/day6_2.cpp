#include <iostream>
using namespace std;

int main() {

    string input;
    cin >> input;
    int array[26] = {0};

    int diff = 0;
    int i = 0;

    while(diff != 14) {
        int index = input[i]- 'a';
        if (!array[index]++) diff++;
        if (i > 13) {
            diff -= --array[input[i-14] - 'a'] == 0;
        }
        i++;
    }

    cout << i << endl;

    return 0;
}