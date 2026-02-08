#include <iostream>

using std::cout;
using std::cin;
using std::endl;

int main(){
    int number1{0};
    int number2{0};

cout << "Enter the two integer numbers to compare: ";
cin >> number1 >> number2; //read two integers from the user
    if (number1 == number2) {
        cout << number1 << " ==" << number2 << endl;
    } //if statement to check if the two numbers are equal

    if (number1 != number2) {
        cout << number1 << " !=" << number2 << endl;
    }// if statement to check if the two numbers are not equal
    if (number1 > number2) {
        cout << number1 << " > " << number2 << endl;    
    } // if statement to check if the first number is greater than the second number
    if (number1 < number2) {
        cout << number1 << " < " << number2 << endl;
    }// if statement to check if the first number is less than the second number
    if (number1 >= number2) {
        cout << number1 << " >= " << number2 << endl;    
    }// if statement to check if the first number is greater than or equal to the second number
    if (number1 <= number2) {
        cout << number1 << " <= " << number2 << endl;
    } // if statement to check if the first number is less than or equal to the second number
}
