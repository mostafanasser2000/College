#include "BookList.h"


BookList::BookList(int capacity){
    this->capacity = capacity;
    books = new Book[capacity];
    booksCount = 0;
}

BookList::BookList(const BookList& anotherList){
    books = new Book[anotherList.capacity];
    booksCount  = anotherList.booksCount;
    for(int i = 0; i < anotherList.capacity; i++){
        books[i] = anotherList.books[i];
    }
}

void BookList::setCapacity(int cap){
    capacity = cap;
    books = new Book[capacity];
}
bool BookList::addBook(Book book){
    if(booksCount < capacity)
    {
        book.setId(booksCount+1);
        books[booksCount] = book;
        booksCount++;
        return true;
    }
    return false;
}

Book* BookList::searchBook(std::string name){
    for(int i = 0; i < booksCount; i++){
        if(books[i].getTitle() == name){
            return &books[i];
        }
    }
    return nullptr;
}

Book* BookList::searchBook(int id){
    for(int i = 0; i < booksCount; i++){
        if(books[i].getId() == id){
            return &books[i];
        }
    }
    return nullptr;
}

void BookList::deleteBook(int id){
    for(int i = 0; i < capacity;i++){
        if(books[i].getId() == id){
            books[i].setTitle("");
            books[i].setCategory("");
            books[i].setISBN("");
            books[i].setId(0);
            books[i].rateBook(0);
            User u("",0,"","");
            books[i].setAuthor(u);
            for(int j = i; j < capacity-1; j++){
                books[j] = books[j+1];
            }
        }
    }
    booksCount--;

}
Book BookList::getTheHighestRatedBook(){
    float MAX = 0;
    Book b;
    for(int i = 0; i < booksCount; i++){
        if(books[i].getAverageRating() > MAX){
            MAX = books[i].getAverageRating();
            b = books[i];
        }
    }
    return b;
}

Book* BookList::getBooksForUser(User u){
    Book *list;
    for(int i = 0; i < booksCount; i++){
        if(books[i].getAuthor() == u){
            list[i] = books[i];
        }

    }
    return list;

}

Book & BookList::operator [ ] (int position){
    return books[position-1];
}

std::ostream &operator<<( std::ostream &output, BookList &booklist){
    for(int i = 0; i < booklist.booksCount;i++){
        output<<booklist.books[i];
    }
    return output;

}

BookList::~BookList(){
    delete [] books;
}