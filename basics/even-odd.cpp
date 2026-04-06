#include <iostream>
using namespace std;

int main() {
    while(true) {
        int num;
        cout << "Enter a number to determine if it's Even/Odd\n";        
        if (!(cin >> num)) {
            cout << "Error: Enter an integer.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        if (num % 2 == 0) {
            cout << num << " is an EVEN number\n";
        } else {
            cout << num << " is an ODD number\n";
        }

        char again;
        cout << "Continue? y/n\n";
        cin >> again;
        if(again != 'y') {
            break;
        }
    } 

    return 0;
}