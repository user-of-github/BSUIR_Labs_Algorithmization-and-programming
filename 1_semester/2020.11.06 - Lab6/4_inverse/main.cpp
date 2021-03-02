#include <iostream>
#include<vector>
using namespace std;

short inverses(vector<short> Array)
{
    short counter = 0;
    for(int i = 0; i < Array.size() - 1; i++)
    {
        for (int j = i + 1; j < Array.size(); j++)
        {
            if( Array[i] > Array[j] )
                counter++;
        }
    }

    return counter;
}
int main()
{
    vector<short> arr(10);
    for (int i = 0; i < 10; i++)
        arr[i] = i + 1;

    bool flag = false;
    for (int i = 0; i < 10 - 1; i++)
    {
        for (int j = 0; j < 10 - i - 1; j++)
        {
            if (arr[j] < arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
            }
            if (inverses(arr) == 23)
            {
                flag = true;
                break;
            }
        }
        if (flag)
            break;
    }

    for (int i = 0; i < 10; i++)
        cout<<arr[i]<<" ";
    cout<<"\n"<<inverses(arr)<<"\n";
    return 0;
}
