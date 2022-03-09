//
// Created by mostafa nasser mohamed ali on 5/14/2021.
//

#ifndef MATRIX_MATRIX_H
#define MATRIX_MATRIX_H



#include<iostream>
#include<iomanip>
using namespace std;



template<class T>
class Matrix{
private:
    int rows;
    int columns;
    T **mat;

public:
    Matrix();
    Matrix(int  , int  );
    Matrix(const Matrix & );
    ~Matrix();
    void setSize(int rows, int columns);
    template<class U>
    friend istream& operator>>(istream &input, const Matrix<U> &);
    template<class U>
    friend ostream& operator<< (ostream &output,const  Matrix<U> &);
    Matrix operator + (Matrix &);
    Matrix operator-(Matrix &);
    Matrix operator * (Matrix &);
    Matrix transpose(Matrix &m);
    Matrix& operator=(const Matrix &);
    int getRows() const;
    int getColumns() const;
};





#endif //MATRIX_MATRIX_H
