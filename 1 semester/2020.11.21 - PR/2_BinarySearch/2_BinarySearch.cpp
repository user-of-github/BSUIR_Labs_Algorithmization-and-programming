#include <iostream>

using std::cin,
      std::cout,
      std::ios_base;

struct ResponseToRequest
{
    bool found = true;
    int index = 0;
};

ResponseToRequest binarySearch(int *arr, int &length, int &desiredElement);

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int length;
    cin>>length;
    int *numbers = new int [length];
    for (int counter = 0; counter < length; counter ++)
        cin>>numbers[counter];

    int numberOfRequests;
    cin>>numberOfRequests;

    int query;
    ResponseToRequest answer;
    int temp;

    for (int request = 0; request < numberOfRequests; request ++)
    {
        cin>>query;
        answer = binarySearch(numbers, length, query);
        cout<<(answer.found)<<' ';
        if (answer.found)
        {
            temp = answer.index;
            while (numbers[temp - 1] == query && temp > 0)
                temp --;
            cout<<temp<<' ';
            temp = answer.index;
            while (numbers[temp] == query)
                temp ++;
            cout<<temp;
        }
        else
        {
            if (numbers[answer.index] > query)
                cout<<(answer.index)<<' '<<(answer.index);
            else
                cout<<(answer.index + 1)<<' '<<(answer.index + 1);
        }

        cout<<'\n';
    }

    return 0;
}

ResponseToRequest binarySearch(int *arr, int &length, int &desiredElement)
{
    int left = 0,
        right = length - 1;

    int middle;
    while (left <= right)
    {
        middle = (left + right) / 2;
        if (arr[middle] == desiredElement)
            break;
        else if (arr[middle] > desiredElement)
            right = middle - 1;
        else
            left = middle + 1;
    }

    ResponseToRequest answer;

    if (arr[middle] == desiredElement)
        answer.found = true;
    else
        answer.found = false;

    answer.index = middle;

    return answer;
}

