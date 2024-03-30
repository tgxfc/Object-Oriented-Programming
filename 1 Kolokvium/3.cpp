#include <iostream>
#include <cstring>
using namespace std;

struct FootballPlayer{
    char ime[20];
    int dres;
    int golovi;
};

struct FootballTeam{
    char ime[20];
    FootballPlayer player[11];
    int golovi;
};

void bestTeam(FootballTeam * team, int n)
{
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<11; j++)
        {
            team[i].golovi+=team[i].player[j].golovi;
        }
    }

    FootballTeam max=team[0];
    for(int i=0; i<n; i++)
    {
        if(team[i].golovi>max.golovi)
        {
            max=team[i];
        }
    }

    cout<<"Najdobar tim e: "<<max.ime;
}

int main()
{
    FootballTeam team[100];
    int n;

    cin>>n;
    for(int i=0; i<n; i++)
    {
        cin>>team[i].ime;
        for(int j=0; j<11; j++)
        {
            cin>>team[i].player[j].ime;
            cin>>team[i].player[j].dres;
            cin>>team[i].player[j].golovi;
        }
    }

    bestTeam(team,n);

    return 0;
}
