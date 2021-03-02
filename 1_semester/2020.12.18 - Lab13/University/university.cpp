#include "university.h"

University :: University (const string &name, const string &adress)
{
    this->university_title_ = name;
    this->university_address_ = adress;
}

string University :: Title () const
{
    return this->university_title_;
}

string University :: Adress () const
{
    return this->university_address_;
}

void University :: Info () const
{
    cout<<"University: "<<this->Title()<<"\n";
    cout<<"Location: "<<this->Adress()<<"\n";
    this->PrintFaculties();

    return;
}

void University :: SetTitle (const string &_title)
{
    this->university_title_ = _title;
    return;
}

void University :: SetAddress (const string &_address)
{
    this->university_address_ = _address;
    return;
}

void University :: PrintFaculties () const
{
    cout<<"Faculties ("<<this->faculties_list_.size()<<"): \n[ \n";
    for (unsigned short counter = 0; counter < this->faculties_list_.size(); counter ++)
        cout<<"\t"<<this->faculties_list_[counter]->faculty_short_title_<<" - "<<
            (counter != this->faculties_list_.size() - 1 ? "\n" : "");

    cout<<"\n]\n\n";
    return;
}

void University :: AddFaculty (const string &short_name)
{
    Faculty *new_faculty = new Faculty(short_name);
    this->faculties_list_.push_back(new_faculty);

    return;
}

University :: Faculty :: Faculty (const string &short_name)
{
    this->faculty_short_title_ = short_name;
}

void University :: AddGroup (const string &which_faculty, const string &group_id)
{
    Faculty *found = this->FindFaculty(which_faculty);

    if (found != nullptr)
    {
        // cout<<"Факультет найден "<<which_faculty<<"\n"

        Faculty :: Group *new_group = new Faculty :: Group (group_id, found);
        found->groups_list_.push_back(new_group);
        this->groups_list_.push_back(new_group);
    }
    else
    {
        cout<<"Error. Group wasn't added. Faculty '"<<which_faculty<<"' wasn't found\n";
    }

    return;
}

void University :: PrintGroupIds () const
{
    for (unsigned short counter = 0; counter < this->faculties_list_.size(); counter ++)
    {
        cout<<this->faculties_list_[counter]->faculty_short_title_<<": ("<<this->faculties_list_[counter]->groups_list_.size()<<"): [ ";
        for (unsigned short counter2 = 0; counter2 < this->faculties_list_[counter]->groups_list_.size(); counter2 ++)
            cout<<"№ "<<this->faculties_list_[counter]->groups_list_[counter2]->group_id_<<((counter2 != (this->faculties_list_[counter]->groups_list_.size() - 1)) ? ", " : "");

        cout<<" ]\n";

    }

    return;
}


University :: Faculty :: Group :: Group (const string &new_id, Faculty *parent_faculty)
{
    this->group_id_ = new_id;
    this->parent_faculty_ = parent_faculty;
}

void University :: Faculty :: Group :: GetParentFaculty () const
{
    cout<<this->parent_faculty_->faculty_short_title_;

    return;
}

University :: Faculty :: Group :: Student :: Student (const string &first_name,
        const string &last_name,
        const unsigned short &birth_year,
        Group *parent_group)
{
    this->first_name_ = first_name;
    this->last_name_ = last_name;
    this->birth_year_ = birth_year;
    this->parent_group_ = parent_group;
}

void University :: AddStudent (const string &last_name,
                               const string &first_name,
                               const unsigned short &birth_year,
                               const string &faculty,
                               const string &group_id)
{
    Faculty *foundF = this->FindFaculty(faculty);

    if (foundF != nullptr)
    {
        Faculty :: Group *foundG = foundF->FindGroup(group_id);

        if (foundG != nullptr)
        {
            //cout<<"Группа найдена\n";
            Faculty :: Group :: Student *new_student = new Faculty :: Group :: Student (first_name, last_name, birth_year, foundG);
            foundG->students_list_.push_back(new_student);
            this->students_list_.push_back(new_student);
        }
        else
            cout<<"Error. Student wasn't added. Group №"<<group_id<<" was not found\n";
    }
    else
        cout<<"Error. Student wasn't added. Faculty'"<<faculty<<"' was not found\n";


    return;
}

void University :: DisplayHierarchy () const
{
    for (unsigned short counter1 = 0; counter1 < this->faculties_list_.size(); counter1 ++)
    {
        cout<<this->faculties_list_[counter1]->faculty_short_title_<<" ("<<
            this->faculties_list_[counter1]->groups_list_.size()<<"):\n";

        for (unsigned short counter2 = 0; counter2 < this->faculties_list_[counter1]->groups_list_.size(); counter2 ++)
        {
            cout<<"\t# "<<this->faculties_list_[counter1]->groups_list_[counter2]->group_id_
                <<" ("<<this->faculties_list_[counter1]->groups_list_[counter2]->students_list_.size()
                <<"):\n";

            for (unsigned short counter3 = 0; counter3 < this->faculties_list_[counter1]->groups_list_[counter2]->students_list_.size(); counter3 ++)
            {
                cout<<"\t\t"<<this->faculties_list_[counter1]->groups_list_[counter2]->students_list_[counter3]->last_name_<<" "
                    <<this->faculties_list_[counter1]->groups_list_[counter2]->students_list_[counter3]->first_name_[0]<<". "
                    <<this->faculties_list_[counter1]->groups_list_[counter2]->students_list_[counter3]->birth_year_;

                cout<<" <marks ("<<this->faculties_list_[counter1]->groups_list_[counter2]->students_list_[counter3]->marks_.size()<<"): [";

                for (unsigned short counter4 = 0; counter4 < this->faculties_list_[counter1]->groups_list_[counter2]->students_list_[counter3]->marks_.size(); counter4 ++)
                {
                    cout<<this->faculties_list_[counter1]->groups_list_[counter2]->students_list_[counter3]->marks_[counter4]<<(counter4 != this->faculties_list_[counter1]->groups_list_[counter2]->students_list_[counter3]->marks_.size() - 1 ? ", " : "");
                }

                cout<<"]>\n";

            }
        }
    }
    return;
}

void University :: PrintGroupList () const
{
    cout<<"Totally groups ("<<this->groups_list_.size()<<")\n";
    for (unsigned short counter = 0; counter < this->groups_list_.size(); counter ++)
    {
        cout<<"\t№ "<<this->groups_list_[counter]->group_id_<<" ("<<this->groups_list_[counter]->parent_faculty_->faculty_short_title_<<")\n";
    }

    return;
}

void University :: AddMark (const string &group_name, const string &last_name,
                            const unsigned short &mark)
{
    Faculty :: Group *found = nullptr;

    for (unsigned short counter = 0; counter < this->groups_list_.size(); counter ++)
        if (this->groups_list_[counter]->group_id_ == group_name)
        {
            found = groups_list_[counter];
            break;
        }

    if (found != nullptr)
    {
        Faculty :: Group :: Student *foundS = nullptr;

        for (unsigned short counter = 0; counter < found->students_list_.size(); counter ++)
            if (found->students_list_[counter]->last_name_ == last_name)
            {
                foundS = found->students_list_[counter];
                break;
            }

        if (foundS != nullptr)
        {
            foundS->marks_.push_back(mark);
        }
        else
        {
            cout<<"Error. Can't add mark. No student in such group\n";
        }
    }
    else
    {
        cout<<"Error. Can't add mark. Group wasn't found\n";
    }
    return;
}

void University :: PrintExcellentStudents (const string &group_id) const
{
    Faculty :: Group *found = nullptr;

    for (unsigned short counter = 0; counter < this->groups_list_.size(); counter ++)
        if (this->groups_list_[counter]->group_id_ == group_id)
        {
            found = this->groups_list_[counter];
            break;
        }


    if (found != nullptr)
    {
        cout<<"Excellent students in group "<<group_id<<": ";
        for (unsigned short counter = 0; counter < found->students_list_.size(); counter ++)
        {
            //cout<<found->students_list_[counter]->last_name_<<",";
            if (found->students_list_[counter]->IsExcellent())
                cout<<found->students_list_[counter]->last_name_<<", ";
        }
        cout<<"\n";
    }
    else
    {
        cout<<"Error. Can't add mark. Group wasn't found\n";
    }
    return;
}

bool University :: Faculty :: Group :: Student :: IsExcellent () const
{
    if (this->marks_.size() == 0)
        return false;

    unsigned short sum = 0;
    for (unsigned short counter = 0; counter < this->marks_.size(); counter ++)
        sum += this->marks_[counter];

    return ((sum / this->marks_.size()) >= 8 ? true : false);
}

void University :: PrintAllStudents () const
{
    cout<<"All students: \n";
    for (unsigned short counter = 0; counter < this->students_list_.size(); counter ++)
        cout<<"\t"<<this->students_list_[counter]->last_name_<<" ("<<this->students_list_[counter]->parent_group_->group_id_<<")\n";
}
