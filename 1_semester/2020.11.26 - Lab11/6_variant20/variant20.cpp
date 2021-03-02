/* � ��������� ����� � ������ ������ �������� �����
����� (�� ����� 10000) � ���������� ��������� � �������,
� ��������� ������� �� ������ ������ ����� � �������� ����� �������.
����� ���������� ��������� �������, ������ ��������� ������� ��� �������������
������� �� 33. ��� ����� ��������� � ��������� �� 00 �� 10^9 */
#include <iostream>

using std::cin,
      std::cout,
      std::ios_base;

int main()
{
    freopen ("in.txt", "r", stdin);
    freopen ("out.txt", "w", stdout);

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    unsigned short length = 0;
    cin>>length;

    unsigned long long temp = 0;

    unsigned short remainder0 = 0,
                   remainder1 = 0,
                   remainder2 = 0;

    for (unsigned short counter = 0; counter < length; counter ++)
    {
        cin>>temp;
        cout<<temp<<(counter != length - 1 ? " " : "");

        if (temp % 3 == 0)
        {
            remainder0 ++;
        }
        else if (temp % 3 == 1)
        {
            remainder1 ++;
        }
        else
        {
            remainder2 ++;
        }
    }

    if (length != 0)
    {
        cout<<"\n"<<remainder0<<" "<<remainder1<<" "<<remainder2;
    }

    return 0;
}
