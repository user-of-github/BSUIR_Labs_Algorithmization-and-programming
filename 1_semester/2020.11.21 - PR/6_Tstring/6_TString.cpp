#include <iostream>
#include <string.h>

using std::cin,
      std::cout,
      std::ios_base,
      std::ostream,
      std::istream;


class TString
{
private:
    char *value;
    short length;
public:
    // Constructors, destructors
    TString (int _length)
    {
        this->length = _length;
        this->value = new char [this->length + 1];
        for (short counter = 0; counter < this->length; counter ++)
            this->value[counter] = '5';
    }
    TString (char *_str)
    {
        this->length = strlen(_str);
        this->value = new char [this->length + 1];
        for (short counter = 0; counter < this->length; counter ++)
            this->value[counter] = _str[counter];
    }
    ~TString ()
    {
        delete [] this->value;
    }

    // operators
    TString operator+ (TString a)
    {
        TString result((this->length + a.length));

        for (short counter = 0; counter < this->length; counter ++)
            result.value[counter] = this->value[counter];

        for (short counter = 0; counter < a.length; counter ++)
            result.value[counter + this->length]  = a.value[counter];

        return result;
    }
    friend ostream& operator<< (ostream &cout, const TString &m)
    {
        for (short counter = 0; counter < m.length; counter ++)
            cout<<m.value[counter];
        cout<<"\n";

        return cout;
    }

    // methods
    void Push(char symbol)
    {
        char *backup = new char [this->length + 1];
        for (short counter = 0; counter < this->length; counter ++)
            backup[counter] = this->value[counter];

        delete[] this->value;
        this->length ++;
        this->value = new char [this->length + 1];


        for (short counter = 0; counter < this->length - 1; counter ++)
            this->value[counter] = backup[counter];

        this->value[this->length - 1] = symbol;

        delete[] backup;

        return;
    }
};
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    TString a("4848"); // 4848
    TString b("5848"); // 5848

    cout<<(a + b); // 48485848

    a.Push('p');
    cout<<(a); // 4848p

    return 0;
}
