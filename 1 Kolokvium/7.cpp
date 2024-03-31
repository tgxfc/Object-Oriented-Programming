#include<iostream>
#include<cstring>
using namespace std;

class Patnik{
private:
    char ime[100];
    int klasa;
    bool velosiped;
public:
    Patnik()
    {
        strcpy(this->ime,"");
        this->klasa=0;
        this->velosiped=false;
    }
    Patnik(char *ime, int klasa, bool velosiped)
    {
        strcpy(this->ime,ime);
        this->klasa=klasa;
        this->velosiped=velosiped;
    }
    Patnik(const Patnik &cc)
    {
        strcpy(this->ime,cc.ime);
        this->klasa=cc.klasa;
        this->velosiped=cc.velosiped;
    }

    Patnik &operator=(const Patnik &o)
    {
        if(this == &o)
        {
            return *this;
        }
        strcpy(this->ime,o.ime);
        this->klasa=o.klasa;
        this->velosiped=o.velosiped;
        return *this;
    }

    friend ostream &operator<<(ostream &o, Patnik &u)
    {
        o<<u.ime<<endl;
        o<<u.klasa<<endl;
        o<<u.velosiped<<endl;
        o<<endl;
        return o;
    }

    bool getVelosiped(){return velosiped;}
    int getKlasa(){return klasa;}

    ~Patnik() {}
};

class Voz{
private:
    char destinacija[100];
    Patnik *patnik;
    int nPatnik;
    int nVelosiped;
public:
    Voz()
    {
        strcpy(destinacija,"");
        this->patnik=nullptr;
        this->nPatnik=0;
        this->nVelosiped=0;
    }
    Voz(char *destinacija, int nVelosiped)
    {
        strcpy(this->destinacija, destinacija);
        this->patnik= nullptr;
        this->nPatnik=0;
        this->nVelosiped=nVelosiped;
    }
    Voz(const Voz &cc)
    {
        strcpy(this->destinacija,cc.destinacija);
        this->patnik=new Patnik[cc.nPatnik];
        for(int i=0; i<cc.nPatnik; i++)
        {
            this->patnik[i]=cc.patnik[i];
        }
        this->nPatnik=cc.nPatnik;
        this->nVelosiped=cc.nVelosiped;
    }
    Voz &operator=(const Voz &o)
    {
        if(this == &o)
        {
            return *this;
        }
        delete [] this->patnik;
        strcpy(this->destinacija,o.destinacija);
        this->patnik=new Patnik[o.nPatnik];
        for(int i=0; i<o.nPatnik; i++)
        {
            this->patnik[i]=o.patnik[i];
        }
        this->nPatnik=o.nPatnik;
        this->nVelosiped=o.nVelosiped;
        return *this;
    }

    Voz operator+=(Patnik p)
    {
        Patnik *temp=new Patnik[nPatnik+1];
        for(int i=0; i<nPatnik; i++)
        {
            temp[i]=patnik[i];
        }
        temp[nPatnik++]=p;
        delete [] patnik;
        patnik=new Patnik[nPatnik];
        for(int i=0; i<nPatnik; i++)
        {
            patnik[i]=temp[i];
        }
        return *this;
    }

    friend ostream &operator<<(ostream &o, Voz &v)
    {
        o<<v.destinacija<<endl;
        if(v.nVelosiped==0)
        {
            for(int i=0; i<v.nPatnik; i++)
            {
                if(!v.patnik[i].getVelosiped())
                {
                    o<<v.patnik[i];
                }
            }
            return o;
        }

        for(int i=0; i<v.nPatnik; i++)
        {
            o<<v.patnik[i];
        }
        return o;
    }

    void patniciNemaMesto()
    {
        int klasa1=0, klasa2=0, v=nVelosiped;
        
        if (nVelosiped == 0) 
        {
            cout << "Brojot na patnici od 1-va klasa koi ostanale bez mesto e: 0" << endl;
            cout << "Brojot na patnici od 2-ra klasa koi ostanale bez mesto e: 0" << endl;
            return;
        }
        
        for(int i=0; i<nPatnik; i++)
        {
            if(patnik[i].getKlasa()==1)
            {
                if (v > 0)
                {
                    v--;
                }
                else
                {
                    klasa1++;
                }
            }
        }
        for(int i=0; i<nPatnik; i++)
        {
            if(patnik[i].getKlasa()==2)
            {
                if (v > 0)
                {
                    v--;
                }
                else
                {
                    klasa2++;
                }
            }
        }

        cout<<"Brojot na patnici od 1-va klasa koi ostanale bez mesto e: "<<klasa1<<endl;
        cout<<"Brojot na patnici od 2-ra klasa koi ostanale bez mesto e: "<<klasa2<<endl;
    }

    ~Voz()
    {
        delete [] patnik;
    }
};


int main()
{
    Patnik p;
    char ime[100], destinacija[100];
    int n;
    bool velosiped;
    int klasa;
    int maxv;
    cin >> destinacija >> maxv;
    cin >> n;
    Voz v(destinacija, maxv);
    //cout<<v<<endl;
    for (int i = 0; i < n; i++){
        cin >> ime >> klasa >> velosiped;
        Patnik p(ime, klasa, velosiped);
        //cout<<p<<endl;
        v += p;
    }
    cout << v;
    v.patniciNemaMesto();

    return 0;
}
