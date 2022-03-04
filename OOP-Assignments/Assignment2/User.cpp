#include "User.h"

//initialize the static member


//default constructor
User::User(){
    name = "";
    age = 0;
    password = "";
    email = "";
    id = 0;

}

// Parameterized constructor
User::User(std::string name , int age, std::string email, std::string password) {
    this->name = name;
    this->email = email;
    this->age = age;
    this->password = password;
    id = 0;

}

//Copy constructor
User::User(const User &user) {
    name = user.name;
    age = user.age;
    password = user.password;
    email = user.email;
    id = user.id;

}


void User::setName(std::string name){
    this->name = name;
}

std::string User::getName() const {
    return name;
}

void User::setPassword(std::string password){
    this->password = password;
}

std::string User::getPassword()const {

    return password;
}

void User::setEmail(std::string email){
    this->email = email;
}

std::string User::getEmail()const{
    return email;
}

void User::setAge(int age){
    this->age = age;
}

int User::getAge()const{
    return age;
}

void User::setId(int id){
    this->id = id;
}

int User::getId()const{
    return id;
}

//  << operator to print all the user members
std::ostream &operator<<(std::ostream &output, const User &user ){
    std::cout<<"======== User info ========"<<'\n';
    output<<"Name: "<<user.name<<"\nAge: "<<user.age<<"\nId: "<<user.id<<"\nEmail: "<<user.email<<"\n";
    std::cout<<"========================================\n";
    return output;
}

// >>  operator to get all the user members from console
std::istream &operator>>( std::istream &input, User &user ){
    std::cout<<"Enter the user information in this order"<<'\n';
    std::cout<<"Name "<<"Age "<<"Email "<<"Password "<<"(Space separated)"<<'\n';

    //every user object take a unique id start with 1
    input>>user.name>>user.age>>user.email>>user.password;
    return input;
}

//  == operator to check if two user are equal
bool User:: operator==(const User& user){
    return (id == user.id && age == user.age && email == user.email && name == user.name);

}

