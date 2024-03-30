#include <iostream>
#include <cstring>
using namespace std;

struct Student{
    char ime[20];
    int index;
    int br_kursevi;
    int kod[100];
};

struct Course {
    char ime[20];
    int kod;
    int br_studenti;
};

void BrojNaStudentiPoKurs(Course course[], Student student[], int br_kursevi, int br_studenti)
{
    for(int i=0; i<br_kursevi; i++)
    {
        for(int j=0; j<br_studenti; j++)
        {
            for(int k=0; k<student[j].br_kursevi; k++)
            {
                if(student[j].kod[k]==course[i].kod)
                {
                    course[i].br_studenti++;
                }
            }
        }
    }
}

int get_most_popular_course(Course course[], int num_courses)
{
    Course max=course[0];
    for(int i=0; i<num_courses; i++)
    {
        if(course[i].br_studenti>max.br_studenti)
        {
            max=course[i];
        }
    }

    return max.kod;
}

int main()
{
    Student student[100];
    Course course[100];
    int br_studenti, br_kursevi;
    cin>>br_studenti>>br_kursevi;
    for(int i=0; i<br_kursevi; i++)
    {
        cin>>course[i].ime;
        cin>>course[i].kod;
    }
    for(int i=0; i<br_studenti; i++)
    {
        cin>>student[i].ime;
        cin>>student[i].index;
        cin>>student[i].br_kursevi;
        for(int j=0; j<student[i].br_kursevi; j++)
        {
            cin>>student[i].kod[j];
        }
    }

    BrojNaStudentiPoKurs(course,student,br_kursevi,br_studenti);
    int najpopularen_kod = get_most_popular_course(course, br_kursevi);
    char najpopularen_ime[20];
    for(int i=0; i<br_kursevi; i++)
    {
        if(course[i].kod==najpopularen_kod)
        {
            strcpy(najpopularen_ime,course[i].ime);
        }
    }

    cout<<"Najpopularen kurs e: "<<najpopularen_ime;

    return 0;
}
