#ifndef ASSIGNMENT2_BOOKLIST_H
#define ASSIGNMENT2_BOOKLIST_H

#include "Book.h"

class BookList {
    Book* books;
    int capacity;
    int booksCount;
public:
    BookList(const BookList& anotherList);
    BookList(int capacity  = 0);
    void setCapacity(int cap);
    bool addBook(Book book);
    Book* searchBook(std::string name);
    Book* searchBook(int id);
    void deleteBook(int id); //delete a book
    Book getTheHighestRatedBook();
    Book* getBooksForUser(User); // get all books of this author
    Book & operator[](int position);
    friend std::ostream &operator<<( std::ostream &output, BookList &booklist ); //to display all books
    ~BookList();
};


#endif //ASSIGNMENT2_BOOKLIST_H
