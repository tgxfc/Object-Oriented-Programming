#include<iostream>
#include<cstring>
using namespace std;

class Chocolate {
private:
    char name[100];
    int price;
public:
    Chocolate() {
        strcpy(this->name, "");
        this->price = 0;
    }

    Chocolate(char *name, int price) {
        strcpy(this->name, name);
        this->price = price;
    }

    Chocolate(const Chocolate &cc)
    {
        strcpy(this->name, cc.name);
        this->price = cc.price;
    }
    Chocolate &operator=(const Chocolate &cc)
    {
        if(this==&cc)
        {
            return *this;
        }
        strcpy(this->name, cc.name);
        this->price = cc.price;
        return *this;
    }

    friend ostream &operator<<(ostream &os, const Chocolate &cc)
    {
        os<<cc.name<<": $"<<cc.price;
        return os;
    }

    int getPrice(){return price;}

    ~Chocolate() {}
};

class ChocolateFactory{
private:
    Chocolate *products;
    int *weeklyProducts;
    int numProducts;
public:
    ChocolateFactory()
    {
        this->products=nullptr;
        this->weeklyProducts=nullptr;
        this->numProducts=0;
    }
    ChocolateFactory(Chocolate *products, int *weeklyProducts, int numProducts)
    {
        this->numProducts=numProducts;
        this->products=new Chocolate[numProducts];
        this->weeklyProducts=new int[numProducts];
        for(int i=0; i<numProducts; i++)
        {
            this->products[i]=products[i];
            this->weeklyProducts[i]=weeklyProducts[i];
        }
    }
    ChocolateFactory(const ChocolateFactory &cc)
    {
        for(int i=0; i<cc.numProducts; i++)
        {
            this->products[i]=cc.products[i];
            this->weeklyProducts[i]=cc.weeklyProducts[i];
        }
        this->numProducts=cc.numProducts;
    }
    ChocolateFactory &operator=(const ChocolateFactory &cc)
    {
        if(this == &cc)
        {
            return *this;
        }
        delete[] products;
        delete[] weeklyProducts;
        this->numProducts = cc.numProducts;
        this->products = new Chocolate[numProducts];
        this->weeklyProducts = new int[numProducts];
        for (int i = 0; i < numProducts; i++) {
            this->products[i] = cc.products[i];
            this->weeklyProducts[i] = cc.weeklyProducts[i];
        }
        return *this;
    }

    int weeklyIncome() const
    {
        int suma=0;
        for(int i=0; i<numProducts; i++)
        {
            suma+=(products[i].getPrice()*weeklyProducts[i]);
        }

        return suma;
    }

    bool operator>(const ChocolateFactory &o) const
    {
        if(weeklyIncome()>o.weeklyIncome())
        {
            return true;
        }
        return false;
    }
    bool operator<(const ChocolateFactory &o) const
    {
        if(weeklyIncome()<o.weeklyIncome())
        {
            return true;
        }
        return false;
    }
    ChocolateFactory operator+(ChocolateFactory &o)
    {
        ChocolateFactory nov;
        nov.numProducts = numProducts + o.numProducts;
        nov.products = new Chocolate[nov.numProducts];
        nov.weeklyProducts = new int[nov.numProducts];
        for(int i = 0; i < numProducts; i++)
        {
            nov.products[i] = products[i];
            nov.weeklyProducts[i] = weeklyProducts[i];
        }
        for(int i = 0; i < o.numProducts; i++)
        {
            nov.products[numProducts + i] = o.products[i];
            nov.weeklyProducts[numProducts + i] = o.weeklyProducts[i];
        }
        return nov;
    }

    friend ostream &operator<<(ostream &os, const ChocolateFactory &cc)
    {
        for(int i=0; i<cc.numProducts; i++)
        {
            os<<cc.products[i]<<" x "<<cc.weeklyProducts[i]<<endl;
        }
        cout<<"$"<<cc.weeklyIncome()<<"/wk"<<endl;
        return os;
    }

    ~ChocolateFactory()
    {
        delete [] products;
        delete [] weeklyProducts;
    }
};

int main() {
    int testCase;
    char name[100];
    int price;

    Chocolate products[100];
    int weeklyProduction[100];

    cin >> testCase;
    if (testCase == 0) {
        cout<<"Testing Chocolate print operator:"<<endl;
        for (int i = 0; i < 10; ++i) {
            cin>>name>>price;
            cout<<Chocolate(name,price)<<endl;
        }
    }
    else if (testCase == 1) {
        cout<<"Testing ChocolateFactory print operator:"<<endl;

        for (int i = 0; i < 10; ++i) {
            cin>>name>>price;
            products[i] = Chocolate(name, price);
            cin>>weeklyProduction[i];
        }

        ChocolateFactory cf(products,weeklyProduction,10);
        cout<<cf<<endl;
    }
    else if (testCase == 2) {
        cout<<"Testing ChocolateFactory comparison operators:"<<endl;

        for (int i = 0; i < 3; ++i) {
            cin>>name>>price>>weeklyProduction[i];
            products[i] = Chocolate(name,price);
        }
        ChocolateFactory cf1 = ChocolateFactory(products,weeklyProduction,3);

        for (int i = 0; i < 4; ++i) {
            cin>>name>>price>>weeklyProduction[i];
            products[i] = Chocolate(name,price);
        }
        ChocolateFactory cf2 = ChocolateFactory(products,weeklyProduction,4);

        cout<<cf1<<cf2;

        cout<<"< operator: "<< (cf1<cf2 ? "PASS" : "FAIL") <<endl;
        cout<<"> operator: "<< (cf2>cf1 ? "PASS" : "FAIL") <<endl;
    }
    else if (testCase == 3) {
        cout<<"Testing ChocolateFactory sum operator:"<<endl;

        for (int i = 0; i < 5; ++i) {
            cin>>name>>price>>weeklyProduction[i];
            products[i] = Chocolate(name,price);
        }
        ChocolateFactory cf1 = ChocolateFactory(products,weeklyProduction,5);
        for (int i = 0; i < 5; ++i) {
            cin>>name>>price>>weeklyProduction[i];
            products[i] = Chocolate(name,price);
        }
        ChocolateFactory cf2 = ChocolateFactory(products,weeklyProduction,5);

        cout<<cf1+cf2;
    }
}
