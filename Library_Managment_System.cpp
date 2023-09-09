#include<bits/stdc++.h>
using namespace std;
class Book{
public:
    string Bookname;
    string Bookauthor;
    string ISBN;
    bool check_out;
    Book (){}
    Book(string bn,string ba,string isb) : Bookname(bn), Bookauthor(ba), ISBN(isb), check_out(false) {} 
};

class Member{
public:
    string customername;
    string contactinfo;
    Member(){}
    Member(string cn,string ci) : customername(cn), contactinfo(ci) {}
};

class Borrowing {
public:
    int book_ind;
    int member_ind;
    time_t due_Date;
    Borrowing(){}
    Borrowing(int b, int m) : book_ind(b), member_ind(m) {
        time(&due_Date);
        due_Date += 28 * 24 * 60 * 60; 
    }
};


class functions : public Member, public Book, public Borrowing{
public:
    functions() {}
    vector<Book> books;
    vector<Borrowing> borrowings;
    vector<Member> members;
    void add_book(){
        string bookname,bookauthor,isbn;
        cout<<"Enter the Name of the book : ";
        cin.ignore();
        getline(cin,bookname);
        cout<<"Enter the Author of the Book : ";
        getline(cin,bookauthor);
        cout<<"Enter the ISBN code of the Book : ";
        cin>>isbn;
        Book book(bookname,bookauthor,isbn);
        books.push_back(book);
        cout<<"Books have Been Added successfully"<<endl;
        cout<<endl;
    }

    void display_book(){
        cout << "Book List:" << endl;
        for (int i = 0; i < books.size(); ++i) {
            cout << "Index: " << i << endl;
            cout << "Title: " << books[i].Bookname << endl;
            cout << "Author: " << books[i].Bookauthor << endl;
            cout << "ISBN: " << books[i].ISBN << endl;
            cout << "Status: " << (books[i].check_out ? "Available" : "Checked Out") << endl;
            cout<<"endl";
        }
    }

    void delete_book(){
        int del_ind;
        cout<<"Enter the index of the book you want to delete";
        cin>>del_ind;
        if(del_ind>=0 && del_ind<=books.size()){
            if(books[del_ind].check_out){
                books.erase(books.begin()+del_ind);
                cout<<"Books has been deleted successfully"<<endl;
            }
            else{
                cout<<"Return the book first! In order to delete it"<<endl;
            }
        }
        else{
            cout<<"Invalid Index"<<endl;
        }
    }

    // Borrow_Managment
    void borrowBook() {
        int bookIndex, memberIndex;
        cout << "Enter the index of the book to borrow: ";
        cin >> bookIndex;

        if (bookIndex >= 0 && bookIndex < books.size() && books[bookIndex].check_out) {
            cout << "Enter the index of the member borrowing the book: ";
            cin >> memberIndex;

            if (memberIndex >= 0 && memberIndex < members.size()) {
                borrowings.push_back(Borrowing(bookIndex, memberIndex));
                books[bookIndex].check_out = false;
                cout << "Book successfully borrowed!" << endl;
                cout << "Due Date: " << ctime(&borrowings.back().due_Date);
            } else {
                cout << "Invalid member index." << endl;
            }
        } 
        else {
            cout << "Invalid book index or the book is already checked out." << endl;
        }
    }

    void returnBook() {
        int borrow_ind;
        cout << "Enter the index of the borrowing record to return: ";
        cin >> borrow_ind;
        if (borrow_ind >= 0 && borrow_ind < borrowings.size()) {
            int bookIndex = borrowings[borrow_ind].book_ind;
            books[bookIndex].check_out = true;
            // cout << "Book successfully returned!" << endl;
        } 
        else {
            cout << "Invalid borrowing record index." << endl;
        }
    }

    // member_managment
    void add_member(){
        string name,contact_info;
        cout<<"enter Member name";
        cin.ignore();
        getline(cin,name);
        cout<<"Enter contact Information";
        getline(cin,contact_info);
        Member memb(name,contact_info);
        members.push_back(memb);
        cout<<"Member added successfully"<<endl;
    }

    void display_member(){
        for(int i=0;i<members.size();i++){
            cout<<"NAME :: "<<members[i].customername<<endl;
            cout<<"Customer Contact :: "<<members[i].contactinfo<<endl;
            cout<<endl;

        }
    }

    void remove_member(){
        int remove_ind;
        cout<<"Enter the index of the member you want to remove";
        cin>>remove_ind;
        if(remove_ind>=0 && remove_ind <members.size()){
            bool ispossible=true;
            for(int i=0;i<borrowings.size();i++){
                if(borrowings[i].member_ind==remove_ind){
                    ispossible=false;
                    cout<<"Return all books first"<<endl;
                    break;
                }
            }
            if(ispossible){
                members.erase(members.begin()+remove_ind);
                cout<<"member deleted succesfully "<<endl;
            }
            else{
                cout<<"Invalid Index!"<<endl;
            }
        }
    }    
};
int main()
{
    int choice;
    functions *obj1= new functions();
    while (true) {
        cout << "Library Management System" << endl;
        cout << "1. Add Book" << endl;
        cout << "2. Display Books" << endl;
        cout << "3. Remove Books" <<endl;
        cout << "4. Add Member" << endl;
        cout << "5. Display Members" << endl;
        cout << "6. Remove Members " <<endl;
        cout << "7. Borrow book "<< endl;
        cout << "8. return Book" <<endl; 
        cout << "9. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                obj1->add_book();
                break;
            case 2:
                obj1->display_book();
                break;
            case 3:
                obj1->delete_book();
            case 4:
                obj1->add_member();
                break;
            case 5:
                obj1->display_member();
                break;
            case 6:
                obj1->remove_member();
                break;
            case 7:
                obj1->borrowBook();
                break;
            case 8:
                obj1->returnBook();
                break;
            case 9:
                exit(0);
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
    
}