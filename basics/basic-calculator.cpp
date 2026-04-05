#include <iostream>
using namespace std;
int main() {
    while(true) {
        double num1, num2;
        string op;
        cout << "Enter first number: ";
        cin >> num1;
        cout << "Enter operator (+, -, *, /): ";
        cin >> op;
        if(op.length() != 1) {
            cout << "Error: Invalid operator\n";
            continue;
        }

        cout << "Enter second number: ";
        cin >> num2;

        double result = 0;
        bool valid = true;
        switch (op[0]) {
            default:
                cout << "Error: Invalid response\n";
                valid = false;
                break;
            case '+':
                result = num1 + num2;
                break;
            case '-':
                result = num1 - num2;
                break;
            case '*':
                result = num1 * num2;
                break;
            case '/':
                if (num2 == 0) {
                    cout << "Error: Cannot divide by 0\n";
                    valid = false;
                } else {
                    result = num1 / num2;
                }
                break;     
        }
        if (valid) {
            cout << "Result: " << result << "\n";
        }

        char again;
        cout << "Continue? (y/n): ";
        cin >> again;
        if (again != 'y') {
            break;
        }
    }

    return 0;

}