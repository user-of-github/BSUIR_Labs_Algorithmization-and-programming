#include<iostream>
#include<vector>

using std::string, std::ios_base, std::cin, std::cout, std::vector;

bool notEqualArrays(vector<char> &arr1,vector<char> &arr2);
void arrayOfNumbers(string &str, vector<char> &arr);
void makePalindrom(vector<char> &arr);
bool compareIfGreater(vector<char> &arr1, vector<char> &arr2);
void printNumber(vector<char> &arr);

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    string input;
    cin>>input;
    short length = input.size();
    vector<char> original(length);
    vector<char> MAIN(length);

    arrayOfNumbers(input, original);
    arrayOfNumbers(input, MAIN);

    makePalindrom(MAIN);

    if (compareIfGreater(MAIN, original) == true)
    {
        printNumber(MAIN);
    }
    else
    {
        arrayOfNumbers(input, MAIN);
        short position = ((length % 2) == 0 ? (length / 2 - 1) : (length / 2));
        MAIN[position] = (MAIN[position] + 1) % 10;

        if (MAIN[position] == 0)
        {
            position--;
            while (MAIN[position] == 9 && position >= 0)
            {

                MAIN[position] = 0;
                position --;
            }

            if (position <= 0 && MAIN[0] == 0)
            {
                MAIN.push_back(0);
                for (short i = 0; i < MAIN.size() - 1; i ++)
                    MAIN[i + 1] = MAIN[i];

                MAIN[0] = 1;
            }
            else
            {
                MAIN[position] += 1;
            }
        }

        makePalindrom(MAIN);
        printNumber(MAIN);
    }


    return 0;
}

bool notEqualArrays(vector<char> &arr1,vector<char> &arr2)
{
    for (int counter = 0; counter < arr1.size(); counter ++)
        if (arr1[counter] != arr2[counter])
            return true;
    return false;
}

void arrayOfNumbers(string &str, vector<char> &arr)
{
    for (short counter = 0; counter < arr.size(); counter ++)
    {
        arr[counter] = (str[counter] - '0');
    }

    return;
}
void makePalindrom(vector<char> &arr)
{
    for (short counter = 0; counter < (arr.size() / 2); counter ++)
    {
        arr[arr.size() - counter - 1] = arr[counter];
    }

    return;
}
bool compareIfGreater(vector<char> &arr1, vector<char> &arr2)
{
    // сравниваем, что arr1 > arr2
    bool flag = true;
    for (short counter = 0; counter < arr1.size(); counter ++)
    {
        if (arr1[counter] > arr2[counter])
            return true;
        else if (arr1[counter] < arr2[counter])
            return false;
    }


    return notEqualArrays(arr1, arr2);
}

void printNumber(vector<char> &arr)
{
    for (short counter = 0; counter < arr.size(); counter ++)
    {
        cout<<static_cast<int>(arr[counter]);
    }

    return;
}

