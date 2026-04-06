#include <iostream>
#include <vector>
using namespace std;

int main() {
    while(true) {
        vector<double> numbers;
        int n;
        // Ask how many numbers to track
        cout << "How many numbers? \n";
        if (!(cin >> n)) {
            cout << "Error: Enter an integer.\n";
            cin.clear();
            cin.ignore(10000, '\n'); 
            continue; 
        }

        if(n <= 0) {
            cout << "Enter a positive number of values.\n";
            continue;
        }
            
        for (int i = 0; i < n; i++) {
            double value;
            cout << "Enter number " << i+1 << ": ";
            if(!(cin >> value)) {
                cout << "Error: Enter a valid number";
                cin.clear();
                cin.ignore(10000, '\n');
                i--;
                continue;
            }
            numbers.push_back(value);
        }
        // Check the numbers after all are inputted and return the maxValue
        double maxValue = numbers[0];
        for (double num : numbers) {
            if (num > maxValue) {
                maxValue = num;
            }
        }

        cout << "Maximum number: " << maxValue << "\n";

        char again;
        cout << "Continue? y/n\n";
        cin >> again;
        if(again != 'y') {
            break;
        } 
    }

    return 0;
}