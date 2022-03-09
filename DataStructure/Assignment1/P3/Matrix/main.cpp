#include "Matrix.h"

void menu();
void Addition();
void Subtraction();
void Multiplication();
void Transpose();

int main() {

    cout<<"Welcome to MX Matrix Calculator\n";
    int choice = -1;
    while (choice != 5){
        menu();
        cin>>choice;
        switch (choice) {
            case 1:
                Addition();
                break;


            case 2:
                Subtraction();
                break;
            case 3:
                Multiplication();
                break;
                case 4:
                    Transpose();
                break;

                default:
                    break;
    }


    }
    return  0;
}



