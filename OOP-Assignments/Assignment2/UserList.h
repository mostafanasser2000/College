#include "User.h"
#ifndef ASSIGNMENT2_USERLIST_H
#define ASSIGNMENT2_USERLIST_H


class UserList {
private:
    User* users;
    int capacity;
    int usersCount;
public:
    UserList(int capacity  = 0);
    UserList(const UserList &obj);
    void setCapacity(int cap);
    bool addUser(User user); // at the end of the array.
    User* searchUser(std::string name);
    User* searchUser(int id);
    void deleteUser(int id);
    friend std::ostream &operator<<( std::ostream &output, UserList &userList );
    ~UserList();
    User & operator [ ] (int position);
};


#endif //ASSIGNMENT2_USERLIST_H
