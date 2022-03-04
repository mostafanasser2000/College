//
// Created by mostafa on ٢٨‏/٢‏/٢٠٢٢.
//


#ifndef ASSIGNMENT1_BOOK_H
#define ASSIGNMENT1_BOOK_H


#include "User.h"

class Book {
private:
    std::string title;
    std::string isbn;
    int id; //
    std::string category;
    double averageRating;
    User author;
    int number_ratings;
    double sum_ratings;

public:
    static int count;
    Book();
    Book(std::string title, std::string isbn, std::string category);
    Book(const Book& book);
    void setTitle(std::string title);
    std::string getTitle();
    void setISBN(std::string isbn);
    std::string getISBN();
    void setId(int id);
    int getId();//done
    void setCategory(std::string category);
    std::string getCategory();
    void setAuthor(User user);
    User getAuthor();
    void rateBook(int rating);
    bool operator==(const Book& book);
    friend std::ostream &operator<<(std::ostream &output, const Book &book );
    friend std::istream &operator>>( std::istream &input, Book &book );
};


#endif //ASSIGNMENT1_BOOK_H
