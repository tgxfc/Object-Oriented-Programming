#include <iostream>
#include <cstring>
using namespace std;

class Flight{
protected:
    char code[40];
    char from[100];
    char to[100];
    double price;
    double baggagePrice;
public:
    Flight(char *code, char *from, char *to, double price, double baggagePrice)
    {
        strcpy(this->code, code);
        strcpy(this->from, from);
        strcpy(this->to, to);
        this->price=price;
        this->baggagePrice=baggagePrice;
    }

    double calculateTotalPrice()
    {
        return price+baggagePrice;
    }
    virtual void displayInfo()
    {
        cout<<code<<" "<<from<<"-"<<to<<" "<<calculateTotalPrice();
    }
};

class InvalidSeatNumberException{
private:
    string text;
public:
    InvalidSeatNumberException(string text)
    {
        this->text=text;
    }
    void print()
    {
        cout<<text;
    }
};

class EconomyFlight: public Flight{
private:
    char seat[4];
    static double LOYALTY_DISCOUNT;
public:
    EconomyFlight(Flight f, char *seat) : Flight(f) {
        strcpy(this->seat, seat);
    }
    double calculateTotalPrice()
    {
        double totalPrice=0;
        try
        {
            if(seat[0]=='C' || seat[0]=='F')
            {
                totalPrice=(price+baggagePrice)*(1-(LOYALTY_DISCOUNT/100))+(price*0.30);
            }
            else if(seat[0] < 'A' || seat[0] > 'F')
            {
                throw InvalidSeatNumberException("Invalid Seat Number Exception\n");
            }
            else
            {
                totalPrice=(price+baggagePrice)*(1-(LOYALTY_DISCOUNT/100));
            }

        }
        catch(InvalidSeatNumberException &ex)
        {
            ex.print();
        }
        return totalPrice;
    }

    void displayInfo()
    {
        cout<<code<<" "<<from<<"-"<<to<<" "<<seat<<endl;
        double totalPrice=calculateTotalPrice();
        if(totalPrice!=0)
        {
            cout<<"Total Price: $"<<calculateTotalPrice()<<endl;
        }
    }

    static void setLoyaltyDiscount(double loyalty)
    {
        LOYALTY_DISCOUNT=loyalty;
    }
};

double EconomyFlight::LOYALTY_DISCOUNT=20;

int main() {
    int testCase;
    cin>>testCase;
    char code[100];
    char from[100];
    char to[100];
    double price;
    double baggagePrice;
    char seatNumber[4];

    if(testCase == 1){
        cout << "===== Testiranje na klasite ======" << endl;
        int n;
        cin>>n;
        for(int i=0; i<n;i++){
            cin>>code>>from>>to>>price>>baggagePrice>>seatNumber;
            Flight f = Flight(code, from, to, price, baggagePrice);
            EconomyFlight ec = EconomyFlight(f, seatNumber);
            ec.displayInfo();
        }
    }
    if(testCase == 2){
        cout << "===== Testiranje na isklucoci ======" << endl;
        int n;
        cin>>n;
        for(int i=0; i<n;i++){
            cin>>code>>from>>to>>price>>baggagePrice>>seatNumber;
            Flight f = Flight(code, from, to, price, baggagePrice);
            EconomyFlight ec = EconomyFlight(f, seatNumber);
            ec.displayInfo();
        }
    }
    if(testCase == 3){
        cout << "===== Testiranje na static clenovi ======" << endl;
        cin>>code>>from>>to>>price>>baggagePrice>>seatNumber;
        Flight f = Flight(code, from, to, price, baggagePrice);
        EconomyFlight ec = EconomyFlight(f, seatNumber);
        ec.displayInfo();
        EconomyFlight::setLoyaltyDiscount(50);
        ec.displayInfo();
    }

    return 0;
}
