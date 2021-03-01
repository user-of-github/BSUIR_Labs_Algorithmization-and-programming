/* � ��������� ����� � ������ ������ �������� ����
����������� �����. ��� ������� ����� ����������, �������� ��
��� ����� �����������, ���������� ��� �������������
(����������� ����� ����� ����� ���� ����� ���������, �������������
� ���������� ����� �������������� ������ ��� ������ ���� �����).
���������� ����� �� ����������� 100100, � ���� ����� �� ����������� 10^6*/

#include <iostream>
#include <algorithm>

using std::cin,
      std::cout,
      std::ios_base,
      std::sort,
      std::string;

bool comparator (const unsigned int &a, const unsigned int &b)
{
    return a < b;
}

string typeOfNumber (const unsigned int &num)
{
    string response = "";
    if (num == 1)
        response = "deficient";
    else
    {
        unsigned int sum = 1;
        for (unsigned int divider = 2; divider < num; divider ++)
            sum += (num % divider == 0 ? divider : 0);

        response = (sum > num ? "abundant" : (sum == num ? "perfect" : "deficient"));
    }

    return response;
}

int main()
{
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);

    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    unsigned int data[100];
    unsigned short length = 0;

    unsigned long long temp;
    while (cin >> temp)
    {
        length ++;
        data[length - 1] = temp;
    }

    sort (data, data + length, comparator);

    for (unsigned int counter = 0; counter < length; counter ++)
    {
        if (counter > 0 && data[counter] != data[counter - 1])
            cout<<"\n"<<data[counter]<<":"<<typeOfNumber(data[counter]);
        else if (counter == 0)
            cout<<data[counter]<<":"<<typeOfNumber(data[counter]);
    }

    return 0;
}
