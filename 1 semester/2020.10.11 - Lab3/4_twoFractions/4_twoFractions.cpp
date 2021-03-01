#include <iostream>

using std::cout;
using std::cin;
using std::swap;
using std::ios_base;

long long GCD (long long a, long long b)
{
    while (b)
    {
        a %= b;
        swap (a, b);
    }

    return a;
}

void startingSettings(long long &a, long long &b, bool &sign)
{
    if (a > 0 && b > 0)
        sign = true;
    else if (a > 0 && b < 0)
        sign = false;
    else if (a < 0 && b > 0)
        sign = false;
    else
        sign = true;

    a = (a > 0) ? a : (a * (-1));
    b = (b > 0) ? b : (b * (-1));

    long long gcdOfNumeratorAndDenominator = GCD(a, b);

    a /= gcdOfNumeratorAndDenominator;
    b /= gcdOfNumeratorAndDenominator;

    return;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    long long a1, b1,
         a2, b2;


    cin>>a1>>b1>>a2>>b2;

    if (a1 == 0 && a2 == 0)
    {
        cout<<0;
        return 0;
    }

    bool sign1, sign2;

    startingSettings(a1, b1, sign1);
    startingSettings(a2, b2, sign2);

    //можно сразу отсеить, если разные знаки
    if (sign1 != sign2)
    {
        cout<<(sign1 == true ? 1 : -1);
        return 0;
    }

    // если они всё же одного знака
    long double firstFraction = (long double)((long double)a1 / (long double)b1);
    long double secondFraction = (long double)((long double)a2 / (long double)b2);

    if (firstFraction > secondFraction)
    {
        cout<<(sign1 == true ? 1 : -1);
    }
    else if (firstFraction < secondFraction)
    {
        cout<<(sign1 == true ? -1 : 1);
    }
    else
    {
        cout<<0;
    }

    return 0;
}
