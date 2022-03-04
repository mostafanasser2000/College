#include "User.h"
#include "Book.h"

void display_User();
void display_Book();

int main() {

    // test example that in the description pdf file
    User u1, u2 ;
    std::cout<<"Let's add a user"<<'\n';
    display_User();
    std::cin>>u1 ;
    std::cout<<u1;
    std::cout<<"Let's add another user"<<'\n';
    display_User();
    std::cin >>u2;
    std::cout<<u2;

    Book book1,book2;
    std::cout<<"Let's add a book"<<'\n';
    display_Book();
    std::cin>>book1;
    std::cout<<book1;
    std::cout<<"Let's add another book"<<'\n';
    display_Book();
    std::cin>>book2;
    std::cout<<book2;
    std::cout<<"Let's assign an author for the first book ,set the first user as an author"<<'\n';
    std::cout<<"Let's rate the first book with 3 and 4 ratings and print the book info"<<'\n';
    book1.setAuthor(u1);
    book1.rateBook(3);
    book1.rateBook(4);
    std::cout<<book1;
    std::cout<<"\n======================================================\n";
    std::cout<<"Let's add a new rating for b1 with 5 and print the book info"<<'\n';
    book1.rateBook(5);
    std::cout<<book1;
    std::cout<<"\n======================================================\n";
    return 0;
}

 void display_User()
 {
     std::cout<<"Enter the user information in this order"<<'\n';
     std::cout<<"Name "<<"Age "<<"Email "<<"Password "<<"(Space separated)"<<'\n';
 }

 void display_Book()
 {
     std::cout<<"Enter the book information in this order"<<'\n';
     std::cout<<"Title "<<"ISBN "<<"Category "<<"(Space separated)"<<'\n';
 }