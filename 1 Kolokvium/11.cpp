#include<iostream>
#include<cstring>
using namespace std;

enum Extension{
    pdf, txt, exe
};
ostream &operator<<(std::ostream& os, Extension ext) {
    switch (ext) {
        case txt:
            os << "txt";
            break;
        case pdf:
            os << "pdf";
            break;
        case exe:
            os << "exe";
            break;
    }
    return os;
}

class File{
private:
    char *imeDatoteka;
    Extension ext;
    char *imeSopstvenik;
    int golemina;
public:
    File()
    {
        this->imeDatoteka=nullptr;
        this->ext=txt;
        this->imeSopstvenik=nullptr;
        this->golemina=0;
    }
    File(char *imeDatoteka, char *imeSopstvenik, int golemina, Extension ext)
    {
        this->imeDatoteka=new char[strlen(imeDatoteka)+1];
        strcpy(this->imeDatoteka, imeDatoteka);
        this->imeSopstvenik=new char[strlen(imeSopstvenik)+1];
        strcpy(this->imeSopstvenik,imeSopstvenik);
        this->golemina=golemina;
        this->ext=ext;
    }
    File(const File &cc)
    {
        this->imeDatoteka=new char[strlen(cc.imeDatoteka)+1];
        strcpy(this->imeDatoteka, cc.imeDatoteka);
        this->imeSopstvenik=new char[strlen(cc.imeSopstvenik)+1];
        strcpy(this->imeSopstvenik,cc.imeSopstvenik);
        this->golemina=cc.golemina;
        this->ext=cc.ext;
    }
    File &operator=(const File &cc)
    {
        if(this==&cc)
        {
            return *this;
        }
        this->imeDatoteka=new char[strlen(cc.imeDatoteka)+1];
        strcpy(this->imeDatoteka, cc.imeDatoteka);
        this->imeSopstvenik=new char[strlen(cc.imeSopstvenik)+1];
        strcpy(this->imeSopstvenik,cc.imeSopstvenik);
        this->golemina=cc.golemina;
        this->ext=cc.ext;
        return *this;
    }

    void print()
    {
        cout<<"File name: "<<imeDatoteka<<"."<<(Extension)ext<<endl;
        cout<<"File owner: "<<imeSopstvenik<<endl;
        cout<<"File size: "<<golemina<<endl;
    }
    bool equals(const File &that)
    {
        if(strcmp(this->imeSopstvenik,that.imeSopstvenik)==0 && strcmp(this->imeDatoteka,that.imeDatoteka)==0 && this->ext==that.ext)
        {
            return true;
        }
        return false;
    }

    bool equalsType(const File &that)
    {
        if(strcmp(this->imeSopstvenik,that.imeSopstvenik)==0 && this->ext==that.ext)
        {
            return true;
        }
        return false;
    }

    ~File()
    {
        delete [] imeDatoteka;
        delete [] imeSopstvenik;
    }
};

class Folder{
private:
    char *imeDirektorium;
    int n;
    File *file;
public:
    Folder()
    {
        this->imeDirektorium=nullptr;
        this->n=0;
        this->file= nullptr;
    }
    Folder(const char *imeDirektorium)
    {
        this->imeDirektorium=new char[strlen(imeDirektorium)+1];
        strcpy(this->imeDirektorium,imeDirektorium);
        this->n=0;
        this->file= nullptr;
    }
    Folder(Folder &cc)
    {
        delete [] imeDirektorium;
        delete [] file;
        this->imeDirektorium=new char[strlen(cc.imeDirektorium)+1];
        strcpy(this->imeDirektorium,cc.imeDirektorium);
        this->n=cc.n;
        this->file=new File[n];
        for(int i=0; i<n; i++)
        {
            this->file[i]=cc.file[i];
        }
    }
    Folder &operator=(Folder &cc)
    {
        delete [] imeDirektorium;
        delete [] file;
        this->imeDirektorium=new char[strlen(cc.imeDirektorium)+1];
        strcpy(this->imeDirektorium,cc.imeDirektorium);
        this->n=cc.n;
        this->file=new File[n];
        for(int i=0; i<n; i++)
        {
            this->file[i]=cc.file[i];
        }
    }

    void print()
    {
        cout<<"Folder name: "<<imeDirektorium<<endl;
        for(int i=0; i<n; i++)
        {
            file[i].print();
        }
    }
    void remove(const File &f)
    {
        int index=0;
        for(int i=0; i<n; i++)
        {
            if(file[i].equals(f))
            {
                index=i;
                break;
            }
        }
        for(int i=index; i<n-1; i++)
        {
            file[i]=file[i+1];
        }
        n--;
    }

    void add(const File &f)
    {
        File *temp=new File[n+1];
        for(int i=0; i<n; i++)
        {
            temp[i]=file[i];
        }
        temp[n++]=f;
        delete [] file;
        file=new File[n];
        for(int i=0; i<n; i++)
        {
            file[i]=temp[i];
        }
    }

    ~Folder()
    {
        delete [] imeDirektorium;
        delete [] file;
    }
};

int main() {
    char fileName[20];
    char fileOwner[20];
    int ext;
    int fileSize;

    int testCase;
    cin >> testCase;
    if (testCase == 1) {
        cout << "======= FILE CONSTRUCTORS AND = OPERATOR =======" << endl;
        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File created = File(fileName, fileOwner, fileSize, (Extension) ext);
        File copied = File(created);
        File assigned = created;

        cout << "======= CREATED =======" << endl;
        created.print();
        cout << endl;
        cout << "======= COPIED =======" << endl;
        copied.print();
        cout << endl;
        cout << "======= ASSIGNED =======" << endl;
        assigned.print();
    }
    else if (testCase == 2) {
        cout << "======= FILE EQUALS & EQUALS TYPE =======" << endl;
        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File first(fileName, fileOwner, fileSize, (Extension) ext);
        first.print();

        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File second(fileName, fileOwner, fileSize, (Extension) ext);
        second.print();

        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File third(fileName, fileOwner, fileSize, (Extension) ext);
        third.print();

        bool equals = first.equals(second);
        cout << "FIRST EQUALS SECOND: ";
        if (equals)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

        equals = first.equals(third);
        cout << "FIRST EQUALS THIRD: ";
        if (equals)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

        bool equalsType = first.equalsType(second);
        cout << "FIRST EQUALS TYPE SECOND: ";
        if (equalsType)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

        equalsType = second.equals(third);
        cout << "SECOND EQUALS TYPE THIRD: ";
        if (equalsType)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

    }
    else if (testCase == 3) {
        cout << "======= FOLDER CONSTRUCTOR =======" << endl;
        cin >> fileName;
        Folder folder(fileName);
        folder.print();

    }
    else if (testCase == 4) {
        cout << "======= ADD FILE IN FOLDER =======" << endl;
        char name[20];
        cin >> name;
        Folder folder(name);

        int iter;
        cin >> iter;

        while (iter > 0) {
            cin >> fileName;
            cin >> fileOwner;
            cin >> fileSize;
            cin >> ext;

            File file(fileName, fileOwner, fileSize, (Extension) ext);
            folder.add(file);
            iter--;
        }
        folder.print();
    }
    else {
        cout << "======= REMOVE FILE FROM FOLDER =======" << endl;
        char name[20];
        cin >> name;
        Folder folder(name);

        int iter;
        cin >> iter;

        while (iter > 0) {
            cin >> fileName;
            cin >> fileOwner;
            cin >> fileSize;
            cin >> ext;

            File file(fileName, fileOwner, fileSize, (Extension) ext);
            folder.add(file);
            iter--;
        }
        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File file(fileName, fileOwner, fileSize, (Extension) ext);
        folder.remove(file);
        folder.print();
    }
    return 0;
}
