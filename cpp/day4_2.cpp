#include <stdio.h>
#include <iostream>
using namespace std;

int main() {

    int l1, r1, l2, r2;
    int count = 0;
    while (scanf("%d-%d,%d-%d", &l1, &r1, &l2, &r2) != -1) {
        count += ((l1 <= l2 && r1 >= l2) || (l2 <= l1 && r2 >= l1));
    }
    cout << count << endl;

    return 0;
}