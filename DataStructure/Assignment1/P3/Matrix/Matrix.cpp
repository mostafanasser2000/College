//
// Created by mostafa nasser mohamed ali on 5/14/2021.
//

#include "Matrix.h"


//default constructor
template<class T>
Matrix<T>::Matrix() {
    rows = 4;
    columns = 4;
    mat = new T *[rows];
    for (int i = 0; i < rows; i++)
    {
        mat[i] = new T[columns];
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j <columns; j++) {
            mat[i][j] = 0;
        }
    }

}

//parametrized constructor
template<class T>

Matrix<T>::Matrix(int numberOfRows , int numberOfColumns) {
    rows = numberOfRows;
    columns = numberOfColumns;
    mat = new T *[rows];
    for (int i = 0; i < rows; i++)
    {
        mat[i] = new T[columns];
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j <columns; j++) {
            mat[i][j] = 0;
        }
    }

}
//set number of rows and columns of a matrix
template<class T>
void Matrix<T>::setSize(int rows, int columns) {
    this->rows = rows;
    this->columns = columns;
}
//copy constructor
template<class T>
Matrix<T>::Matrix(const Matrix & obj){
    //allocate memory for the whole matrix
    rows = obj.rows;
    columns = obj.columns;
    mat = new T *[rows];
    //allocate memory for every row
    for(int i = 0; i < rows; i++){
        mat[i] = new T[columns];
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j <columns; j++) {
            mat[i][j] = obj.mat[i][j];
        }
    }
}
//get number of rows
template<class T>
int Matrix<T>::getRows() const {
    return rows;
}
//get number of columns
template<class T>
int Matrix<T>::getColumns() const {
    return columns;
}

//input operator
template<class T>
istream &operator >>(istream &input, const Matrix<T> &obj){
    int r = obj.getRows(), c = obj.getColumns();
    for(int i = 0; i < r; i++){
        for(int j = 0; j < c; j++){
            input>>obj.mat[i][j];
        }

    }

    cout<<"----------------------------------------------\n";
    return input;
}
//output operator
template<class T>
ostream &operator <<(ostream &output,const  Matrix<T> &obj){
    int r = obj.getRows(), c = obj.getColumns();
    output<<fixed<<setprecision(2);
    for(int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++){
            output << obj.mat[i][j] << " "<<"|"<<" ";
        }

        output << endl;
    }
    output<<"-------------------------------------------------\n";
    return output;
}

// operator +
template<class T>

Matrix<T> Matrix<T>::operator + (Matrix &obj){
    int r = obj.getRows(), c = obj.getColumns();
    if(rows != r || columns != c ){
        throw "The rows and columns of two matrices must be equal\n";
    }

    for(int i = 0; i < r; i++){
        for(int j = 0; j < c; j++){
            this->mat[i][j] += obj.mat[i][j];
        }
    }

    return *this;

}
// operator -

template<class T>
Matrix<T> Matrix<T>::operator - (Matrix &obj){
    int r = obj.getRows(), c = obj.getColumns();
    if(rows != r || columns != c ){

        throw "The rows and columns of two matrices must be equal\n";
    }

    for(int i = 0; i < r; i++){
        for(int j = 0; j <c; j++){
            this->mat[i][j] -= obj.mat[i][j];
        }
    }
    return *this;

}
// operator *

template<class T>
Matrix<T> Matrix<T>::operator *(Matrix &obj){
    if(this->columns != obj.getRows()){

        throw "The columns of first matrix must be equal to the rows of second matrix\n";
    }
    Matrix Multiplication_Matrix(this->rows,obj.columns);

    int r = Multiplication_Matrix.getRows();
    int c = Multiplication_Matrix.getColumns();

    for(int i = 0; i <r ; ++i){
        for(int j = 0; j < c; ++j){
            //Multiplication Matrix[i][j] = the result of Multiplication of all elements in row (i) in first matrix
            //in all elements of  column j in second matrix
            int r1 = obj.getRows();
            for(int k = 0; k < r1 ; ++k){
                Multiplication_Matrix.mat[i][j] += mat[i][k] * obj.mat[k][j];
            }
        }
    }
    return Multiplication_Matrix;

}
// operator =

template<class T>
Matrix<T>& Matrix<T>::operator = (const Matrix  &obj){
    rows = obj.getRows();
    columns = obj.getColumns();
    for(int i = 0 ; i < rows; ++i){
        for(int j = 0; j < columns; ++j){
            mat[i][j] = obj.mat[i][j];
        }
    }
    return *this;
}
//Transpose the whole matrix
template<class T>
Matrix<T> Matrix<T>::transpose(Matrix &m) {
    int r = m.getRows(), c =  m.getColumns();
    Matrix<T> Transpose(c,r);
    for(int i = 0; i < r; ++i){
        for(int j = 0; j < c; ++j){
            Transpose.mat[j][i] = m.mat[i][j];
        }
    }
    return  Transpose;
}
//destructor
template<class T>
Matrix<T>::~Matrix(){
    for(int i = 0; i < rows; i++)
        delete []mat[i];
    delete [] mat;
}
