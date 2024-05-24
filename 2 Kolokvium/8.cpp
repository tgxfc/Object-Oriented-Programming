#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

class Trud{
protected:
    char znak;
    int godinaIzdavanje;
public:
    Trud()
    {
        this->znak=0;
        this->godinaIzdavanje=0;
    }
    Trud(char znak, int godinaIzdavanje)
    {
        this->znak=znak;
        this->godinaIzdavanje=godinaIzdavanje;
    }

    char getZnak()
    {
        return znak;
    }

    int getGodinaIzdavanje() {
        return godinaIzdavanje;
    }

    friend istream &operator>>(istream &is, Trud &t)
    {
        is>>t.znak;
        is>>t.godinaIzdavanje;
        return is;
    }

};

class Student{
protected:
    char ime[30];
    int indeks;
    int godinaUpis;
    vector<int> predmeti;
    int brPredmeti;
public:
    Student()
    {
        strcpy(this->ime,"");
        this->indeks=0;
        this->godinaUpis=0;
        this->predmeti.resize(0);
        this->brPredmeti=0;
    }
    Student(char *ime, int indeks, int godinaUpis, int *predmeti, int brPredmeti)
    {
        strcpy(this->ime,ime);
        this->indeks=indeks;
        this->godinaUpis=godinaUpis;
        this->predmeti.resize(brPredmeti);
        this->predmeti.assign(predmeti, predmeti+brPredmeti);
        this->brPredmeti=brPredmeti;
    }

    virtual float rang()
    {
        int ocena=0;
        for(int i=0; i<brPredmeti; i++)
        {
            ocena+=predmeti[i];
        }
        return (float)ocena/brPredmeti;
    }

    friend ostream &operator<<(ostream &os, Student &s)
    {
        os<<s.indeks<<" "<<s.ime<<" "<<s.godinaUpis<<" "<<s.rang()<<endl;
        return os;
    }

    int getIndeks()
    {
        return indeks;
    }
};

class Exception{
public:
    void print()
    {
        cout<<"Ne moze da se vnese dadeniot trud"<<endl;
    }
};

class PhDStudent : public Student{
private:
    vector<Trud> trudovi;
    int n;
    static int konferenciskiPoeni;
    static int spisaniePoeni;
public:
    PhDStudent()
    {
        trudovi.resize(0);
        this->n=0;
    }
    PhDStudent(char *ime, int indeks, int godinaUpis, int *predmeti, int brPredmeti, Trud *trudovi, int n)
    : Student(ime, indeks, godinaUpis, predmeti,brPredmeti)
    {
        try {
            for (int i = 0; i < n; i++) {
                if (trudovi[i].getGodinaIzdavanje() < godinaUpis) {
                    throw Exception();
                }
            }
        } catch (Exception &ex) {
            ex.print();
        }
        this->trudovi.assign(trudovi, trudovi + n);
        this->n = n;
    }

    float rang() override
    {
        float ocena=0;
        for(int i=0; i<brPredmeti; i++)
        {
            ocena+=predmeti[i];
        }
        ocena=(float)ocena/brPredmeti;

        float poeni=0;
        for(int i=0; i<n; i++)
        {
            if(tolower(trudovi[i].getZnak())=='c')
            {
                poeni+=konferenciskiPoeni;
            }
            else if(tolower(trudovi[i].getZnak())=='j')
            {
                poeni+=spisaniePoeni;
            }
        }

        return ocena+poeni;
    }

    PhDStudent &operator+=(Trud &t)
    {
        if(t.getGodinaIzdavanje()<godinaUpis)
        {
            throw Exception();
        }
        else
        {
            trudovi.push_back(t);
        }

        return *this;
    }

    static void setKonferenciskiPoeni(int poeni) {
        konferenciskiPoeni = poeni;
    }

    static void setSpisaniePoeni(int poeni) {
        spisaniePoeni = poeni;
    }
};

int PhDStudent::konferenciskiPoeni = 1;
int PhDStudent::spisaniePoeni = 3;

int main(){
    int testCase;
    cin >> testCase;

    int god, indeks, n, god_tr, m, n_tr;
    int izbor; //0 za Student, 1 za PhDStudent
    char ime[30];
    int oceni[50];
    char tip;
    Trud trud[50];

    if (testCase == 1){
        cout << "===== Testiranje na klasite ======" << endl;
        cin >> ime;
        cin >> indeks;
        cin >> god;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> oceni[j];
        Student s(ime, indeks, god, oceni, n);
        cout << s;

        cin >> ime;
        cin >> indeks;
        cin >> god;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> oceni[j];
        cin >> n_tr;
        for (int j = 0; j < n_tr; j++){
            cin >> tip;
            cin >> god_tr;
            Trud t(tip, god_tr);
            trud[j] = t;
        }
        PhDStudent phd(ime, indeks, god, oceni, n, trud, n_tr);
        cout << phd;
    }
    if (testCase == 2){
        cout << "===== Testiranje na operatorot += ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i<m; i++){
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0){
                niza[i] = new Student(ime, indeks, god, oceni, n);
            }
            else{
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++){
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        // dodavanje nov trud za PhD student spored indeks
        Trud t;
        cin >> indeks;
        cin >> t;

        int ind=-1;
        for(int i=0; i<m; i++)
        {
            if(dynamic_cast<PhDStudent*>(niza[i])!= nullptr)
            {
                if(niza[i]->getIndeks()==indeks)
                {
                    ind=i;
                }
            }

        }
        if(ind==-1)
        {
            cout<<"Ne postoi PhD student so indeks "<<indeks<<endl;
        }

        if(ind!=-1)
        {
            try{
                PhDStudent *phdStudent = dynamic_cast<PhDStudent*>(niza[ind]);
                if(phdStudent){
                    *phdStudent+=t;
                }
            } catch(Exception &ex){
                ex.print();
            }
        }

        // vmetnete go kodot za dodavanje nov trud so pomos na operatorot +=


        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    if (testCase == 3){
        cout << "===== Testiranje na operatorot += ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i<m; i++){
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0){
                niza[i] = new Student(ime, indeks, god, oceni, n);
            }
            else{
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++){
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        // dodavanje nov trud za PhD student spored indeks
        Trud t;
        cin >> indeks;
        cin >> t;

        int ind=-1;
        for(int i=0; i<m; i++)
        {
            if(dynamic_cast<PhDStudent*>(niza[i])!= nullptr)
            {
                if(niza[i]->getIndeks()==indeks)
                {
                    ind=i;
                }
            }

        }
        if(ind==-1)
        {
            cout<<"Ne postoi PhD student so indeks "<<indeks<<endl;
        }

        try{
            PhDStudent *phdStudent = dynamic_cast<PhDStudent*>(niza[ind]);
            if(phdStudent){
                *phdStudent+=t;
            }
        } catch(Exception &ex){
            ex.print();
        }
        // vmetnete go kodot za dodavanje nov trud so pomos na operatorot += od Testcase 2


        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    if (testCase == 4){
        cout << "===== Testiranje na isklucoci ======" << endl;
        cin >> ime;
        cin >> indeks;
        cin >> god;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> oceni[j];
        cin >> n_tr;
        for (int j = 0; j < n_tr; j++){
            cin >> tip;
            cin >> god_tr;
            Trud t(tip, god_tr);
            trud[j] = t;
        }
        PhDStudent phd(ime, indeks, god, oceni, n, trud, n_tr);
        cout << phd;


    }
    if (testCase == 5){
        cout << "===== Testiranje na isklucoci ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i<m; i++){
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0){
                niza[i] = new Student(ime, indeks, god, oceni, n);
            }
            else{
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++){
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        // dodavanje nov trud za PhD student spored indeks
        Trud t;
        cin >> indeks;
        cin >> t;

        int ind=-1;
        for(int i=0; i<m; i++)
        {
            if(dynamic_cast<PhDStudent*>(niza[i])!= nullptr)
            {
                if(niza[i]->getIndeks()==indeks)
                {
                    ind=i;
                }
            }

        }
        if(ind==-1)
        {
            cout<<"Ne postoi PhD student so indeks "<<indeks<<endl;
        }

        if(ind!=-1)
        {
            try{
                PhDStudent *phdStudent = dynamic_cast<PhDStudent*>(niza[ind]);
                if(phdStudent){
                    *phdStudent+=t;
                }
            } catch(Exception &ex){
                ex.print();
            }
        }
        // vmetnete go kodot za dodavanje nov trud so pomos na operatorot += i spravete se so isklucokot

        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    if (testCase == 6){
        cout << "===== Testiranje na static clenovi ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i<m; i++){
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0){
                niza[i] = new Student(ime, indeks, god, oceni, n);
            }
            else{
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++){
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        int conf, journal;
        cin >> conf;
        cin >> journal;

        //postavete gi soodvetnite vrednosti za statickite promenlivi
        PhDStudent::setKonferenciskiPoeni(conf);
        PhDStudent::setSpisaniePoeni(journal);

        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }

    return 0;
}
