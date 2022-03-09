#include "BigdecimalInt.h"
#include <algorithm>

// Parametrized Constructor taken number as string
BigdecimalInt::BigdecimalInt(string bigNumber){
   // default number is positive
    signOfNumber = '+';
    resultSign = '+';
    // if number is negative
    if(bigNumber[0] == '-')
    {
        signOfNumber = '-';
    }

    // check if number is contain any invalid symbol
    for(int i = 1, n = bigNumber.size(); i < n; ++i){
        if(!isdigit(bigNumber[i])){
            throw "Invalid Number";
        }
    }


    // reverse string
    reverse(bigNumber.begin(),bigNumber.end());

    // remove - sign if number is negative
    if(signOfNumber == '-')
    {
        bigNumber.pop_back();
    }

    // store number in a container to do summation or subtraction
    for(int i = 0, n = bigNumber.size(); i < n; ++i){
        number.push_back(bigNumber[i] - '0');
    }
}
// Parametrized Constructor taking number as an int
BigdecimalInt::BigdecimalInt(int smallNumber){
    resultSign = '+';
    signOfNumber = '+';
    // if number is negative
    if(smallNumber < 0)
    {
        signOfNumber = '-';
        smallNumber *=-1;
    }
    // store number in container
    while(smallNumber != 0)
    {
        number.push_back(smallNumber%10);
        smallNumber /= 10;
    }

}

// summation of 2 numbers
deque<int> BigdecimalInt::sum(deque<int> &v1, deque<int> &v2) {

    int carry = 0, num1 = 0, num2 = 0, sum;
    // container to store result of summation
    deque<int>summation;

    // add digit by digit until the last digit of the smallest number
    while(!(v1.empty() || v2.empty()))
    {
         num1 = v1.front();
         num2 = v2.front();
         sum = (num1+num2+carry) % 10;
         carry = (num1+num2) / 10;
        summation.push_back(sum);
        v1.pop_front();
        v2.pop_front();
    }
    // if there still carry until summation operation
    if(v1.empty() && v2.empty())
    {
        summation.push_back(carry);
    }

    while(!v1.empty()){
        v1.front() = v1.front() + carry;
        carry = 0;
        summation.push_back(v1.front());
        v1.pop_front();
    }

    while(!v2.empty()){
        v2.front() = v2.front() + carry;
        carry = 0;
        summation.push_back(v2.front());
        v2.pop_front();
    }
    return summation;
}

// subtraction of 2 numbers consider first parameter is bigger number
deque<int> BigdecimalInt::subtract(deque<int> &v1, deque<int> &v2) {

    int  num1 = 0, num2 = 0, sub;

    deque<int>subtraction;
    subtraction.clear();

    while(!(v1.empty() || v2.empty()))
    {
        num1 = v1.front();
        num2 = v2.front();
        // if num1 is less than num2 borrow 10 from the digit beside me
        bool not_borrow = true;
        if(num1 < num2)
        {
            num1 += 10;
            v1.pop_front();
            v1.front() = v1.front()-1;
            not_borrow = false;
        }

        sub = num1-num2;
        subtraction.push_back(sub);
        v2.pop_front();

        if(not_borrow)
        {
            v1.pop_front();
        }

    }

    while(!v1.empty()){
        subtraction.push_back(v1.front());
        v1.pop_front();
    }
    while(!v2.empty()){
        subtraction.push_back(v2.front());
        v2.pop_front();
    }
    return subtraction;
}


//+ operator to add two big numbers
BigdecimalInt BigdecimalInt:: operator +( BigdecimalInt &obj){


    // we have 4 cases for summation
    // case1 positive + positive
    if(this->signOfNumber == '+' && obj.signOfNumber == '+')
    {
        resultSign = '+';
        number = sum(this->number, obj.number);
    }

    // case2 positive + negative
    else if(this->signOfNumber == '+' && obj.signOfNumber == '-')
    {
        int bigger = whoIsBigger(this->number, obj.number);
            if(bigger == 1)
            {
                resultSign = '+';
                number = subtract(this->number,  obj.number);
            }
            else if(bigger == 2)
            {
                resultSign = '-';
                number = subtract( obj.number, this->number);
            }
            else
            {
                resultSign = '+';
                number.clear();
                number.push_back(0);
            }
    }
    // case3 negative + positive
   else if(this->signOfNumber == '-' && obj.signOfNumber == '+')
    {
        int bigger = whoIsBigger(this->number,  obj.number);
        if(bigger == 1)
        {
            resultSign = '-';
           number = subtract(this->number,  obj.number);
        }
        else if(bigger == 2)
        {
            resultSign = '+';
           number = subtract( obj.number, this->number);
        }
        else
        {
            resultSign = '+';
            number.clear();
            number.push_back(0);
        }
    }
    // case4 negative + negative
    else if(this->signOfNumber == '-' && obj.signOfNumber == '-')
    {
           resultSign = '-';
            number = sum(this->number,  obj.number);
    }
        return *this;
}

// check which number of 2 numbers is bigger number
int BigdecimalInt::whoIsBigger(deque<int> &v1, deque<int> &v2) {
    // if length of first number is bigger then first is bigger number
    if(v1.size() > v2.size())
    {
        return 1;
    }
    // if length of second number is bigger then first is bigger number
    else if(v1.size() < v2.size())
    {
        return 2;
    }
    // if they have the same length then check for bigger digit from left to right
    else {
        for(int i = v1.size() - 1; i >= 0; --i)
        {
            if(v1[i] == v2[i])
            {
                continue;
            }
            else if(v1[i] > v2[i])
            {
                return 1;
            }
            else {
                return 2;
            }
        }
    }
    // if both are equal
    return 0;
}



// - operator to subtract to big numbers
BigdecimalInt BigdecimalInt::operator -( BigdecimalInt &obj){
   int bigger_num = 0;

    // we have 4 cases for subtraction
    // case1 positive - positive same (positive + negative)
    if(this->signOfNumber == '+' && obj.signOfNumber == '+')
    {
        bigger_num = whoIsBigger(this->number, obj.number);
        if(bigger_num == 1)
        {
            resultSign = '+';
            number = subtract(this->number, obj.number);
        }
        else if(bigger_num == 2)
        {
            resultSign = '-';
            number = subtract(obj.number,this->number);
        }
        else
        {
            resultSign = '+';
            number.clear();
            number.push_back(0);
        }

    }

        // case2 positive - negative same as (positive + positive)
    else if(this->signOfNumber == '+' && obj.signOfNumber == '-')
    {
       resultSign = '+';
       number = sum(this->number,obj.number);
    }
        // case 3 negative same as (negative + negative)
    else if(this->signOfNumber == '-' && obj.signOfNumber == '+')
    {
        resultSign = '-';
        number = sum(this->number,obj.number);
    }
    // case 4 negative - negative equivalent  to (negative + positive)
    else if(this->signOfNumber == '-' && obj.signOfNumber == '-')
    {
       bigger_num = whoIsBigger(this->number,obj.number);
       if(bigger_num == 1)
       {
           resultSign = '-';
           number = subtract(this->number, obj.number);
       }
       else if(bigger_num == 2)
       {
           resultSign = '+';
           number = subtract(obj.number, this->number);
       }
       else
       {
           resultSign = '+';
           number.clear();
           number.push_back(0);
       }
    }
    return *this;

}

// = operator
BigdecimalInt BigdecimalInt:: operator = (const BigdecimalInt &obj ){

    this->resultSign = obj.resultSign;
    bool checkLeadingZeros = true;
    int len = obj.getNumberLength();
    // avoid case when the result of operation is 0
    if(len == 1)
    {
        this->number = obj.number;
        return  *this;
    }
    // ignore leading zeros
    for(int i = len-1; i >= 0 ; --i){
        if(obj.number[i] != 0)
        {
            checkLeadingZeros = false;
        }
        if(!checkLeadingZeros)
        {
            this->number.push_back(obj.number[i]);
        }

    }

    return *this;
}

//get length of a number
int BigdecimalInt::getNumberLength()const{
    return number.size();
}
//display number
ostream& operator <<(ostream& output , const BigdecimalInt& obj){
    int len = obj.getNumberLength();
    if(obj.resultSign == '-')
    {
        output<<"-";
    }
    for(int i = 0; i < len; ++i){
        output<<obj.number[i];
    }
    output<<'\n';
    return output;
}