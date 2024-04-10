#include<iostream>
#include<cstring>
using namespace std;

class List{
private:
    int *broj;
    int n;
public:
    List()
    {
        this->broj=nullptr;
        this->n=0;
    }
    List(int *broj, int n)
    {
        this->n=n;
        this->broj=new int[n];
        for(int i=0; i<n; i++)
        {
            this->broj[i]=broj[i];
        }
    }
    List(const List &cc)
    {
        this->n=cc.n;
        this->broj=new int[cc.n];
        for(int i=0; i<cc.n; i++)
        {
            this->broj[i]=cc.broj[i];
        }
    }
    List &operator=(const List &cc)
    {
        if(this==&cc)
        {
            return *this;
        }
        this->n=cc.n;
        this->broj=new int[cc.n];
        for(int i=0; i<cc.n; i++)
        {
            this->broj[i]=cc.broj[i];
        }
        return *this;
    }

    int sum()
    {
        int sum=0;
        for(int i=0; i<n; i++)
        {
            sum+=broj[i];
        }
        return sum;
    }
    double average(){return (double)sum()/n;}

    void pecati()
    {
        cout<<n<<": ";
        for(int i=0; i<n; i++)
        {
            cout<<broj[i]<<" ";
        }
        cout<<"sum: "<<sum();
        cout<<" average: "<<average()<<endl;
    }

    int getN(){return n;}

    ~List()
    {
        delete [] broj;
    }
};

class ListContainer{
private:
    List *list;
    int n;
    int obidi;
public:
    ListContainer()
    {
        this->list=nullptr;
        this->n=0;
        this->obidi=0;
    }
    ListContainer(const ListContainer &cc)
    {
        this->list=new List[cc.n];
        for(int i=0; i<cc.n; i++)
        {
            this->list[i]=cc.list[i];
        }
        this->n=cc.n;
        this->obidi=cc.obidi;
    }
    ListContainer operator=(ListContainer &cc)
    {
        if(this==&cc)
        {
            return *this;
        }
        this->list=new List[cc.n];
        for(int i=0; i<cc.n; i++)
        {
            this->list[i]=cc.list[i];
        }
        this->n=cc.n;
        this->obidi=cc.obidi;
        return *this;
    }

    void print()
    {
        if(n==0)
        {
            cout<<"The list is empty"<<endl;
            return;
        }
        for(int i=0; i<n; i++)
        {
            cout<<"List number: "<<i+1<<" List info: ";
            list[i].pecati();
        }
        cout<<"Sum: "<<sum()<<" Average: "<<average()<<endl;
        cout<<"Successful attempts: "<<n<<" Failed attempts: "<<obidi<<endl;
    }
    void addNewList(List l)
    {
        for(int i=0; i<n; i++)
        {
            if(list[i].sum()==l.sum())
            {
                obidi++;
                return;
            }
        }
        List *temp=new List[n+1];
        for(int i=0; i<n; i++)
        {
            temp[i]=list[i];
        }
        temp[n++]=l;
        delete [] list;
        list=new List[n];
        for(int i=0; i<n; i++)
        {
            list[i]=temp[i];
        }
    }

    int sum()
    {
        int sum=0;
        for(int i=0; i<n; i++)
        {
            sum+=list[i].sum();
        }
        return sum;
    }
    double average()
    {
        int totalN=0;
        for(int i=0; i<n; i++)
        {
            totalN+=list[i].getN();
        }
        return (double)sum()/totalN;
    }

    ~ListContainer()
    {
        delete [] list;
    }
};

int main() {

    ListContainer lc;
    int N;
    cin>>N;

    for (int i=0;i<N;i++) {
        int n;
        int niza[100];

        cin>>n;

        for (int j=0;j<n;j++){
            cin>>niza[j];

        }

        List l=List(niza,n);

        lc.addNewList(l);
    }


    int testCase;
    cin>>testCase;

    if (testCase==1) {
        cout<<"Test case for operator ="<<endl;
        ListContainer lc1;
        lc1.print();
        cout<<lc1.sum()<<" "<<lc.sum()<<endl;
        lc1=lc;
        lc1.print();
        cout<<lc1.sum()<<" "<<lc.sum()<<endl;
        lc1.sum();
        lc1.average();

    }
    else {
        lc.print();
    }
}
