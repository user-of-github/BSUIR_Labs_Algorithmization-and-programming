#ifndef CALCULATOR_H_INCLUDED
#define CALCULATOR_H_INCLUDED

#include <map>
#include <stack>

using std :: ostream;
using std :: map;
using std :: stack;


class Calculator
{
private:
    /* declared later
    basic "const" collections of digits, brackets and signs of operators */
    static map <char,char> PRIORITIES;
    static string DIGITS;
    static string OPERATORS;
    static string BRACKETS;

    string original_string_ = "";
    long long answer_ = NULL;

    bool is_already_computed_ = false;

    stack <long long> numbers_;
    stack <char> signs_;

    void Trim (short&, char) const; // method for ignoring (skipping) spaces
    long long GetNumberFromString (short&, short) const;
    long long Pow (const long long &number, const long long &degree) const;
    long long SimpleCalculation (const char&, const long long&, const long long&) const;
    void ExecutionOfPriorityOperators (const char&);
    void ProcessOperator (const short&);

public:
    Calculator (const string&);
    Calculator ();
    ~Calculator ();

    bool CheckingCorrectnessOfBracketSequence () const;
    void Compute ();
    long long Answer ();
    void Clear ();
    void ChangeExpression (const string&);

    friend ostream & operator << (ostream&, const Calculator&);
    long long operator + (Calculator&);
    long long operator - (Calculator&);
    long long operator * (Calculator&);
    long long operator / (Calculator&);
    long long operator ^ (Calculator&);
};

map<char, char> Calculator :: PRIORITIES  =
{
    { '+', 1 },
    { '-', 1 },
    { '*', 2 },
    {'/', 2},
    {'^', 3}
};
string Calculator :: DIGITS = "0123456789";
string Calculator :: OPERATORS = "+-/*^";
string Calculator :: BRACKETS = "()";


Calculator :: Calculator ()
{
    this->is_already_computed_ = false;
    this->answer_ = NULL;
    this->original_string_ = "";
}

Calculator :: Calculator (const string &expression)
{
    this->is_already_computed_ = false;
    this->answer_ = NULL;
    this->original_string_ = expression;
}

Calculator :: ~Calculator ()
{
    this->Clear();
}


void Calculator :: Trim (short &index, char direction) const
{
    while (index < this->original_string_.size() && index >= 0 && this->original_string_[index] == ' ' )
        index += direction;

    return;
}

void Calculator :: ExecutionOfPriorityOperators (const char &new_priority)
{
    while (!this->signs_.empty() && !this->numbers_.empty() && new_priority <= this->PRIORITIES[this->signs_.top()])
    {
        long long second = this->numbers_.top();
        this->numbers_.pop();

        long long first = this->numbers_.top();
        this->numbers_.pop();

        // cout<<"Now it'll be : "<<first<<this->signs_.top()<<second<<"\n";
        this->numbers_.push(this->SimpleCalculation(this->signs_.top(), first, second));
        this->signs_.pop();
    }
    return;
}

void Calculator :: ProcessOperator (const short &index)
{
    char new_sign = this->original_string_[index];

    if (this->signs_.empty())
    {
        this->signs_.push(new_sign);
    }
    else
    {
        char new_priority = this->PRIORITIES[new_sign];

        if (new_priority > this->PRIORITIES[this->signs_.top()])
        {
            this->signs_.push(new_sign);
        }
        else
        {
            // cout<<"Well, now there will be some real computings\n";
            if (new_sign == '^')
            {
                this->signs_.push(new_sign);
            }
            else if (new_sign != '^' && this->signs_.top() == '^')
            {
                while (!this->signs_.empty() && !this->numbers_.empty() && this->signs_.top() == '^')
                {
                    long long second = this->numbers_.top();
                    this->numbers_.pop();

                    long long first = this->numbers_.top();
                    this->numbers_.pop();

                    this->numbers_.push(this->SimpleCalculation(this->signs_.top(), first, second));
                    this->signs_.pop();
                }

                this->ExecutionOfPriorityOperators(new_priority);
                this->signs_.push(new_sign);
            }
            else
            {
                this->ExecutionOfPriorityOperators(new_priority);
                this->signs_.push(new_sign);
            }
        }
    }

    return;
}

bool Calculator :: CheckingCorrectnessOfBracketSequence () const
{
    stack<char> MAIN;

    for (unsigned short counter = 0; counter < this->original_string_.size(); counter++)
    {
        if (this->BRACKETS.find(this->original_string_[counter]) != string :: npos)
        {
            if (MAIN.empty())
                MAIN.push(this->original_string_[counter]);
            else
            {
                if (this->original_string_[counter] == this->BRACKETS[1] && MAIN.top() == this->BRACKETS[0])
                    MAIN.pop();
                else
                    MAIN.push(this->original_string_[counter]);
            }
        }
    }

    return (MAIN.empty() == true);
}

long long Calculator :: Pow (const long long &number, const long long &degree) const
{
    if (degree == 0)
        return 1;

    if (degree % 2 == 0)
        return (this->Pow(number, degree / 2) * this->Pow(number, degree / 2));
    else
        return (number * this->Pow(number, degree / 2) * this->Pow(number, degree / 2));
}

long long Calculator :: GetNumberFromString (short &start_index, short sgn) const
{
    long long number = 0;

    while (this->DIGITS.find(original_string_[start_index]) != string::npos && start_index < this->original_string_.size())
    {
        number = number * 10 + static_cast<int>(original_string_[start_index] - '0');
        start_index ++;
    }

    return (number * sgn);
}

long long Calculator :: SimpleCalculation (const char &operation, const long long &first, const long long &second) const
{
    long long answer_ = 0;

    switch (operation)
    {
    case '+':
    {
        answer_ = first + second;
        break;
    }
    case '-':
    {
        answer_ = first - second;
        break;
    }
    case '*':
    {
        answer_ = first * second;
        break;
    }
    case '/':
    {
        answer_ = first / second;
        break;
    }
    case '^':
    {
        answer_ = this->Pow(first, second);
        break;
    }
    default:
    {
        break;
    }
    }

    return answer_;
}

void Calculator :: Compute ()
{
    if (this->is_already_computed_)
        return;

    if (!this->CheckingCorrectnessOfBracketSequence())
    {
        cout<<"The bracket sequence is not correct !\n";
        return;
    }

    // cout<<"Compution has begun \n";

    short INDEX = 0;
    this->Trim(INDEX, 1);

    if (original_string_[INDEX] == '-')
    {
        INDEX ++;
        this->numbers_.push(0);
        this->signs_.push('-');
    }

    while (INDEX < this->original_string_.size())
    {
        this->Trim(INDEX, 1);

        // 4 occasions: numbers, minus, other operations, braces

        // number
        if (this->DIGITS.find(this->original_string_[INDEX]) != string::npos)
        {
            this->numbers_.push(this->GetNumberFromString(INDEX, true));
            // cout<<"Found a number "<<this->numbers_.top()<<"\n";
        }
        // minus
        else if (this->original_string_[INDEX] == '-')
        {
            /* if digits on the right and no digits on the left,
            it is a negative number */

            short tempIndex = INDEX + 1;
            this->Trim(tempIndex, 1);

            // check if there are numbers on the right
            bool first_condition = (this->DIGITS.find(this->original_string_[tempIndex]) != string::npos);
            // check if there are not numbers on the right
            bool second_condition;

            tempIndex = INDEX - 1;

            this->Trim(tempIndex, -1);

            if (tempIndex < 0)
                second_condition = true;
            else
                second_condition = (this->DIGITS.find(this->original_string_[tempIndex]) == string::npos &&
                                    this->original_string_[tempIndex] != this->BRACKETS[1]);

            if (first_condition && second_condition)
            {
                // Ok, it is a negative number
                INDEX++;
                this->numbers_.push(this->GetNumberFromString(INDEX, -1));
            }
            else
            {
                // Minus - is just a sign
                this->ProcessOperator(INDEX);
                INDEX ++;
            }
        }
        // operation sign
        else if (this->OPERATORS.find(this->original_string_[INDEX]) != string::npos)
        {
            this->ProcessOperator(INDEX);
            INDEX++;
        }
        // bracket
        else if (this->BRACKETS.find(this->original_string_[INDEX]) != string::npos)
        {
            if (this->original_string_[INDEX] == this->BRACKETS[0]) // opening bracket
            {
                this->signs_.push(this->original_string_[INDEX]);
            }
            else // closing bracket
            {
                while (this->signs_.top() != this->BRACKETS[0])
                {
                    long long second = this->numbers_.top();
                    this->numbers_.pop();
                    long long first = this->numbers_.top();
                    this->numbers_.pop();

                    this->numbers_.push(this->SimpleCalculation(this->signs_.top(), first, second));
                    this->signs_.pop();
                }

                this->signs_.pop();
            }

            INDEX++;
        }
    }


    // perform the remaining actions in turn
    while (!this->signs_.empty())
    {
        long long second = this->numbers_.top();
        this->numbers_.pop();
        long long first = this->numbers_.top();
        this->numbers_.pop();

        // cout<<"Now it'll be : "<<first<<this->signs_.top()<<second<<"\n";

        this->numbers_.push(this->SimpleCalculation(this->signs_.top(), first, second));
        this->signs_.pop();
    }

    this->answer_ = this->numbers_.top();
    this->is_already_computed_ = true;

    while (this->numbers_.empty() != true)
        this->numbers_.pop();

    return;
}

long long Calculator :: Answer ()
{
    if (!this->is_already_computed_)
        this->Compute();

    return this->answer_;
}

void Calculator :: Clear ()
{
    while (!this->signs_.empty())
        this->signs_.pop();

    while (!this->numbers_.empty())
        this->numbers_.pop();

    this->answer_ = NULL;
    this->is_already_computed_ = false;
    this->original_string_ = "";

    return;
}

void Calculator :: ChangeExpression (const string &expression)
{
    this->Clear();
    this->original_string_ = expression;

    return;
}


ostream & operator << (ostream &cout, const Calculator &problem)
{
    cout<<problem.original_string_<<" = ";
    if (problem.is_already_computed_ == true)
        cout<<problem.answer_;
    else
        cout<<"undefined";

    cout<<"\n";
    return cout;
}

long long Calculator :: operator + (Calculator &value)
{
    return (this->SimpleCalculation('+', this->Answer(), value.Answer()));
}

long long Calculator :: operator - (Calculator &value)
{
    return (this->SimpleCalculation('-', this->Answer(), value.Answer()));
}

long long Calculator :: operator * (Calculator &value)
{
    return (this->SimpleCalculation('*', this->Answer(), value.Answer()));
}

long long Calculator :: operator / (Calculator &value)
{
    return (this->SimpleCalculation('/', this->Answer(), value.Answer()));
}

long long Calculator :: operator ^ (Calculator &value)
{
    return (this->SimpleCalculation('^', this->Answer(), value.Answer()));
}

#endif // CALCULATOR_H_INCLUDED
