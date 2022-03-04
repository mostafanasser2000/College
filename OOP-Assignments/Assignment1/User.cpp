#include "User.h"
//default constructor
User::User(){
    name = "";
    age = 0;
    password = "";
    email = "";
    count++;
    id = count;//every user object take a unique id start with 1
}

// Parameterized constructor
User::User(std::string name , int age, std::string email, std::string password) {
    this->name = name;
    this->email = email;
    this->age = age;
    this->password = password;


}

//Copy constructor
User::User(const User &user) {
    name = user.name;
    age = user.age;
    password = user.password;
    email = user.email;
    id = user.id;

}

//  to set name to user object
void User::setName(std::string name){
    this->name = name;
}

//  to get the user object name
std::string User::getName() const {
    return name;
}

//   to set password to user object
void User::setPassword(std::string password){
    this->password = password;
}

//  to get the user object password
std::string User::getPassword() {

    return password;
}

// to set email to user object
void User::setEmail(std::string email){
    this->email = email;
}

//get the user object email
std::string User::getEmail(){
    return email;
}

//set age to user object
void User::setAge(int age){
    this->age = age;
}

//get the user object age
int User::getAge(){
    return age;
}

//set id to the user object
void User::setId(int id){
    if(id = 1)
        this->id = id;
    else
        this->id = count;
}

//get the user object id
int User::getId(){
    return id;
}

// declare << operator to print all the user members
std::ostream &operator<<(std::ostream &output, const User &user ){
    std::cout<<"========"<<"User "<<user.id<<" info"<<"========"<<'\n';
    output<<"Name: "<<user.name<<" |Age: "<<user.age<<" |Id: "<<user.id<<" |Email: "<<user.email<<"\n";
    std::cout<<"======================================================\n";
    return output;
}

//declare >> to get all the user members from console
std::istream &operator>>( std::istream &input, User &user ){
    input>>user.name>>user.age>>user.email>>user.password;
    return input;
}

// make == operator to check if two user are equal
bool User:: operator==(const User& user){
    return (id == user.id && age == user.age && email == user.email && name == user.name);

}

//initialize the static member
int User::count = 0;