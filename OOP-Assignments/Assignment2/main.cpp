#include "UserList.h"
#include "BookList.h"
using namespace std;

int choice, number_of_books, number_of_users, userId, bookId, rating;
string username, bookname, category;

UserList userList1;
BookList bookList1, bookList2;
User user1,*foundUser;
Book book1,*foundBook;

bool bookflag = true, userflag = true;


void mainMenu();
void existingBooksMenu();
void existingUsersMenu();
void userMenu();
void bookMenu();
void invalidChoice();
void assignAuthor(Book b);
void updateBook();
void searchForUser(string name, int id);

int main() {

    //Simulate program
    mainMenu();
    return 0;







}



// check if user enter invalid choice
void invalidChoice()
{
    cout<<"Invalid choice\n";
    cout<<"Enter a valid choice: ";

}

// main menu panel
void mainMenu()
{
    int cap;
    cout<<"Select one Of the following choices:"<<'\n';
    cout<<"1- Books Menu\n"<<"2- Users Menu\n"<<"3- Exit\n";
    cin>>choice;


        switch(choice){
            case 1:{
                // using flag to display this message only for one time
                 if(bookflag)
                 {
                     cout<<"How many books will be added?\n";
                     cin>>cap;
                     bookList1.setCapacity(cap);
                 }
                 // go to book menu to after user enter number of books
                bookMenu();
                break;
            }
            case 2:{
                // using flag to display this message one time only
                if(userflag)
                {
                    cout<<"How many users will be added?\n";
                    cin>>cap;
                    userList1.setCapacity(cap);
                }

                // go to user menu
                userMenu();
                break;
            }
            // exit from the program
            case 3:{
                exit(0);
            }
            //enforce user to  enter a valid choice
            default:{
               invalidChoice();
               mainMenu();
            }
        }

}

// user menu panel
void userMenu(){
    userflag = false;

    cout<<"USERS MENU\n"<<"1- Create a USER and add it to the list \n"<<"2- Search for a user \n"
        <<"3- Display all users \n"<<"4- Back to the main menu\n";

    cin>>choice;
    switch(choice){
        case 1:{
            cin>>user1;
            // check if list of users already full
            if(!userList1.addUser(user1))
            {
                cout<<"can't added a new user the list of users is full\n";
                mainMenu();
            }
            // back to user menu
            userMenu();
            break;

        }
        case 2:{
            // search for existing user
            existingUsersMenu();
            break;
        }
        case 3:{
            //print list of users
            cout<<userList1;
            userMenu();
            break;
        }
        // back to main menu
        case 4:{
           mainMenu();
           break;
        }
        // enforce user to enter a valid choice
        default:{
            invalidChoice();
            userMenu();
        }
    }
}

// menu for user to add book search for a book and etc
void bookMenu(){
    cout<<"BOOKS MENU \n"<<"1- Create a book and add it to the list \n"<<"2- Search for a book\n"
        <<"3- Display all books (with book rating) \n"<<"4- Get the highest rating \n"
        <<"5- Get all books of a user \n"<<"6- Copy the current List to a new List and switch to it \n"
        <<"7- Back to the main menu\n";

    bookflag = false;
    cin>>choice;
    switch(choice){
        case 1:
        {

            cin>>book1;

            // print a message if the list of books is already full
           if(!bookList1.addBook(book1))
           {
               cout<<"can't added a new book the list of books is full\n";
               mainMenu();
           }
           // if not ask user if he want to assign author to the recently added book or not
            assignAuthor(book1);
           // back for books menu
            bookMenu();
            break;
        }
        case 2:
        {
            // search in existing book
            existingBooksMenu();
            break;
        }
        case 3:
        {
            // print all the books in the book list
            cout<<bookList1;
            bookMenu();
            break;
        }
        case 4:
        {
            // get the highest rated book and print it
            book1 = bookList1.getTheHighestRatedBook();
            cout<<book1;
            bookMenu();
            break;
        }
        // get all books for a given author
        case 5:
        {

            break;
        }
        // copy currently book list to another book list
        case 6:
        {
            bookList2 = bookList1;
            bookMenu();
            break;
        }

        // back to main menu
        case 7:
        {
            mainMenu();
            break;
        }
        // enforce user to enter a valid choice
        default:{
            invalidChoice();
            bookMenu();
        }
    }
}


// menu to search for a specific user
void existingUsersMenu()
{
    cout<<"SEARCH FOR A USER \n"<<"1- Search by name \n"<<"2- Search by id \n"<<"3- Return to users Menu\n";

    cin>>choice;
    switch(choice){
        case 1:
        {
            cout<<"Enter Username: ";
            cin>>username;
            // search by user name
            searchForUser(username,0);
            break;
        }
        case 2:
        {
            // search by user id
            cout<<"Enter id"<<endl;
            cin>>userId;
            searchForUser("",userId);
            break;
        }
        // back to user menu
        case 3:
        {
            userMenu();
            break;
        }

        // enforce to user to enter a valid choice
        default:
        {
            invalidChoice();
            existingUsersMenu();
        }
    }
}

// menu for search for a specific book
void existingBooksMenu()
{
    cout<<"SEARCH FOR A BOOK \n"<<"1- Search by name \n"<<"2- Search by id \n"<<"3- Return to Books Menu\n";

    cin>>choice;
    switch(choice){
        case 1:
        {
            // search by name
            cout<<"Enter Name\n";
            cin>>bookname;
            foundBook = bookList1.searchBook(bookname);
            if(foundBook == nullptr){
                cout<<"Book not found\n";
            }
            else{
                cout<<*foundBook;
                // go to update menu to update book info
                updateBook();
            }
            break;
        }
        case 2:
        {
            cout<<"Enter id"<<endl;
            cin>>bookId;
            foundBook = bookList1.searchBook(bookId);
            if(foundBook == nullptr){
                cout<<"Book not found\n";
            }
            else{
                cout<<*foundBook;
                updateBook();
            }
            break;
        }
        // back to book menu
        case 3:
        {
            bookMenu();
            break;
        }
        // enforce user to enter a valid choice
        default:{
            invalidChoice();
            existingBooksMenu();
        }
    }
}

// menu to update book info
void updateBook()
{
    cout<<"1- Update Author\n"<<"2- Update Name\n"<<"3- Update Category\n"<<"4- Delete Book\n"<<"5- Rate Book   \n"
        <<"6- Get back to books menu  \n";

    cin>>choice;
    switch(choice){
        // update author
        case 1:
        {
            assignAuthor(*foundBook);
            updateBook();
            break;
        }
        // update title
        case 2:
        {
            cout<<"Enter new name\n";
            cin>>bookname;
            foundBook->setTitle(bookname);
            updateBook();
            break;
        }
        // update category
        case 3:
        {
            cout<<"Enter new category\n";
            cin>>category;
            foundBook->setCategory(category);
            updateBook();
            break;
        }
        // delete book
        case 4:
        {
            bookList1.deleteBook(foundBook->getId());
            bookMenu();
            break;
        }
        // rate current found book
        case 5:
        {
            cout<<"Enter Rating value:\n";
            cin>>rating;
            foundBook->rateBook(rating);
            updateBook();
            break;
        }
        // back to book menu
        case 6:
        {
            bookMenu();
            break;
        }
        // enforce user to enter a valid choice
        default:
        {
            invalidChoice();
        }
    }
}

// assign author for added book
void assignAuthor(Book b )
{
    cout<<"1- Assign author\n"<<"2- Continue\n";
    cin>>choice;
    if(choice == 1){
        cout<<"Enter author (user) id: "<<endl;
        cin>>userId;
        foundUser = userList1.searchUser(userId);
        if(foundUser == nullptr){
            cout<<"No author found with id  = "<<userId<<endl;
            assignAuthor(b);
        }
        else{

            bookList1.searchBook(b.getTitle())->setAuthor(*foundUser);
            bookMenu();
        }
    }
    else {
        bookMenu();
    }
}

// search for user by username or user id
void searchForUser(string username, int id){
    if(id == 0)
    {
        foundUser =  userList1.searchUser(username);
    }

    else
    {
        foundUser =  userList1.searchUser(id);
    }

    if(foundUser == nullptr){
        cout<<"User not found"<<endl;
        existingUsersMenu();
    }
    else{
        cout<<*foundUser<<"\n";
        cout<<"1- Delete user\n"<<"2- Return to Users Menu\n";

        cin>>choice;
        if(choice == 1){
            userList1.deleteUser(foundUser->getId());
            existingUsersMenu();
        }
        else {
            userMenu();
        }
    }
}