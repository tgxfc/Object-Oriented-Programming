#include <iostream>
#include <string.h>
#include <cstdlib>
#include <vector>
#include <string>

using namespace std;

//место за вашиот код
class Oglas{
private:
    string naslov;
    string kategorija;
    string opis;
    float cena;
public:
    Oglas(string naslov, string kategorija, string opis, int cena)
    : naslov(naslov), kategorija(kategorija), opis(opis), cena(cena) {}

    bool operator>(Oglas &o)
    {
        return cena>o.cena;
    }

    friend ostream &operator<<(ostream &os, Oglas &o)
    {
        os<<o.naslov<<endl;
        os<<o.opis<<endl;
        os<<o.cena<<" evra"<<endl;
        return os;
    }

    float getCena() {
        return cena;
    }

    string getKategorija() {
        return kategorija;
    }
};

class NegativnaVrednost{
public:
    void print()
    {
        cout<<"Oglasot ima nevalidna vrednost za cenata i nema da bide evidentiran!"<<endl;
    }
};

class Oglasnik{
private:
    string ime;
    vector<Oglas> oglasi;
    int n;
public:
    Oglasnik(string ime)
    : ime(ime)
    {
        this->oglasi.clear();
        this->n=0;
    }

    Oglasnik &operator+=(Oglas &o)
    {
        if(o.getCena()<0)
        {
            throw NegativnaVrednost();
        }
        oglasi.push_back(o);
    }

    friend ostream &operator<<(ostream &os, Oglasnik &o)
    {
        os<<o.ime<<endl;
        for(int i=0; i<o.oglasi.size(); i++)
        {
            os<<o.oglasi[i]<<endl;
        }
        return os;
    }

    void oglasiOdKategorija(const string k)
    {
        for(int i=0; i<oglasi.size(); i++)
        {
            if(oglasi[i].getKategorija()==k)
            {
                cout<<oglasi[i]<<endl;
            }
        }
    }

    void najniskaCena()
    {
        int index=0;
        for(int i=0; i<oglasi.size(); i++)
        {
            if(oglasi[i].getCena()<oglasi[index].getCena())
            {
                index=i;
            }
        }
        cout<<oglasi[index];
    }
};



int main(){

    char naslov[50];
    char kategorija[30];
    char opis[100];
    float cena;
    char naziv[50];
    char k[30];
    int n;

    int tip;
    cin>>tip;

    if (tip==1){
        cout<<"-----Test Oglas & operator <<-----" <<endl;
        cin.get();
        cin.getline(naslov,49);
        cin.getline(kategorija,29);
        cin.getline(opis,99);
        cin>>cena;
        Oglas o(naslov, kategorija, opis, cena);
        cout<<o;
    }
    else if (tip==2){
        cout<<"-----Test Oglas & operator > -----" <<endl;
        cin.get();
        cin.getline(naslov,49);
        cin.getline(kategorija,29);
        cin.getline(opis,99);
        cin>>cena;
        Oglas o1(naslov, kategorija, opis, cena);
        cin.get();
        cin.getline(naslov,49);
        cin.getline(kategorija,29);
        cin.getline(opis,99);
        cin>>cena;
        Oglas o2(naslov, kategorija, opis, cena);
        if (o1>o2) cout<<"Prviot oglas e poskap."<<endl;
        else cout<<"Prviot oglas ne e poskap."<<endl;
    }
    else if (tip==3){
        cout<<"-----Test Oglasnik, operator +=, operator << -----" <<endl ;
        cin.get();
        cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
            Oglas o(naslov, kategorija, opis, cena);
            try{
                ogl+=o;
            }catch(NegativnaVrednost &ex){
                ex.print();
            }
        }
        cout<<ogl;
    }
    else if (tip==4){
        cout<<"-----Test oglasOdKategorija -----" <<endl ;
        cin.get();
        cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
            Oglas o(naslov, kategorija, opis, cena);
            try{
                ogl+=o;
            }catch(NegativnaVrednost &ex){
                ex.print();
            }
        }
        cin.get();
        cin.getline(k,29);
        cout<<"Oglasi od kategorijata: " <<k<<endl;
        ogl.oglasiOdKategorija(k);

    }
    else if (tip==5){
        cout<<"-----Test Exception -----" <<endl ;
        cin.get();
        cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
            Oglas o(naslov, kategorija, opis, cena);
            try{
                ogl+=o;
            }catch(NegativnaVrednost &ex){
                ex.print();
            }
        }
        cout<<ogl;

    }
    else if (tip==6){
        cout<<"-----Test najniskaCena -----" <<endl ;
        cin.get();
        cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
            Oglas o(naslov, kategorija, opis, cena);
            try{
                ogl+=o;
            }catch(NegativnaVrednost &ex){
                ex.print();
            }
        }
        cout<<"Oglas so najniska cena:"<<endl;
        ogl.najniskaCena();

    }
    else if (tip==7){
        cout<<"-----Test All -----" <<endl ;
        cin.get();
        cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
            Oglas o(naslov, kategorija, opis, cena);
            try{
                ogl+=o;
            }catch(NegativnaVrednost &ex){
                ex.print();
            }
        }
        cout<<ogl;

        cin.get();
        cin.get();
        cin.getline(k,29);
        cout<<"Oglasi od kategorijata: " <<k<<endl;
        ogl.oglasiOdKategorija(k);

        cout<<"Oglas so najniska cena:"<<endl;
        ogl.najniskaCena();

    }

    return 0;
}
