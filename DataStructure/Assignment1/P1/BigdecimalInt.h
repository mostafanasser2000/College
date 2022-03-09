#include <iostream>
#include <vector>
#include <string>
#include <deque>
#ifndef P1_BIGDECIMALINT_H
#define P1_BIGDECIMALINT_H


using namespace std;

class BigdecimalInt {
private:
    deque<int>number;

    char signOfNumber;
    char resultSign;

    int whoIsBigger(deque<int>&v1, deque<int>&v2);
    deque<int> sum(deque<int>&v1, deque<int>&v2);
    deque<int> subtract(deque<int>&v1, deque<int>&v2);

public:

    BigdecimalInt(string );
    BigdecimalInt(int  );
    BigdecimalInt operator +( BigdecimalInt& );
    BigdecimalInt operator -( BigdecimalInt& );
    BigdecimalInt operator = (const BigdecimalInt& );
    int getNumberLength()const;
    friend ostream& operator <<(ostream& output , const BigdecimalInt& obj);
};




#endif //P1_BIGDECIMALINT_H
