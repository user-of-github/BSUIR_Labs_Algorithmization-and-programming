/*  � ������ ������ �������� ���������� ����� (�� ����� 10^4). ����� � ������ ������
�������� ���� ��� ��������� ����������� �����, ������� ������� � ��
 ������������� 10^4 , ����������� ���������.
��� ������� ����� ����������, �������� �� ��� ����� �������. */

#include <iostream>
#include <algorithm>

using std::cin,
      std::cout,
      std::ios_base,
      std::sort;

const unsigned int MAX_SIZE = 10002;

bool comparator (const unsigned int &a, const unsigned int &b);
void sieveOfEratosthenes (bool *arr, const unsigned int &length);

int main()
{
    bool SIMPLE [MAX_SIZE];

    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);

    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    unsigned int length = 0;
    cin>>length;

    unsigned int *arr = new unsigned int [length];
    for (unsigned int counter = 0; counter < length; counter ++)
        cin>>arr[counter];

    sort (arr, arr + length, comparator);

    sieveOfEratosthenes(SIMPLE, MAX_SIZE);

    for (unsigned int counter = 0; counter < length; counter ++)
    {
        if (counter > 0 && arr[counter] != arr[counter - 1])
            cout<<"\n"<<arr[counter]<<":"<<((SIMPLE[arr[counter]] == false && arr[counter] != 1) ? "prime" : "composite");
        else if (counter == 0)
            cout<<arr[counter]<<":"<<((SIMPLE[arr[counter]] == false && arr[counter] != 1) ? "prime" : "composite");
    }


    return 0;
}

bool comparator (const unsigned int &a, const unsigned int &b)
{
    return a > b;
}

void sieveOfEratosthenes (bool *arr, const unsigned int &length)
{
    for (unsigned int counter = 2; counter * counter <= length - 1; counter ++)
    {
        if (arr[counter] == false)
        {
            for (unsigned int value = counter * counter; value <= length - 1; value += counter)
                arr[value] = true;
        }
    }

    return;
}

