#include <iostream>
#include <cstring>
using namespace std;

enum Tip{
    LINUX, UNIX, WINDOWS
};

class OperativenSistem{
private:
    char *ime;
    float verzija;
    Tip tip;
    float golemina;
public:
    OperativenSistem()
    {
        this->ime=nullptr;
        this->verzija=0;
        this->tip=LINUX;
        this->golemina=0;
    }
    OperativenSistem(char *ime, float verzija, Tip tip, float golemina)
    {
        this->ime=new char[strlen(ime)+1];
        strcpy(this->ime,ime);
        this->verzija=verzija;
        this->tip=tip;
        this->golemina=golemina;
    }
    OperativenSistem(const OperativenSistem &cc)
    {
        this->ime=new char[strlen(cc.ime)+1];
        strcpy(this->ime,cc.ime);
        this->verzija=cc.verzija;
        this->tip=cc.tip;
        this->golemina=cc.golemina;
    }
    OperativenSistem &operator=(const OperativenSistem &cc)
    {
        if(this==&cc)
        {
            return *this;
        }
        this->ime=new char[strlen(cc.ime)+1];
        strcpy(this->ime,cc.ime);
        this->verzija=cc.verzija;
        this->tip=cc.tip;
        this->golemina=cc.golemina;
        return *this;
    }

    void pecati()
    {
        cout<<"Ime: "<<ime<<" Verzija: "<<verzija<<" Tip: "<<(Tip)tip<<" Golemina:"<<golemina<<"GB"<<endl;
    }
    bool ednakviSe(const OperativenSistem &os)
    {
        if(strcmp(this->ime,os.ime)==0 && this->verzija==os.verzija && this->tip==os.tip && this->golemina==os.golemina){return true;}
        return false;
    }
    int sporediVerzija(const OperativenSistem &os)
    {
        if(this->verzija==os.verzija){return 0;}
        if(this->verzija>os.verzija){return 1;}
        if(this->verzija<os.verzija){return -1;}
    }
    bool istaFamilija(const OperativenSistem &sporedba)
    {
        if(strcmp(this->ime,sporedba.ime)==0 && this->tip==sporedba.tip){return true;}
        return false;
    }

    ~OperativenSistem()
    {
        delete [] ime;
    }
};

class Repozitorium {
private:
    char ime[30];
    OperativenSistem *os;
    int n;
public:
    Repozitorium() {
        strcpy(this->ime, "");
        this->os = nullptr;
        this->n = 0;
    }

    Repozitorium(char *ime) {
        strcpy(this->ime, ime);
        this->os = nullptr;
        this->n = 0;
    }

    Repozitorium(const Repozitorium &cc) {
        strcpy(this->ime, cc.ime);
        delete[] os;
        this->os = new OperativenSistem[cc.n];
        for (int i = 0; i < cc.n; i++) {
            this->os[i] = cc.os[i];
        }
        this->n = cc.n;
    }

    Repozitorium &operator=(const Repozitorium &cc) {
        if (this == &cc) {
            return *this;
        }
        strcpy(this->ime, cc.ime);
        delete[] os;
        this->os = new OperativenSistem[cc.n];
        for (int i = 0; i < cc.n; i++) {
            this->os[i] = cc.os[i];
        }
        this->n = cc.n;
        return *this;
    }

    void pecatiOperativniSistemi()
    {
        cout << "Repozitorium: " << ime << endl;
        for (int i = 0; i < n; i++)
        {
            os[i].pecati();
        }
    }

    void izbrishi(const OperativenSistem &operativenSistem)
    {
        int index=0;
        for(int i=0; i<n; i++)
        {
            if(os[i].ednakviSe(operativenSistem))
            {
                index=i;
                break;
            }
        }
        if(index!=0) {
            for (int i = index; i < n - 1; i++)
            {
                os[i] = os[i + 1];
            }
            n--;
        }
    }
    void dodadi(const OperativenSistem &nov)
    {
        for(int i=0; i<n; i++)
        {
            if(os[i].istaFamilija(nov))
            {
                if(os[i].sporediVerzija(nov)==-1)
                {
                    os[i]=nov;
                    break;
                }
            }
        }
        OperativenSistem *temp = new OperativenSistem[n + 1];
        for (int i = 0; i < n; i++)
        {
            temp[i] = os[i];
        }
        temp[n++] = nov;
        delete[] os;
        os = new OperativenSistem[n];
        for (int i = 0; i < n; i++)
        {
            os[i] = temp[i];
        }
    }

    ~Repozitorium()
    {
        delete [] os;
    }
};

int main() {
    char repoName[20];
    cin>>repoName;
    Repozitorium repozitorium=Repozitorium(repoName);
    int brojOperativniSistemi = 0;
    cin>>brojOperativniSistemi;
    char ime[20];
    float verzija;
    int tip;
    float golemina;
    for (int i = 0; i<brojOperativniSistemi; i++){
        cin>>ime;
        cin>>verzija;
        cin>>tip;
        cin>>golemina;
        OperativenSistem os = OperativenSistem(ime, verzija, (Tip)tip, golemina);
        repozitorium.dodadi(os);
    }

    repozitorium.pecatiOperativniSistemi();
    cin>>ime;
    cin>>verzija;
    cin>>tip;
    cin>>golemina;
    OperativenSistem os = OperativenSistem(ime, verzija, (Tip)tip, golemina);
    cout<<"=====Brishenje na operativen sistem====="<<endl;
    repozitorium.izbrishi(os);
    repozitorium.pecatiOperativniSistemi();
    return 0;
}
