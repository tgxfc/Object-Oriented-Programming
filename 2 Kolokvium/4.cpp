#include <iostream>
#include <cstring>
using namespace std;

class Vozac{
protected:
    char ime[100];
    int vozrast;
    int brTrki;
    bool veteran;
public:
    Vozac()
    {
        strcpy(this->ime,"");
        this->vozrast=0;
        this->brTrki=0;
        this->veteran=false;
    }
    Vozac(char *ime, int vozrast, int brTrki, bool veteran)
    {
        strcpy(this->ime,ime);
        this->vozrast=vozrast;
        this->brTrki=brTrki;
        this->veteran=veteran;
    }

    friend ostream &operator<<(ostream &os, Vozac &v)
    {
        os<<v.ime<<endl;
        os<<v.vozrast<<endl;
        os<<v.brTrki<<endl;
        if(v.veteran)
        {
            os<<"VETERAN"<<endl;
        }

        return os;
    }

    virtual float zarabotuvacka() = 0;
    virtual float danok() = 0;


    virtual bool operator==(Vozac &v)
    {
        return zarabotuvacka()==v.zarabotuvacka();
    }


};

class Avtomobilist: public Vozac{
private:
    float cenaAvtomobil;
public:
    Avtomobilist() : Vozac()
    {
        this->cenaAvtomobil=0;
    }
    Avtomobilist(char *ime, int vozrast, int brTrki, bool veteran, float cenaAvtomobil) : Vozac(ime, vozrast, brTrki, veteran)
    {
        this->cenaAvtomobil=cenaAvtomobil;
    }

    float zarabotuvacka()
    {
        return cenaAvtomobil/5;
    }

    bool operator==(Avtomobilist &v)
    {
        return zarabotuvacka()>v.zarabotuvacka();
    }

    float danok()
    {
        if(brTrki>10)
        {
            return zarabotuvacka()*0.15;
        }
        else
        {
            return zarabotuvacka()*0.10;
        }
    }
};

class Motociklist : public Vozac{
private:
    int moknostMotor;
public:
    Motociklist() : Vozac()
    {
        this->moknostMotor=0;
    }
    Motociklist(char *ime, int vozrast, int brTrki, bool veteran, int moknostMotor) : Vozac(ime, vozrast, brTrki, veteran)
    {
        this->moknostMotor=moknostMotor;
    }

    float zarabotuvacka()
    {
        return moknostMotor*20;
    }

    bool operator==(Avtomobilist &v)
    {
        return zarabotuvacka()>v.zarabotuvacka();
    }

    float danok()
    {
        if(veteran)
        {
            return zarabotuvacka()*0.25;
        }
        else
        {
            return zarabotuvacka()*0.20;
        }
    }
};

int soIstaZarabotuvachka(Vozac **v, int n, Vozac *vx)
{
    int brojac=0;
    for(int i=0; i<n; i++)
    {
        if(*v[i]==*vx)
        {
            brojac++;
        }
    }

    return brojac;
}

int main() {
	int n, x;
	cin >> n >> x;
	Vozac **v = new Vozac*[n];
	char ime[100];
	int vozrast;
	int trki;
	bool vet;
	for(int i = 0; i < n; ++i) {
		cin >> ime >> vozrast >> trki >> vet;
		if(i < x) {
			float cena_avto;
			cin >> cena_avto;
			v[i] = new Avtomobilist(ime, vozrast, trki, vet, cena_avto);
		} else {
			int mokjnost;
			cin >> mokjnost;
			v[i] = new Motociklist(ime, vozrast, trki, vet, mokjnost);
		}
	}
	cout << "=== DANOK ===" << endl;
	for(int i = 0; i < n; ++i) {
		cout << *v[i];
		cout << v[i]->danok() << endl;
	}
	cin >> ime >> vozrast >> trki >> vet;
	int mokjnost;
	cin >> mokjnost;
	Vozac *vx = new Motociklist(ime, vozrast, trki, vet, mokjnost);
	cout << "=== VOZAC X ===" << endl;
	cout << *vx;
	cout << "=== SO ISTA ZARABOTUVACKA KAKO VOZAC X ===" << endl;
	cout << soIstaZarabotuvachka(v, n, vx);
    for(int i = 0; i < n; ++i) {
        delete v[i];
    }
    delete [] v;
    delete vx;
	return 0;
}
