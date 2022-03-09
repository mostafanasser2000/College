#include <iostream>
#include <string>
#include "BigdecimalInt.h"
using namespace std;
int main() {
    cout<<"Welcome to FCI Calculator\n"
          "----------------------------------------\n"
          "1- Perform Addition\n"
          "2- Perform Subtraction\n"
          "3- Exit\n";
    int choice ;
    cout<<">>";
    cin>>choice;
    string n1,n2;

    if(choice == 3)
    {
        exit(0);
    }
    try{
        cout<<">>";
        cin>>n1;
        BigdecimalInt num1(n1);
        cout<<"num1 = "<<n1<<"\n";

        cout<<">>";
        cin>>n2;
        BigdecimalInt num2(n2);
        cout<<"num2 = "<<n2<<"\n";
        BigdecimalInt result(0);

        if(choice == 1)
        {
            result = num1 + num2;
            cout<<"num1 + num2 = "<<result;
        }
       else if(choice == 2)
        {
            result = num1 - num2;
            cout<<"num1 - num2 = "<<result;
        }


    }
    catch (const char *msg)
    {
        cout<<"Error: "<<msg<<"\n";
    }

    return 0;
}
