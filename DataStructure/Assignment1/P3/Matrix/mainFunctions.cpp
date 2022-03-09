//
// Created by mostafa nasser mohamed ali on 5/14/2021.
//
#include "Matrix.cpp"

//create 3 matrices  of type double
Matrix<int> mat1,mat2,result_Matrix;
int rows,columns;
void first(){
    cout<<"Enter the first Matrix size rows and columns space separated"<<endl;
    cin>>rows>>columns;
    mat1.setSize(rows,columns);
    cin>>mat1;
}
void second(){
    cout<<"Enter the second Matrix size rows and columns space separated"<<endl;
    cin>>rows>>columns;
    mat2.setSize(rows,columns);
    cin>>mat2;
}
//
void menu(){
    cout<<
          "1- Perform Matrix Addition\n"
          "2- Perform Matrix Subtraction\n"
          "3- Perform Matrix Multiplication\n"
          "4- Matrix Transpose\n"
          "5- Exit"<<endl;
}
void Addition(){
    try {
       first();
       second();
        result_Matrix = mat1 + mat2;
        cout<<result_Matrix;
    }
    //catch the throwing exceptions if there is an error in the input
    catch (const char * msg){
        cout<<msg;
    }

}
void Subtraction(){
    try{
        first();
        second();
        result_Matrix = mat1 - mat2;
        cout<<result_Matrix;
    }
        //catch the throwing exceptions if there is an error in the input

    catch (const char * msg){
        cout<<msg;
    }

}
void Multiplication(){
    try {
        first();
        second();
        result_Matrix = mat1 * mat2;
        cout<<result_Matrix;
    }
        //catch the throwing exceptions if there is an error in the input

    catch (const char * msg){
        cout<<msg;
    }

}
void Transpose(){
    cout<<"Enter the  Matrix size rows and columns space separated"<<endl;
    cin>>rows>>columns;
    mat1.setSize(rows,columns);
    cin>>mat1;
    result_Matrix.setSize(mat1.getColumns(),mat1.getRows());
    result_Matrix = mat1.transpose(mat1);
    cout<<result_Matrix;
}
