//
// Created by mostafa on ٢٨‏/٢‏/٢٠٢٢.
//

#include "Book.h"
int Book::count = 0;

//default constructor
Book::Book(){
    title = "";
    isbn = "";
    category = "";
    count++; // increased number of books by one
    id = count;
    averageRating = 0;
    number_ratings = 0;
    sum_ratings = 0;
}

// Parameterized constructor
Book::Book(std::string title, std::string isbn, std::string category){
    this->title = title;
    this->isbn = isbn;
    this->category = category;
}

//Copy constructor
Book::Book(const Book& book){
    title = book.title;
    isbn = book.isbn;
    category = book.category;
    id = book.id;
    averageRating = book.averageRating;
    author = book.author;
}


void Book::setTitle(std::string title){
    this->title = title;
}


std::string Book::getTitle(){
    return title;
}

void Book::setISBN(std::string isbn){
    this->isbn = isbn;
}

std::string Book::getISBN(){
    return isbn;
}

void Book::setId(int id){
    this->id = id;
}

int Book::getId(){
    return id;
}

void Book::setCategory(std::string category){
    this->category = category;
}

std::string Book::getCategory(){
    return category;
}

void Book::setAuthor(User user){
    this->author = user;
}

User Book::getAuthor(){
    return author;
}

/*
 * calculate the average rating for the book by counting the number of rates
 * and sum of these rates
 */
void Book::rateBook(int rating){
    number_ratings++;
    sum_ratings += rating;
    averageRating = sum_ratings / number_ratings;
}

bool Book::operator==(const Book& book){
    return (title == book.title && isbn == book.isbn && id == book.id && category == book.category && author == book.author);
}

// operator << to print all book object members
std::ostream &operator<<(std::ostream &output, const Book &book ){
    std::cout<<"========"<<"Book "<<book.id<<" info"<<"========"<<std::endl;
    output<<"Title: "<<book.title<<" |ISBN: "<<book.isbn<<" |Category: "<<book.category<<" |Avg Rating: "<<book.averageRating<<'\n';
    std::cout<<"======================================================\n\n";
    // if user have author then print author
    if(!(book.author.getName() == ""))
        std::cout<<book.author.getName();
    return output;
}
// operator >> to get all book members from console
std::istream &operator>>( std::istream &input, Book &book ) {
    input >> book.title >> book.isbn >> book.category;
}