

#ifndef ASSIGNMENT2_USER_H
#define ASSIGNMENT2_USER_H

#include<cstring>
#include<iostream>
#include <string>
class User{
private:
    std::string name;
    int age;
    int id;
    std::string password;
    std::string email;
public:
    User();//done
    User(std::string name, int age, std::string email, std::string password);
    User(const User&user);
    bool operator==(const User& user);
    void setName(std::string name);
    std::string getName() const;
    void setPassword(std::string password);
    std::string getPassword()const;
    void setEmail(std::string email);
    std::string getEmail()const;
    void setAge(int age);
    int getAge()const;//done
    void setId(int id);
    int getId()const;
    friend std::ostream &operator<<(std::ostream &output, const User &user );
    friend std::istream &operator>>( std::istream &input, User &user );
};


#endif //ASSIGNMENT2_USER_H
