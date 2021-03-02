#include <fstream>
#include "university.h"

using std :: ifstream;
using std :: getline;

int main()
{
    ifstream cin1("faculties.txt");
    ifstream cin2("groups.txt");
    ifstream cin3("students.txt");
    ifstream cin4("marks.txt");
    cin1.tie(NULL);
    cin2.tie(NULL);
    cin3.tie(NULL);
    cin4.tie(NULL);

    setlocale(0, "");

    University BSUIR("BSUIR", "Minsk, Belarus");

    unsigned short k_faculties;
    cin1>>k_faculties;
    for (unsigned short counter = 0; counter < k_faculties; counter ++)
    {
        string name;
        cin1>>name;
        BSUIR.AddFaculty(name);
    }

    unsigned short k_groups;
    cin2>>k_groups;
    for (unsigned short counter = 0; counter < k_groups; counter ++)
    {
        string faculty, id;
        cin2>>faculty>>id;
        BSUIR.AddGroup(faculty, id);
    }

    unsigned short k_students;
    cin3>>k_students;
    for (unsigned short counter = 0; counter < k_students; counter ++)
    {
        string last_name, first_name, faculty, group;
        unsigned short year;
        cin3>>last_name>>first_name>>year>>faculty>>group;
        BSUIR.AddStudent(last_name, first_name, year, faculty, group);
    }

    unsigned short k_marks;
    cin4>>k_marks;
    for (unsigned short counter = 0; counter < k_marks; counter ++)
    {
        string id, last_name;
        unsigned short mark;

        cin4>>id>>last_name>>mark;
        BSUIR.AddMark(id, last_name, mark);
    }

    BSUIR.DisplayHierarchy();

    cout<<"\n";
    BSUIR.PrintExcellentStudents("053501");

    BSUIR.PrintAllStudents();
    return 0;
}



