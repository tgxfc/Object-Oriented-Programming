#include <iostream>
#include <cstring>
using namespace std;

struct Transaction{
    int id;
    int suma;
    int provizija;
    bool karticka;
};

int main()
{
    Transaction transaction[100];
    int n;

    cin>>n;
    for(int i=0; i<n; i++)
    {
        cin>>transaction[i].id;
        cin>>transaction[i].suma;
        cin>>transaction[i].provizija;
        cin>>transaction[i].karticka;
    }

    bool kreditna=true;
    for(int i=0; i<n; i++)
    {
        if(transaction[i].karticka)
        {
            cout<<transaction[i].id<<" "<<transaction[i].suma+transaction[i].provizija<<endl;
        }
        else
        {
            kreditna=false;
        }
    }

    if(!kreditna)
    {
        cout<<"No credit card transaction.";
    }

    return 0;
}
