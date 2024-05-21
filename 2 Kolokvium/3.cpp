#include <iostream>
#include <fstream>
#include <cctype>
#include <iomanip>

using namespace std;

void writeToFile() {
    std::ofstream outFile("text.txt");
    char c;
    while((c = std::cin.get()) != '#') {
        outFile.put(c);
    }
    outFile.close();
}

int main() {
    writeToFile();
    ifstream inFile("text.txt");
    char c;
    int n=0;
    double mala=0, golema=0;

    while(inFile.get(c))
    {
        if(isupper(c)){golema++;}
        if(islower(c)){mala++;}
        if(isalnum(c)){n++;}
    }
    inFile.close();

    cout << fixed << setprecision(4);
    mala=mala/n;
    golema=golema/n;

    cout<<golema<<endl;
    cout<<mala<<endl;

    ofstream resultFile("text.txt");
    resultFile << fixed << setprecision(4);
    resultFile << golema << endl;
    resultFile << mala << endl;
    resultFile.close();
    return 0;
}
