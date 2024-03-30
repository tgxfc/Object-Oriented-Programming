#include <iostream>
#include <cstring>
using namespace std;

struct Proizvod{
    char kod[20];
    int cena;
    int dostapni;
};

struct Narachka{
    char ime[15];
    Proizvod proizvod[10];
    int brProizvodi[10];
    int n;
};

void pecatiFaktura(Narachka n)
{
    cout<<"Faktura za "<<n.ime<<endl;
    for(int i=0; i<n.n; i++)
    {
        if(n.brProizvodi[i]>n.proizvod[i].dostapni)
        {
            cout<<"Fakturata ne moze da se izgotvi";
            return;
        }
    }

    for(int i=0; i<n.n; i++)
    {
        for(int j=0; j<n.n-i-1; j++)
        {
            if(n.proizvod[j].kod[0]>n.proizvod[j+1].kod[0])
            {
                Proizvod temp=n.proizvod[j];
                n.proizvod[j]=n.proizvod[j + 1];
                n.proizvod[j+1]=temp;
            }

            if(n.proizvod[j].kod[0] == n.proizvod[j+1].kod[0] &&
               n.proizvod[j].kod[1] > n.proizvod[j+1].kod[1])
            {
                Proizvod temp=n.proizvod[j];
                n.proizvod[j]=n.proizvod[j + 1];
                n.proizvod[j+1]=temp;
            }
        }
    }
    int suma=0;
    for(int i=0; i<n.n; i++)
    {
        suma+=(n.brProizvodi[i]*n.proizvod[i].cena);
        n.proizvod[i].dostapni-=n.brProizvodi[i];
    }

    for(int i=0; i<n.n; i++)
    {
        cout<<n.proizvod[i].kod<<" "<<n.proizvod[i].cena<<" "<<n.brProizvodi[i]<<" "<<n.brProizvodi[i]*n.proizvod[i].cena<<endl;
    }
    cout<<"Vkupnata suma na fakturata e "<<suma;
}
//место за вашиот код

int main() {

    Narachka narachka;

    cin>>narachka.ime;
    cin>>narachka.n;

    int i;
    //за секој од нарачаните производи се внесуваат информации
    for (i = 0; i < narachka.n; ++i) {
        cin>>narachka.proizvod[i].kod;
        cin>>narachka.proizvod[i].cena;
        cin>>narachka.proizvod[i].dostapni;
    }
    //за секој производ се внесува колку такви производи се порачани во нарачката
    int j;
    for (j = 0; j < narachka.n; ++j) {
        cin>>narachka.brProizvodi[j];
    }

    pecatiFaktura(narachka);

    return 0;
}
