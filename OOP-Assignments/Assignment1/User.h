
#ifndef ASSIGNMENT1_USER_H
#define ASSIGNMENT1_USER_H

#include<cstring>
#include<iostream>
#include <string>

class User {
private:
    std::string name;
    int age;
    int id;
    std::string password;
    std:: string email;
public:
    static int count;//done
    User();//done
    User(std::string name, int age, std::string email, std::string password);
    User(const User&user);
    bool operator==(const User& user);
    void setName(std::string name);
    std::string getName() const;
    void setPassword(std::string password);
    std::string getPassword();
    void setEmail(std::string email);
    std::string getEmail();
    void setAge(int age);
    int getAge();//done
    void setId(int id);
    int getId();
    friend std::ostream &operator<<(std::ostream &output, const User &user );
    friend std::istream &operator>>(std::istream &input, User &user );
};


#endif //ASSIGNMENT1_USER_H
