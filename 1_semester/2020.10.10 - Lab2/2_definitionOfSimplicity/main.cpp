/* ���� ����������� ����� X, �� ������������� longint.
���������� ������� YES ���� ��� �������, � NO ���� ���.  */

#include <fstream>
#include <cmath>
using namespace std;

int main()
{
    unsigned long long X;

    ifstream read("input.txt");
    ofstream write("output.txt");

    read >> X;

    if (X == 1)
    {
        write<<"NO";
        return 0;
    }

    for (unsigned long long divider = 2; divider <= sqrt(X); divider++)
    {
        if (X % divider == 0)
        {
            write<<"NO";
            return 0;
        }
    }

    write<<"YES";


    return 0;
}
