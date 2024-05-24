#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

class Koncert{
protected:
    char naziv[20];
    char lokacija[20];
    static float sezonskiPopust;
    float cenaBilet;
public:
    Koncert()
    {
        strcpy(this->naziv,"");
        strcpy(this->lokacija,"");
        this->cenaBilet=0;
    }
    Koncert(char *naziv, char *lokacija, float cenaBilet)
    {
        strcpy(this->naziv,naziv);
        strcpy(this->lokacija,lokacija);
        this->cenaBilet=cenaBilet;
    }

    void setSezonskiPopust(float novPopust)
    {
        sezonskiPopust=novPopust;
    }
    char* getNaziv()
    {
        return naziv;
    }
    float getSezonskiPopust()
    {
        return sezonskiPopust;
    }

    virtual float cena()
    {
        return cenaBilet-(cenaBilet*sezonskiPopust);
    }
};

float Koncert::sezonskiPopust=0.2;

class ElektronskiKoncert : public Koncert{
private:
    vector<char> imeDJ;
    int casovi;
    bool dnevna;
public:
    ElektronskiKoncert() : Koncert()
    {
        this->imeDJ.resize(0);
        this->casovi=0;
        this->dnevna=false;
    }
    ElektronskiKoncert(char *naziv,char *lokacija, float cenaBilet,char *imeDJ,int casovi,bool dnevna)
            : Koncert(naziv, lokacija, cenaBilet)
    {
        this->imeDJ.assign(imeDJ, imeDJ+strlen(imeDJ));
        this->casovi=casovi;
        this->dnevna=dnevna;
    }

    float cena() override
    {
        float konecnaCena=cenaBilet;
        if(casovi>7)
        {konecnaCena+=360;}
        else if(casovi>5)
        {konecnaCena+=150;}

        if(dnevna)
        {konecnaCena-=50;}
        else
        {konecnaCena+=100;}

        konecnaCena-=(cenaBilet*sezonskiPopust);
        return konecnaCena;
    }
};

void najskapKoncert(Koncert ** koncerti, int n)
{
    int ind=0, counter=0;
    for(int i=0; i<n; i++)
    {
        if(koncerti[i]->cena()>koncerti[ind]->cena())
        {
            ind=i;
        }
        if(dynamic_cast<ElektronskiKoncert*>(koncerti[i])!=nullptr)
        {
            counter++;
        }
    }

    cout<<"Najskap koncert: "<<koncerti[ind]->getNaziv()<<" "<<koncerti[ind]->cena()<<endl;
    cout<<"Elektronski koncerti: "<<counter<<" od vkupno "<<n<<endl;
}

bool prebarajKoncert(Koncert ** koncerti, int n, char * naziv, bool elektronski)
{
    bool najden=false;
    int ind=0;
    if(elektronski)
    {
        for(int i=0; i<n; i++)
        {
            if(dynamic_cast<ElektronskiKoncert*>(koncerti[i])!= nullptr)
            {
                if(strcmp(koncerti[i]->getNaziv(),naziv)==0)
                {
                    najden=true;
                    ind=i;
                }
            }
        }
    }
    else
    {
        for(int i=0; i<n; i++)
        {
            if(strcmp(koncerti[i]->getNaziv(),naziv)==0)
            {
                najden=true;
                ind=i;
            }
        }
    }
    if(najden)
    {
        cout<<koncerti[ind]->getNaziv()<<" "<<koncerti[ind]->cena()<<endl;
        return najden;
    }
    return false;
}


int main(){

    int tip,n,novaCena;
    char naziv[100], lokacija[100], imeDJ[40];
    bool dnevna;
    float cenaBilet, novPopust;
    float casovi;

    cin>>tip;
    if (tip==1){//Koncert
        cin>>naziv>>lokacija>>cenaBilet;
        Koncert k1(naziv,lokacija,cenaBilet);
        cout<<"Kreiran e koncert so naziv: "<<k1.getNaziv()<<endl;
    }
    else if (tip==2){//cena - Koncert
        cin>>naziv>>lokacija>>cenaBilet;
        Koncert k1(naziv,lokacija,cenaBilet);
        cout<<"Osnovna cena na koncertot so naziv "<<k1.getNaziv()<< " e: " <<k1.cena()<<endl;
    }
    else if (tip==3){//ElektronskiKoncert
        cin>>naziv>>lokacija>>cenaBilet>>imeDJ>>casovi>>dnevna;
        ElektronskiKoncert s(naziv,lokacija,cenaBilet,imeDJ,casovi,dnevna);
        cout<<"Kreiran e elektronski koncert so naziv "<<s.getNaziv()<<" i sezonskiPopust "<<s.getSezonskiPopust()<<endl;
    }
    else if (tip==4){//cena - ElektronskiKoncert
        cin>>naziv>>lokacija>>cenaBilet>>imeDJ>>casovi>>dnevna;
        ElektronskiKoncert s(naziv,lokacija,cenaBilet,imeDJ,casovi,dnevna);
        cout<<"Cenata na elektronskiot koncert so naziv "<<s.getNaziv()<<" e: "<<s.cena()<<endl;
    }
    else if (tip==5) {//najskapKoncert

    }
    else if (tip==6) {//prebarajKoncert
        Koncert ** koncerti = new Koncert *[5];
        int n;
        koncerti[0] = new Koncert("Area","BorisTrajkovski",350);
        koncerti[1] = new ElektronskiKoncert("TomorrowLand","Belgium",8000,"Afrojack",7.5,false);
        koncerti[2] = new ElektronskiKoncert("SeaDance","Budva",9100,"Tiesto",5,true);
        koncerti[3] = new Koncert("Superhiks","PlatoUkim",100);
        koncerti[4] = new ElektronskiKoncert("CavoParadiso","Mykonos",8800,"Guetta",3,true);
        char naziv[100];
        najskapKoncert(koncerti,5);
    }
    else if (tip==7){//prebaraj
        Koncert ** koncerti = new Koncert *[5];
        int n;
        koncerti[0] = new Koncert("Area","BorisTrajkovski",350);
        koncerti[1] = new ElektronskiKoncert("TomorrowLand","Belgium",8000,"Afrojack",7.5,false);
        koncerti[2] = new ElektronskiKoncert("SeaDance","Budva",9100,"Tiesto",5,true);
        koncerti[3] = new Koncert("Superhiks","PlatoUkim",100);
        koncerti[4] = new ElektronskiKoncert("CavoParadiso","Mykonos",8800,"Guetta",3,true);
        char naziv[100];
        bool elektronski;
        cin>>elektronski;
        if(prebarajKoncert(koncerti,5, "Area",elektronski))
            cout<<"Pronajden"<<endl;
        else cout<<"Ne e pronajden"<<endl;

        if(prebarajKoncert(koncerti,5, "Area",!elektronski))
            cout<<"Pronajden"<<endl;
        else cout<<"Ne e pronajden"<<endl;

    }
    else if (tip==8){//smeni cena
        Koncert ** koncerti = new Koncert *[5];
        int n;
        koncerti[0] = new Koncert("Area","BorisTrajkovski",350);
        koncerti[1] = new ElektronskiKoncert("TomorrowLand","Belgium",8000,"Afrojack",7.5,false);
        koncerti[2] = new ElektronskiKoncert("SeaDance","Budva",9100,"Tiesto",5,true);
        koncerti[3] = new Koncert("Superhiks","PlatoUkim",100);
        koncerti[2] -> setSezonskiPopust(0.9);
        najskapKoncert(koncerti,4);
    }

    return 0;
}
