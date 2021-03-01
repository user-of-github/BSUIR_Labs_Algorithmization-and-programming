#include <iostream>
#include <algorithm>

using std::cin;
using std::cout;
using std::string;
using std::next_permutation;

const string variants[10] = {"0000", "1111", "2222", "3333", "4444", "5555", "6666", "7777", "8888", "9999"};

int main()
{
    cin.tie(NULL);
    cout.tie(NULL);

    short response1,
          response2;

    short numbers[4] {0,0,0,0};
    short numCount = 0;

    for (short counter = 0; counter < 10; counter ++)
    {
        cout<<variants[counter]<<"\n";
        cin>>response1>>response2;

        while (response1 > 0)
        {
            numbers[numCount] = static_cast<short>(variants[counter][0] - '0');
            numCount ++;
            response1 --;
        }
        if (numCount >= 4)
            break;
    }

    cout<<numbers[0]<<numbers[1]<<numbers[2]<<numbers[3]<<"\n";
    cin>>response1>>response2;
    if (response1 == 4)
    {
        cout<<"Success!\n";
        return 0;
    }

    for (short counter = 0; counter < 24; counter ++)
    {
        next_permutation(numbers, numbers + 4);

        cout<<numbers[0]<<numbers[1]<<numbers[2]<<numbers[3]<<"\n";
        cin>>response1>>response2;

        if (response1 == 4)
            break;
    }

    cout<<"Success!\n";
    return 0;
}
