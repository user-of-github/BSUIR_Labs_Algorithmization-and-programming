#ifndef UNIVERSITY_H_INCLUDED
#define UNIVERSITY_H_INCLUDED

#include <iostream>
#include <vector>

using std :: cout;
using std :: string;
using std :: vector;

class University
{
private:
    string university_title_ = "";
    string university_address_ = "";

    class Faculty
    {
    public:
        string faculty_short_title_ = "";

        Faculty (const string &short_name);
        class Group
        {
        public:
            Faculty *parent_faculty_ = nullptr;
            string group_id_ = "";
            Group (const string &new_id, Faculty* parent_faculty);
            class Student
            {
            public:
                string first_name_ = "";
                string last_name_ = "";
                unsigned short birth_year_ = NULL;
                vector<unsigned short> marks_;
                Group *parent_group_ = nullptr;

                Student (const string &first_name,
                         const string &last_name,
                         const unsigned short &birth_year,
                         Group *parent_group);

                bool IsExcellent () const;
            };
            vector<Student*> students_list_;
            void GetParentFaculty () const;
        };
        vector<Group*> groups_list_;
        Group* FindGroup (const string &search_group) const
        {
            short temp = -1;
            for (unsigned short counter = 0; counter < this->groups_list_.size(); counter ++)
                if (this->groups_list_[counter]->group_id_ == search_group)
                {
                    temp = counter;
                    break;
                }

            return (temp == -1 ? nullptr : groups_list_[temp]);
        }
    };
    vector<Faculty*> faculties_list_;
    vector<Faculty :: Group*> groups_list_;
    vector<Faculty :: Group :: Student*> students_list_;
    Faculty* FindFaculty (const string &search_faculty) const
    {
        short temp = -1;
        for (unsigned short counter = 0; counter < this->faculties_list_.size(); counter ++)
            if (this->faculties_list_[counter]->faculty_short_title_ == search_faculty)
            {
                temp = counter;
                break;
            }

        return (temp == -1 ? nullptr : faculties_list_[temp]);
    }
public:
    University (const string &name, const string &adress);
    string Title () const;
    string Adress () const;
    void Info () const;
    void SetTitle (const string &_title);
    void SetAddress (const string &_address);
    void PrintFaculties () const;
    void AddFaculty (const string &short_name);

    void AddGroup (const string &which_faculty, const string &group_id);
    void PrintGroupIds () const;
    void LearnFacultyOfGroup (const string &search_group) const;

    void AddStudent (const string &last_name,
                     const string &first_name,
                     const unsigned short &birth_year,
                     const string &faculty,
                     const string &group_id);
    void DisplayHierarchy () const;
    void PrintGroupList () const;
    void AddMark (const string &group_name, const string &last_name, const unsigned short &mark);
    void PrintExcellentStudents (const string &group_id) const;
    void PrintAllStudents () const;
};

#endif // UNIVERSITY_H_INCLUDED
