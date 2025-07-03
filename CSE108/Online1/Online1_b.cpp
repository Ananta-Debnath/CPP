#include <iostream>
#include <string>
using namespace std;


class Book
{
    string title;
    string author;
    int ratingCount;
    double avgRating;

public:
    Book()
    {
        title = "No Title";
        author = "No Author";
        ratingCount = 0;
        avgRating = 0;
    }

    Book(string title, string author)
    {
        this->title = title;
        this->author = author;
        ratingCount = 0;
        avgRating = 0;
    }

    void addRating(int rating)
    {
        avgRating = ((avgRating * ratingCount) + rating) / (ratingCount + 1);
        ratingCount++;
    }

    double getAverageRating()
    {
        return avgRating;
    }

    void display()
    {
        cout << title << " by " << author << endl;
        if (ratingCount != 0) cout << ", Average Rating: " << getAverageRating();
    }
};

class Library
{
    int maxBooks;
    Book* books;
    int totalBooks;

public:
    Library();

    Library(int maxBooks);
    
    Library(int maxBooks, Book* books, int totalBooks);

    Library(Library& lib);

    void addBook(Book b);

    void removeBook(Book b);

    void rateBook(string title, string author, int rating);

    void showBooks();

    Book bestRatedBook();

    ~Library();
};


int main() {
    Library lib1(5);
    Book b1("The Great Gatsby", "F. Scott Fitzgerald");
    Book b2("To Kill a Mockingbird", "Harper Lee");
    Book b3("1984", "George Orwell");
    Book b4("War and Peace", "Leo Tolstoy");
    Book b5("The Kite Runner", "Khaled Hosseini");
    Book b6("A Tale of Two Cities", "Charles Dickens");
    lib1.addBook(b1);
    lib1.addBook(b2);
    lib1.addBook(b3);
    lib1.addBook(b4);
    lib1.addBook(b5);
    lib1.addBook(b6);
    lib1.rateBook("The Great Gatsby", "F. Scott Fitzgerald", 5);
    lib1.rateBook("The Great Gatsby", "F. Scott Fitzgerald", 4);
    lib1.rateBook("To Kill a Mockingbird", "Harper Lee", 5);
    lib1.rateBook("1984", "George Orwell", 4);
    lib1.rateBook("1984", "George Orwell", 5);
    lib1.rateBook("1984", "George Orwell", 5);
    lib1.rateBook("War and Peace", "Leo Tolstoy", 3);
    lib1.rateBook("War and Peace", "Leo Tolstoy", 4);
    lib1.rateBook("The Kite Runner", "Khaled Hosseini", 5);
    lib1.rateBook("The Kite Runner", "Khaled Hosseini", 4);
    lib1.rateBook("The Kite Runner", "Khaled Hosseini", 5);
    cout << "\nLibrary 1 Books and Ratings:\n";
    lib1.showBooks();
    cout << "\nBest Rated Book in Library 1:\n";
    lib1.bestRatedBook().display();
    cout << endl;
    Library lib2(lib1);
    lib2.removeBook(b2);
    lib2.addBook(b6);
    cout << "\nLibrary 2 Books and Ratings:\n";
    lib2.showBooks();
    cout << "\nBest Rated Book in Library 1:\n";
    lib1.bestRatedBook().display();
    cout << "\nBest Rated Book in Library 2:\n";
    lib2.bestRatedBook().display();
    return 0;
    }