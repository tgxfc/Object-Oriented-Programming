#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

#define MAX 50

enum typeC{
    standard, loyal, vip
};

class Customer{
private:
    char ime[MAX];
    char email[MAX];
    typeC tC;
    static int popust;
    static int dopPopust;
    int n;
public:
    Customer()
    {
        strcpy(this->ime,"");
        strcpy(this->email,"");
        this->tC=standard;
        this->n=0;
    }
    Customer(char *ime,char *email, typeC tC, int n)
    {
        strcpy(this->ime,ime);
        strcpy(this->email,email);
        this->tC=tC;
        this->popust=popust;
        this->dopPopust=dopPopust;
        this->n=n;
    }

    friend ostream &operator<<(ostream &os, Customer &c)
    {
        os<<c.ime<<endl;
        os<<c.email<<endl;
        os<<c.n<<endl;
        if(c.tC==standard){os<<"standard "<<0<<endl;}
        if(c.tC==loyal){os<<"loyal "<<c.popust<<endl;}
        if(c.tC==vip){os<<"vip "<<c.popust+c.dopPopust<<endl;}
        return os;
    }

    const char *getEmail() const {
        return email;
    }

    void setDiscount1(int disc)
    {
        this->popust=disc;
    }

    int getN()
    {
        return n;
    }

    void setTc(typeC tC)
    {
        this->tC=tC;
    }
    typeC getTC()
    {
        return tC;
    }
};

int Customer::dopPopust=20;
int Customer::popust=10;

class UserExistsException{
public:
    UserExistsException(){}

    void print()
    {
        cout<<"The user already exists in the list!"<<endl;
    }
};

class FINKI_bookstore{
private:
    vector<Customer> customers;
public:
    FINKI_bookstore(){
        this->customers.clear();
    }

    FINKI_bookstore &operator+=(Customer &c)
    {
        for(int i=0; i<customers.size(); i++)
        {
            if(strcmp(customers[i].getEmail(),c.getEmail())==0)
            {
                throw UserExistsException();
            }
        }

        customers.push_back(c);
        return *this;
    }

    friend ostream &operator<<(ostream &os, FINKI_bookstore &f)
    {
        for(int i=0; i<f.customers.size(); i++)
        {
            os<<f.customers[i];
        }
        return os;
    }

    void setCustomers(Customer *customers, int n)
    {
        this->customers.clear();
        for(int i=0; i<n; i++)
        {
            this->customers.push_back(customers[i]);
        }
    }

    void update()
    {
        for(int i=0; i<customers.size(); i++)
        {
            if(customers[i].getN()>=10 && customers[i].getTC()==loyal)
            {
                customers[i].setTc(vip);
            }else if(customers[i].getN()>=5 && customers[i].getTC()==standard)
            {
                customers[i].setTc(loyal);
            }
        }
    }
};

int main(){
    int testCase;
    cin >> testCase;

    char name[MAX];
    char email[MAX];
    int tC;
    int discount;
    int numProducts;


    if (testCase == 1){
        cout << "===== Test Case - Customer Class ======" << endl;
        cin.get();
        cin.getline(name,MAX);
        cin.getline(email,MAX);
        cin >> tC;
        cin >> numProducts;
        cout << "===== CONSTRUCTOR ======" << endl;
        Customer c(name, email, (typeC) tC, numProducts);
        cout << c;

    }

    if (testCase == 2){
        cout << "===== Test Case - Static Members ======" << endl;
        cin.get();
        cin.getline(name,MAX);
        cin.getline(email,MAX);
        cin >> tC;
        cin >> numProducts;
        cout << "===== CONSTRUCTOR ======" << endl;
        Customer c(name, email, (typeC) tC, numProducts);
        cout << c;

        c.setDiscount1(5);

        cout << c;
    }

    if (testCase == 3){
        cout << "===== Test Case - FINKI-bookstore ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,MAX);
            cin.getline(email,MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);

        cout << fc <<endl;
    }

    if (testCase == 4){
        cout << "===== Test Case - operator+= ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,MAX);
            cin.getline(email,MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);
        cout << "OPERATOR +=" << endl;
        cin.get();
        cin.getline(name,MAX);
        cin.getline(email,MAX);
        cin >> tC;
        cin >> numProducts;
        Customer c(name, email, (typeC) tC, numProducts);
        try{
            fc+=c;
        } catch(UserExistsException &ex){
            ex.print();
        }


        cout << fc;
    }

    if (testCase == 5){
        cout << "===== Test Case - operator+= (exception) ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,MAX);
            cin.getline(email,MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);
        cout << "OPERATOR +=" << endl;
        cin.get();
        cin.getline(name,MAX);
        cin.getline(email,MAX);
        cin >> tC;
        cin >> numProducts;
        Customer c(name,email,(typeC)tC,numProducts);
        try{
            fc+=c;
        } catch(UserExistsException &ex){
            ex.print();
        }

        cout << fc;
    }

    if (testCase == 6){
        cout << "===== Test Case - update method  ======" << endl << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,MAX);
            cin.getline(email,MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);

        cout << "Update:" << endl;
        fc.update();
        cout << fc;
    }
    return 0;

}
