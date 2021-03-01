/* Дано натуральное число X, не превосходящее longint.
Необходимо вывести YES если оно простое, и NO если нет.  */

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
