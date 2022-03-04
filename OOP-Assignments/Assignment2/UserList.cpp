#include "UserList.h"

//Parametrized Constructor
UserList::UserList(int capacity  ) {
    this->capacity = capacity;
    users = new User[capacity];
    usersCount = 0;

}

//Copy  Constructor
UserList::UserList(const UserList &obj){
    capacity = obj.capacity;
    users = new User[capacity];
    usersCount = obj.usersCount;
    for(int i = 0; i < usersCount; i++){
        users[i] = obj.users[i];
    }

}

void UserList::setCapacity(int cap) {
    this->capacity = cap;
    std::cout<<this->capacity<<"\n";
    users = new User[capacity];
}

bool UserList::addUser(User user){
    if(usersCount < capacity)
    {
        user.setId(usersCount+1);
        users[usersCount] = user;
        usersCount++;
        return true;
    }
    return false;
}

User*UserList::searchUser(std::string name){

    for(int i = 0; i < this->usersCount; i++){
        if(users[i].getName() == name)
            return &users[i];
    }
    return nullptr;
}

User* UserList::searchUser(int id){
    for(int i = 0; i < usersCount; i++){
        if(users[i].getId() == id)
            return &users[i];
    }
    return nullptr;
}
// delete user given it's id
void UserList::deleteUser(int id){
    for(int i = 0; i < capacity;i++){
        if(users[i].getId() == id ){
            users[i].setName("");
            users[i].setAge(0);
            users[i].setEmail("");
            users[i].setId(0);
            users[i].setPassword("");
            for(int j = i; j < capacity-1;j++){
                users[j] = users[j+1];
            }
        }
    }
    usersCount--;
}

// << operator to display user information
std::ostream &operator<<( std::ostream &output, UserList &userList ){
    for(int i = 0; i <userList.usersCount;i++){
        output<<userList.users[i];
    }
    return output;
}

UserList::~UserList(){
    delete [] users;
}
// [] operator to get user by index
User & UserList::operator [ ] (int position){
    return users[position-1];
}