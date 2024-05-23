#include <cstring>
#include <iostream>
using namespace std;

// Your Code goes here
class Pizza{
protected:
    char ime[20];
    char sostojki[100];
    float cena;
public:
    Pizza()
    {
        strcpy(this->ime,"");
        strcpy(this->sostojki,"");
        this->cena=0;
    }
    Pizza(char *ime, char *sostojki, float cena)
    {
        strcpy(this->ime,ime);
        strcpy(this->sostojki,sostojki);
        this->cena=cena;
    }

    virtual float price()=0;
    virtual bool operator<(Pizza &p)
    {
        return price()<p.price();
    }
};

enum Size{
    mala, golema, familijarna
};

class FlatPizza : public Pizza{
private:
    Size size;
public:
    FlatPizza() : Pizza(){
        this->size=mala;
    }
    FlatPizza(char *ime, char *sostojki, float cena, Size size) : Pizza(ime,sostojki,cena)
    {
        this->size=size;
    }
    FlatPizza(char *ime, char *sostojki, float cena) : Pizza(ime,sostojki,cena)
    {
        this->size=mala;
    }

    float price()
    {
        if(size==mala){return cena*1.10;}
        else if(size==golema){return cena*1.20;}
        else if(size==familijarna){return cena*1.30;}
    }

    friend ostream &operator<<(ostream &os, FlatPizza &p)
    {
        os<<p.ime<<": "<<p.sostojki<<", ";
        if(p.size==mala){os<<"small";}
        if(p.size==golema){os<<"big";}
        if(p.size==familijarna){os<<"family";}
        os<<" - "<<p.price()<<endl;
        return os;
    }
};

class FoldedPizza : public Pizza{
private:
    bool brasno;
public:
    FoldedPizza() : Pizza(){
        this->brasno=true;
    }
    FoldedPizza(char *ime, char *sostojki, float cena) : Pizza(ime,sostojki,cena)
    {
        this->brasno=true;
    }

    float price()
    {
        if(brasno){return cena*1.10;}
        else if(!brasno){return cena*1.30;}
    }

    friend ostream &operator<<(ostream &os, FoldedPizza &p)
    {
        os<<p.ime<<": "<<p.sostojki<<", "<<(p.brasno ? "wf" : "nwf")<<" - "<<p.price()<<endl;
        return os;
    }

    void setWhiteFlour(bool flour)
    {
        this->brasno=flour;
    }
};

void expensivePizza(Pizza **pi,int num_p)
{
    int ind=0;
    for(int i=0; i<num_p; i++)
    {
        if(*pi[ind]<*pi[i])
        {
            ind=i;
        }
    }

    if(dynamic_cast<FlatPizza*>(pi[ind])!=nullptr) 
    {
        cout<<static_cast<FlatPizza&>(*pi[ind]);
    } 
    else if(dynamic_cast<FoldedPizza*>(pi[ind])!=nullptr) 
    {
        cout<<static_cast<FoldedPizza&>(*pi[ind]);
    }
}


// Testing

int main() {
    int test_case;
    char name[20];
    char ingredients[100];
    float inPrice;
    Size size;
    bool whiteFlour;

    cin >> test_case;
    if (test_case == 1) {
        // Test Case FlatPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FlatPizza fp(name, ingredients, inPrice);
        cout << fp;
    } else if (test_case == 2) {
        // Test Case FlatPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        int s;
        cin>>s;
        FlatPizza fp(name, ingredients, inPrice, (Size)s);
        cout << fp;

    } else if (test_case == 3) {
        // Test Case FoldedPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FoldedPizza fp(name, ingredients, inPrice);
        cout << fp;
    } else if (test_case == 4) {
        // Test Case FoldedPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FoldedPizza fp(name, ingredients, inPrice);
        fp.setWhiteFlour(false);
        cout << fp;

    } else if (test_case == 5) {
        // Test Cast - operator <, price
        int s;

        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        cin>>s;
        FlatPizza *fp1 = new FlatPizza(name, ingredients, inPrice, (Size)s);
        cout << *fp1;

        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        cin>>s;
        FlatPizza *fp2 = new FlatPizza(name, ingredients, inPrice, (Size)s);
        cout << *fp2;

        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FoldedPizza *fp3 = new FoldedPizza(name, ingredients, inPrice);
        cout << *fp3;

        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FoldedPizza *fp4 = new FoldedPizza(name, ingredients, inPrice);
        fp4->setWhiteFlour(false);
        cout << *fp4;

        cout<<"Lower price: "<<endl;
        if(*fp1<*fp2)
            cout<<fp1->price()<<endl;
        else cout<<fp2->price()<<endl;

        if(*fp1<*fp3)
            cout<<fp1->price()<<endl;
        else cout<<fp3->price()<<endl;

        if(*fp4<*fp2)
            cout<<fp4->price()<<endl;
        else cout<<fp2->price()<<endl;

        if(*fp3<*fp4)
            cout<<fp3->price()<<endl;
        else cout<<fp4->price()<<endl;

    } else if (test_case == 6) {
        // Test Cast - expensivePizza
        int num_p;
        int pizza_type;

        cin >> num_p;
        Pizza **pi = new Pizza *[num_p];
        for (int j = 0; j < num_p; ++j) {

            cin >> pizza_type;
            if (pizza_type == 1) {
                cin.get();
                cin.getline(name,20);

                cin.getline(ingredients,100);
                cin >> inPrice;
                int s;
                cin>>s;
                FlatPizza *fp = new FlatPizza(name, ingredients, inPrice, (Size)s);
                cout << (*fp);
                pi[j] = fp;
            }
            if (pizza_type == 2) {

                cin.get();
                cin.getline(name,20);
                cin.getline(ingredients,100);
                cin >> inPrice;
                FoldedPizza *fp =
                        new FoldedPizza (name, ingredients, inPrice);
                if(j%2)
                    (*fp).setWhiteFlour(false);
                cout << (*fp);
                pi[j] = fp;

            }
        }

        cout << endl;
        cout << "The most expensive pizza:\n";
        expensivePizza(pi,num_p);


    }
    return 0;
}
