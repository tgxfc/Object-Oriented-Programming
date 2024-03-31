#include <iostream>
#include <cstring>
using namespace std;

class Ucesnik{
private:
    char *ime;
    bool pol;
    int vozrast;
public:
    Ucesnik()
    {
        this->ime = new char[0];
        strcpy(this->ime, "");
        this->pol=false;
        this->vozrast=0;
    }
    Ucesnik(char *ime, bool pol, int vozrast)
    {
        this->ime=new char[strlen(ime)+1];
        strcpy(this->ime,ime);
        this->pol=pol;
        this->vozrast=vozrast;
    }
    Ucesnik(const Ucesnik &cc)
    {
        this->ime=new char[strlen(cc.ime)+1];
        strcpy(this->ime,cc.ime);
        this->pol=cc.pol;
        this->vozrast=cc.vozrast;
    }

    Ucesnik &operator=(const Ucesnik &o)
    {
        if(this == &o)
        {
            return *this;
        }
        delete[] this->ime;
        this->ime=new char[strlen(o.ime)+1];
        strcpy(this->ime,o.ime);
        this->pol=o.pol;
        this->vozrast=o.vozrast;
        return *this;
    }

    bool operator>(const Ucesnik &o)
    {
        return o.vozrast > this->vozrast;
    }

    friend ostream &operator<<(ostream &o, Ucesnik &u)
    {
        o<<u.ime<<endl;
        o<<(u.pol ? "maski" : "zenski")<<endl;
        o<<u.vozrast<<endl;
    }

    int getVozrast() {return vozrast;}

    ~Ucesnik()
    {
        delete [] ime;
    }
};

class Maraton{
private:
    char lokacija[100];
    Ucesnik *ucesnik;
    int n;
public:
    Maraton()
    {
        strcpy(this->lokacija,"");
        this->ucesnik=nullptr;
        this->n=0;
    }
    Maraton(char *lokacija)
    {
        strcpy(this->lokacija,lokacija);
        this->ucesnik=nullptr;
        this->n=0;
    }
    Maraton(const Maraton &cc)
    {
        strcpy(this->lokacija,cc.lokacija);
        this->ucesnik=cc.ucesnik;
        this->n=cc.n;
    }

    Maraton &operator+=(const Ucesnik &o)
    {
        Ucesnik *temp=new Ucesnik[n+1];
        for(int i=0; i<n; i++)
        {
            temp[i]=ucesnik[i];
        }
        temp[n++]=o;
        delete [] ucesnik;
        ucesnik = temp;
        return *this;
    }

    float prosecnoVozrast()
    {
        float suma=0;
        for(int i=0; i<n; i++)
        {
            suma+=ucesnik[i].getVozrast();
        }
        return (float)suma/n;
    }

    void pecatiPomladi(const Ucesnik &u)
    {
        for(int i=0; i<n; i++)
        {
            if(ucesnik[i]>u)
            {
                cout<<ucesnik[i];
            }
        }
    }

    ~Maraton()
    {
        delete [] ucesnik;
    }
};
// vashiot kod ovde

int main() {
    char ime[100];
    bool maski;
    int vozrast, n;
    cin >> n;
    char lokacija[100];
    cin >> lokacija;
    Maraton m(lokacija);
    Ucesnik **u = new Ucesnik*[n];
    for(int i = 0; i < n; ++i) {
        cin >> ime >> maski >> vozrast;
        u[i] = new Ucesnik(ime, maski, vozrast);
        m += *u[i];
    }
    m.pecatiPomladi(*u[n - 1]);
    cout << m.prosecnoVozrast() << endl;
    for(int i = 0; i < n; ++i) {
        delete u[i];
    }
    delete [] u;
    return 0;
}
