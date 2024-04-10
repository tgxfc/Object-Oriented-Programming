#include<iostream>
#include<cstring>
using namespace std;

// vasiot kod za klasite ovde
class StockRecord{
private:
    char ID[12];
    char ime[50];
    float kupena_cena;
    float momentalna_cena;
    int brAkcii;
public:
    StockRecord()
    {
        strcpy(this->ID,"");
        strcpy(this->ime,"");
        this->kupena_cena=0;
        this->momentalna_cena=0;
        this->brAkcii=0;
    }
    StockRecord(char *ID, char *ime, float kupena_cena, int brAkcii)
    {
        strcpy(this->ID,ID);
        strcpy(this->ime,ime);
        this->kupena_cena=kupena_cena;
        this->momentalna_cena=0;
        this->brAkcii=brAkcii;
    }
    StockRecord(const StockRecord &cc)
    {
        strcpy(this->ID,cc.ID);
        strcpy(this->ime,cc.ime);
        this->kupena_cena=cc.kupena_cena;
        this->momentalna_cena=cc.momentalna_cena;
        this->brAkcii=cc.brAkcii;
    }
    StockRecord &operator=(const StockRecord &cc)
    {
        if(this==&cc)
        {
            return *this;
        }
        strcpy(this->ID,cc.ID);
        strcpy(this->ime,cc.ime);
        this->kupena_cena=cc.kupena_cena;
        this->momentalna_cena=cc.momentalna_cena;
        this->brAkcii=cc.brAkcii;
        return *this;
    }

    void setNewPrice(double c){this->momentalna_cena=c;}
    double value(){return (double)brAkcii*momentalna_cena;}
    double profit(){return (double)brAkcii*(momentalna_cena-kupena_cena);}

    friend ostream &operator<<(ostream &os, StockRecord &o)
    {
        os<<o.ime<<" "<<o.brAkcii<<" "<<o.kupena_cena<<" "<<o.momentalna_cena<<" "<<o.profit()<<endl;
        return os;
    }

    ~StockRecord(){}
};

class Client{
private:
    char ime[60];
    int ID;
    StockRecord *stock;
    int nStock;
public:
    Client()
    {
        strcpy(this->ime,"");
        this->ID=0;
        this->stock=nullptr;
        this->nStock=0;
    }
    Client(char *ime, int ID)
    {
        strcpy(this->ime,ime);
        this->ID=ID;
        this->stock=nullptr;
        this->nStock=0;
    }
    Client(const Client &cc)
    {
        strcpy(this->ime,cc.ime);
        this->ID=cc.ID;
        delete [] this->stock;
        this->stock=new StockRecord[cc.nStock];
        for(int i=0; i<cc.nStock; i++)
        {
            this->stock[i]=cc.stock[i];
        }
        this->nStock=cc.nStock;
    }
    Client &operator=(Client &cc)
    {
        if (this == &cc)
        {
            return *this;
        }
        strcpy(this->ime,cc.ime);
        this->ID=cc.ID;
        delete [] this->stock;
        this->stock=new StockRecord[cc.nStock];
        for(int i=0; i<cc.nStock; i++)
        {
            this->stock[i]=cc.stock[i];
        }
        this->nStock=cc.nStock;
        return *this;
    }

    double totalValue()
    {
        double suma=0;
        for(int i=0; i<nStock; i++)
        {
            suma+=stock[i].value();
        }
        return suma;
    }

    Client &operator+=(StockRecord &c)
    {
        StockRecord *temp=new StockRecord[nStock+1];
        for(int i=0; i<nStock; i++)
        {
            temp[i]=stock[i];
        }
        temp[nStock++]=c;
        delete [] stock;
        stock=new StockRecord[nStock];
        for(int i=0; i<nStock; i++)
        {
            stock[i]=temp[i];
        }
        return *this;
    }

    friend ostream &operator<<(ostream &os, Client &o)
    {
        os<<o.ID<<" "<<o.totalValue()<<endl;
        for(int i=0; i<o.nStock; i++)
        {
            os<<o.stock[i];
        }
        return os;
    }

    ~Client()
    {
        delete [] stock;
    }
};


// ne menuvaj vo main-ot

int main(){

    int test;
    cin >> test;

    if(test == 1){
        double price;
        cout << "=====TEST NA KLASATA StockRecord=====" << endl;
        StockRecord sr("1", "Microsoft", 60.0, 100);
        cout << "Konstruktor OK" << endl;
        cin >> price;
        sr.setNewPrice(price);
        cout << "SET metoda OK" << endl;
    }
    else if(test == 2){
        cout << "=====TEST NA METODITE I OPERATOR << OD KLASATA StockRecord=====" << endl;
        char id[12], company[50];
        double price, newPrice;
        int n, shares;
        cin >> n;
        for(int i = 0; i < n; ++i){
            cin >> id;
            cin >> company;
            cin >> price;
            cin >> newPrice;
            cin >> shares;
            StockRecord sr(id, company, price, shares);
            sr.setNewPrice(newPrice);
            cout << sr.value() << endl;
            cout << sr;
        }
    }
    else if(test == 3){
        cout << "=====TEST NA KLASATA Client=====" << endl;
        char companyID[12], companyName[50], clientName[50];
        int clientID, n, shares;
        double oldPrice, newPrice;
        bool flag = true;
        cin >> clientName;
        cin >> clientID;
        cin >> n;
        Client c(clientName, clientID);
        cout << "Konstruktor OK" << endl;
        for(int i = 0; i < n; ++i){
            cin >> companyID;
            cin >> companyName;
            cin >> oldPrice;
            cin >> newPrice;
            cin >> shares;
            StockRecord sr(companyID, companyName, oldPrice, shares);
            sr.setNewPrice(newPrice);
            c += sr;
            if(flag){
                cout << "Operator += OK" << endl;
                flag = false;
            }
        }
        cout << c;
        cout << "Operator << OK" << endl;
    }
    return 0;

}
