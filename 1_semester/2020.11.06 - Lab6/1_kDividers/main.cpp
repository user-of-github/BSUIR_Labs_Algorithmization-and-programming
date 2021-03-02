#include <iostream>

using std::cin, std::cout, std::ios_base;

int main()
{
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    const int k = 23;
    int length = (2 * k + 20) * 10;
    char *brackets = new char [length];
    for (int i = 0; i < length; i++)
        brackets[i] = ' ';

    int L = length / 2;
    int R = L + 1;
    for (int counter = 0; counter < 2*k+20; counter++)
    {
        if (rand()%2 == 0)
        {
            brackets[R] = '(';
            brackets[R + 1] = ')';
            R += 2;
        }
        else
        {
            brackets[R] = ')';
            brackets[L] = '(';
            L--;
            R++;
        }
    }

    for (int i = 0; i < length; i++)
        cout<<brackets[i];

    return 0;
}
