#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <fstream>
using namespace std;

void wtf() {
    ofstream fout("input.txt");

    string fname, lname;
    int points;
    string line;

    while (getline(std::cin, line)) {
        if (line == "----") {
            break;
        }
        fout << line << endl;
    }
}

void rff1() {
    ifstream fin("output1.txt");
    string line;
    while (getline(fin, line)) {
        cout << line << endl;
    }
}

void rff2() {
    ifstream fin("output2.txt");
    string line;
    while (getline(fin, line)) {
        cout << line << endl;
    }
}

class Book{
private:
    string title;
    string author;
    int yearPub;
public:
    Book(const string &title, const string &author, int yearPub)
    : title(title), author(author), yearPub(yearPub) {}

    const string &getTitle() const {
        return title;
    }

    const string &getAuthor() const {
        return author;
    }

    int getYearPub() const {
        return yearPub;
    }

    friend ostream &operator<<(ostream &o, Book &b){
        o<<b.title<<" "<<b.author<<" "<<b.yearPub<<endl;
        return o;
    }
};

class BookAlreadyExistsException{
private:
    Book b;
public:
    explicit BookAlreadyExistsException(const Book &b) : b(b) {}

    void print(){
        cout<<"Book "<<b<<" already exists in the library"<<endl;
    }
};

class Library{
private:
    string name;
    int numBooks;
    vector<Book> books;
public:
    Library(const string &name, int numBooks)
    : name(name), numBooks(numBooks) {
        books.clear();
    }

    Library &operator+=(Book &b)
    {
        for(int i=0; i<books.size(); i++){
            if(books[i].getAuthor()==b.getAuthor() && books[i].getTitle()==b.getTitle() && books[i].getYearPub()==b.getYearPub()){
                throw BookAlreadyExistsException(b);
            }
        }

        books.push_back(b);
        return *this;
    }

    friend ostream &operator<<(ostream &o, Library &l)
    {
        for(int i=0; i<l.numBooks; i++){
            o<<l.books[i];
        }
        return o;
    }

    vector<Book> getBooksByAuthor(string & author, int & numberFound){
        numberFound=0;
        vector<Book> found;

        for(int i=0; i<books.size(); i++){
            if(books[i].getAuthor()==author){
                found.push_back(books[i]);
            }
        }
        numberFound=found.size();
        if(numberFound==0){
            found.clear();
            return found;
        }

        return found;
    }

    int getNumBooks() const {
        return books.size();
    }

};

int main() {


    wtf();


    //YOUR CODE STARTS HERE

    ifstream fin("input.txt");

    string libraryName;
    getline(fin, libraryName);
    int n;
    fin>>n;
    fin.ignore();

    Library library(libraryName, n);

    string title, avtor;
    int year;

    for(int i=0; i<n; i++){
        getline(fin,title);
        getline(fin,avtor);
        fin>>year;
        fin.ignore();
        Book b(title,avtor,year);
        try{
            library+=b;
        } catch(BookAlreadyExistsException &ex){
            ex.print();
        }
    }
    fin.close();

    ofstream fout1("output1.txt");
    fout1<<library;
    fout1.close();

    //DO NOT MODIFY THE NEXT PART

    string author;
    getline(std::cin, author);

    //DO NOT MODIFY THE PART ABOVE, CONTINUE AFTER THIS COMMENT

    ofstream  fout2("output2.txt");
    vector<Book> result=library.getBooksByAuthor(author,n);
    if(n==0){
        fout2<<"None"<<endl;
    }else{
        for(int i=0; i<n; i++){
            fout2<<result[i]<<endl;
        }
    }
    fout2.close();

    //YOUR CODE ENDS HERE
    rff1();
    cout << "Books written by " << author << " are: " << endl;
    rff2();

    return 0;
}
