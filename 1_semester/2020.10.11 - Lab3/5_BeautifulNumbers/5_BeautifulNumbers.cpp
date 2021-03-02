#include <iostream>
#include<algorithm>

using namespace std;

const string NUMERALS[2] = {"13579", "02468"}; // 0 - нечётные, 1 - чётные

bool checkIfBeautiful (string data)
{
    for (int counter = 0; counter < data.size(); counter ++)
    {
        if (NUMERALS[counter % 2].find(data[counter]) == string::npos)
        {
            return false;
        }
    }
    return true;
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int N, numberOfBeautifulNumbers = 0;
    cin>>N;

    string input;
    for (int counter = 1; counter <= N; counter++)
    {
        cin>>input;
        reverse(input.begin(), input.end());

        if(checkIfBeautiful(input))
        {
            numberOfBeautifulNumbers++;
        }
    }

    cout<<numberOfBeautifulNumbers;
    return 0;
}
