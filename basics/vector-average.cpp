#include <iostream>
#include <vector>
using namespace std;

int main() {
    while(true) {
        vector<double> numbers;
        int n;

        cout << "How many numbers? \n";
        if (!(cin >> n)) {
                cout << "Error: Enter an integer.\n";
                cin.clear();
                cin.ignore(10000, '\n');
                continue;
        }

        if(n <= 0) {
            cout << "Please enter a postive integer greater than 0.\n";
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

        double sum = 0;
        for (double num : numbers) {
            sum += num;
        }

        double average = sum / numbers.size();

        cout << "Average is " << average << "\n";

        char again;
        cout << "Continue? y/n\n";
        cin >> again;
        if(again != 'y') {
            break;
        }        

    }  

    return 0;
}