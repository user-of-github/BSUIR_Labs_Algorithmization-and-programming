/*���� ����������� ����� X, �� �������������� longint.
������� ������� ���������, �� ������� ����� ��������� ����� (�� ������������ ������ ��������� X)
� ������� ����������. X>1.
Input */
#include<fstream>
#include<cmath>

using namespace std;

int main()
{
    unsigned long long X;
    ifstream cin("input.txt");
    ofstream cout("output.txt");

    cin>>X;

    if (X == 1)
        cout<<X;
    unsigned long long root = sqrt(X);

    for (unsigned long long divider = 2; divider <= root; divider++)
    {
        while ((X % divider) == 0 && (X > divider))
        {
            X /= divider;
            cout<<divider<<" ";
        }
    }

    if (X != 1)
        cout<<X;

    return 0;
}
