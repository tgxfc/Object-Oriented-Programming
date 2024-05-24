#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

enum tip{
    mobilen, laptop
};

class Device{
private:
    char model[100];
    static float casovi;
    tip tipD;
    int godinaPr;
public:
    Device()
    {
        strcpy(this->model,"");
        this->tipD=mobilen;
        this->godinaPr=0;
    }
    Device(char *model, tip tipD, int godinaPr)
    {
        strcpy(this->model,model);
        this->tipD=tipD;
        this->godinaPr=godinaPr;
    }

    static void setPocetniCasovi(float n)
    {
        casovi=n;
    }

    float proverka()
    {
        float proverka=casovi;
        if(this->godinaPr>2015)
        {
            proverka+=2;
        }
        if(this->tipD==laptop)
        {
            proverka+=2;
        }

        return proverka;
    }

    friend ostream &operator<<(ostream &os, Device &d)
    {
        os<<d.model<<endl;
        if(d.tipD==mobilen){os<<"Mobilen ";}
        else if(d.tipD==laptop){os<<"Laptop ";}
        os<<d.proverka()<<endl;
    }

    int getGodinaPr()
    {
        return godinaPr;
    }

};

float Device::casovi=1;

class InvalidProductionDate{
public:
    void print()
    {
        cout<<"Невалидна година на производство"<<endl;
    }

};

class MobileServis{
private:
    char adresa[100];
    vector<Device> uredi;
    int n;
public:
    MobileServis()
    {
        strcpy(this->adresa,"");
        this->uredi.clear();
        this->n=0;
    }
    MobileServis(char *adresa)
    {
        strcpy(this->adresa,adresa);
    }

    MobileServis &operator+=(Device &d)
    {
        if(d.getGodinaPr()>2019 || d.getGodinaPr()<2000)
        {
            throw InvalidProductionDate();
        }
        else
        {
            this->uredi.push_back(d);
            this->n++;
        }
    }

    void pecatiCasovi()
    {
        cout<<"Ime: "<<adresa<<endl;
        for(int i=0; i<uredi.size(); i++)
        {
            cout<<uredi[i];
        }
    }
};

int main()
{
    int testCase;
    cin >> testCase;
    char ime[100];
    int tipDevice;
    int godina;
    int n;
    Device devices[50];
    if (testCase == 1){
        cout << "===== Testiranje na klasite ======" << endl;
        cin >> ime;
        cin >> tipDevice;
        cin >> godina;
        Device ig(ime,(tip)tipDevice,godina);
        cin>>ime;
        MobileServis t(ime);
        cout<<ig;
    }
    if (testCase == 2){
        cout << "===== Testiranje na operatorot += ======" << endl;
        cin>>ime;
        cin >> n;
        MobileServis t(ime);
        for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            try{
                t+=tmp;
            } catch(InvalidProductionDate &ex){
                ex.print();
            }
        }
        t.pecatiCasovi();
    }
    if (testCase == 3){
        cout << "===== Testiranje na isklucoci ======" << endl;
        cin>>ime;
        cin >> n;
        MobileServis t(ime);
        for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            try{
                t+=tmp;
            } catch(InvalidProductionDate &ex){
                ex.print();
            }
        }
        t.pecatiCasovi();
    }
    if (testCase == 4){
        cout <<"===== Testiranje na konstruktori ======"<<endl;
        cin>>ime;
        cin >> n;
        MobileServis t(ime);
        for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            try{
                t+=tmp;
            } catch(InvalidProductionDate &ex){
                ex.print();
            }
        }
        MobileServis t2 = t;
        t2.pecatiCasovi();
    }
    if (testCase == 5){
        cout << "===== Testiranje na static clenovi ======" << endl;
        cin>>ime;
        cin >> n;
        MobileServis t(ime);
        for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            try{
                t+=tmp;
            } catch(InvalidProductionDate &ex){
                ex.print();
            }
        }
        t.pecatiCasovi();
        cout << "===== Promena na static clenovi ======" << endl;
        Device::setPocetniCasovi(2);
        t.pecatiCasovi();
    }

    if (testCase == 6){
        cout << "===== Testiranje na kompletna funkcionalnost ======" << endl;
        cin>>ime;
        cin >> n;
        MobileServis t(ime);
        for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            try{
                t+=tmp;
            } catch(InvalidProductionDate &ex){
                ex.print();
            }

        }
        Device::setPocetniCasovi(3);
        MobileServis t2 = t;
        t2.pecatiCasovi();
    }

    return 0;

}

