#include <iostream>
#include <string>
#include <algorithm>
using namespace std;


struct Book
{
    string name;
    int num_book = 0, num_borrrow = 0, id;
    void makeValue(){
        num_book = num_borrrow = 0;
    }
    void makeValue(int _id, string _name){
        id = _id, name = _name;
    }
    void makeValue(int _num_book, int _num_borrow, int _id, string _name){
        name = _name, num_book += _num_book, num_borrrow = _num_borrow, id = _id;
    }

};

struct User
{
    int num_borrrow = 0, national_id;
    Book borrowedBook[101];
    string name;
    void makeValue(){ // Constructor
        num_borrrow = 0;
    }
    void makeValue(string _name, int _national_id){ // Input name and id
        name = _name, national_id = _national_id;
    }
    void makeBorrow(Book _book){ // make a borrow
        borrowedBook[num_borrrow++] = _book;
    }
    int SearchBook(string _name){
        int pos = -1;
        for (int i = 0; i < num_borrrow; i++)
        {
            if(borrowedBook[i].name == _name){
                pos = i; break;
            }
        }
        return pos;
    }
    int checkValidBorrowedBook(string _name){ // return index of the book , if it is not there, it returns -1.
        int bookIndex = SearchBook(_name);
        return bookIndex;   
    }
    void makeReturn(int _bookIndex){ // return book 
        for (int i = _bookIndex; i < num_borrrow - 1; i++) // Delete the book
        {
            borrowedBook[i] = borrowedBook[i + 1];
        }
        num_borrrow--;
    }
};

bool sortByid(Book &_first, Book &_second){
    return _first.id < _second.id;
}                            
bool sortByName(Book &_first, Book &_second){
    return _first.name < _second.name;
}
struct Library
{
    int numBook = 0,  numUser = 0;
    Book Books[102];
    User Users[102];
    bool checkIfPref(string &_first, string &_second){
        if(_first.size() > _second.size()) return false;
        for (int i = 0; i < _first.size(); i++)
        {
            if(_first[i] != _second[i]) return false;
        }
        return true;
    }
    
    int searchUserIndex(string _name){
        int pos = -1;
        for (int i = 0; i < numUser; i++)
        {
            if(Users[i].name == _name){
                pos = i; break;
            }
        }
        return pos;
    }
    int searchBookIndex(string _name){
        int pos = -1;
        for (int i = 0; i < numBook; i++)
        {
            if(Books[i].name == _name){
                pos = i; break;
            }
        }
        return pos;
    }
    int searchLeftString(int start, int end, string &_name){
        int left = start, right = end, pos = -1;
        while(right >= left){
            int mid = (left + right) / 2;
            if(checkIfPref(_name, Books[mid].name)){
                right = mid - 1;
                pos = mid;
            } else{
                if(_name < Books[mid].name){
                    right = mid - 1;
                } else
                    left = mid + 1;
            }
        }
        return pos;
    }
    int searchRightString(int start, int end, string &_name){
        int left = start, right = end, pos = -1;
        while(right >= left){
            int mid = (left + right) / 2;
            if(checkIfPref(_name, Books[mid].name)){
                left = mid + 1;
                pos = mid;
            } else{
                if(_name < Books[mid].name){
                    right = mid - 1;
                } else
                    left = mid + 1;
            }
        }
        return pos;
    }
    
    // Adding Book 
    void addingBook(int _id, string _name, int _quantity){
        Books[numBook++].makeValue(_quantity, 0, _id, _name);
    }
    // Adding Users
    void addingUser(string _name, int _national_id){
        Users[numUser++].makeValue(_name, _national_id);
    }
    void PrintRangeInBooks(int left, int right){
        for (int i = left; i <= right; i++)
        {
            cout << Books[i].name << endl;
        }
    }
    void printBorrowByBookName(string &_name){
        int numPrint = 0;
        if(searchBookIndex(_name) == -1){
            invalidname();
            return;
        }
        for (int i = 0; i < numUser; i++)
        {
            if(Users[i].SearchBook(_name) != -1){
                cout << Users[i].name << endl;
                numPrint++;
            }
        }
        if(!numPrint){
            cout << "No one borrowed this book, please try again.." << endl;
        }
    }
    void sortBookbyId(){
        sort(Books, Books + numBook, sortByid);
    }
    void sortBookbyName(){
        sort(Books, Books + numBook, sortByName);
    }
    void printBook(){
        for (int i = 0; i < numBook; i++)
        {
            printBook(Books[i]);
        }
    }
    void printUser(){
        for (int i = 0; i < numUser; i++)
        {
            printUser(Users[i]);
        }
    }
    void printBook(Book &_book){
        cout << "id = " << _book.id << ", name = " << _book.name << ",  total_quantity = " << _book.num_book <<
             ", total_borrow = " << _book.num_borrrow << endl;
    }
    void printUser(User &user){
        cout << "Name = " << user.name << ", id = " << user.national_id << ", borrowed books = ";
        for (int i = 0; i < user.num_borrrow; i++)
        {
            cout << user.borrowedBook[i].id << " ";
        }
        cout << endl;
    }
    void invalidname(){
        cout << "Invalid Book / User Name, please try again..." << endl;
    }
    // User borrow a book  
    void userBorrowBook(string _userName, string _bookName){
        int indexBook = searchBookIndex(_bookName), indexUser = searchUserIndex(_userName); // Searching for the index of book / user in array.
        if(indexBook != -1 && indexUser != -1){ // Check if name of User or Book are valid 
            if(Books[indexBook].num_book > 0){ // Check if there enough quantity of this book
                Books[indexBook].num_book--, Books[indexBook].num_borrrow++;
                Users[indexUser].makeBorrow(Books[indexBook]);
            } else{
                cout << "You can't borrow this book right now, please try again later ...." << endl;
            }
        } else{
            invalidname();
        }
    }
    // User return a book
    void userReturnBook(string _userName, string _bookName){
        int indexBook = searchBookIndex(_bookName), indexUser = searchUserIndex(_userName); // Searching for the index of book / user in array.
        if(indexBook != -1 && indexUser != -1){ // Check if name of User or Book are valid 
        int indexBookInUser = Users[indexUser].checkValidBorrowedBook(_bookName);
            if(indexBookInUser != -1){ // Check if the book is already borrwed by the user of not
                Books[indexBook].num_book++, Books[indexBook].num_borrrow--;
                Users[indexUser].makeReturn(indexBookInUser);
            } else{
                cout << "You didn't borrow this book before, please try again  ...." << endl;
            }
        } else{
            invalidname();
        }
    }
    void searchBookByPrefix(string &_name){
        sort(Books, Books + numBook, sortByName);
        int l = searchLeftString(0, numBook - 1, _name), r = searchRightString(max(l, 0), numBook - 1, _name);
        if(l != -1 && r != -1){
            PrintRangeInBooks(l, r);
        } else{
            invalidname();
        }
     } 
};

int main(){
    Library mohamedLibrary;
    while(true){
        cout << "1) add_book\n" 
        << "2) serch books by prefix\n" 
        << "3) print who borrowed books by name\n" 
        << "4) print books by id\n" 
        << "5) print books by name\n" 
        << "6) add user\n" 
        << "7) user borrow book\n" 
        << "8) user return book\n" 
        << "9) print users\n" 
        << "10) exit" << endl;
        int operationNum; cin >> operationNum;
        if(operationNum == 10){
            cout << "Thanks for Using our System, Bye";
            break;
        }
        if(operationNum == 1){
            int id , quantity;
            string name;
            cout << "Enter The book (ID, Name, Quantity)" << endl;
            cin >> id >> name >> quantity;
            mohamedLibrary.addingBook(id, name, quantity);
        } else if(operationNum == 2){
            cout << "Enter Name of the book: " << endl;
            string name; cin >> name;
            mohamedLibrary.searchBookByPrefix(name);
        } else if(operationNum == 3){
            cout << "Enter name of the book: " << endl;
            string name; cin >> name;
            mohamedLibrary.printBorrowByBookName(name);
        } else if(operationNum == 4){
            mohamedLibrary.sortBookbyId();
            mohamedLibrary.printBook();
        } else if(operationNum == 5){
            mohamedLibrary.sortBookbyName();
            mohamedLibrary.printBook();
        }  else if(operationNum == 6){
            string name; int id; 
            cout << "Enter User name: " << endl;
            cin >> name;
            cout << "Eneter User id: " << endl;
            cin >> id;
            mohamedLibrary.addingUser(name, id);
        } else if(operationNum == 7){
            string nameUser, nameBook; 
            cout << "Enter User name: " << endl;
            cin >> nameUser;
            cout << "Eneter Book name: " << endl;
            cin >> nameBook;
            mohamedLibrary.userBorrowBook(nameUser, nameBook);
        } else if(operationNum == 8){
            string nameUser, nameBook; 
            cout << "Enter User name: " << endl;
            cin >> nameUser;
            cout << "Eneter Book name: " << endl;
            cin >> nameBook;
            mohamedLibrary.userReturnBook(nameUser, nameBook);
        } else if(operationNum == 9){
            mohamedLibrary.printUser();
        }
    }
    return 0;
}