#include <iostream>

using std :: cout;
using std :: cin;
using std :: ios;
using std :: string;
using std :: getline;

#include "calculator.h"

int main()
{
    cout.setf(ios :: boolalpha);
    cin.tie(NULL);
    cout.tie(NULL);

    Calculator example("-(3*5) * (125^2 / 25^3 + 6)");
    cout<<example; // -(3*5) * (125^2 / 25^3 + 6) = undefined

    example.Compute();
    cout<<example; // -(3*5) * (125^2 / 25^3 + 6) = -105

    example.ChangeExpression("5 * 6 + -5 + 4 / 4");
    cout<<example.Answer()<<"\n"; // 26

    example.ChangeExpression("5 - 5^0"); // 5 - 5^0 = 4
    example.Compute();
    cout<<example;

    example.ChangeExpression(" (-5 - (5^5)) / 5 ");
    cout<<example.CheckingCorrectnessOfBracketSequence()<<"\n"; // true
    example.Compute();
    cout<<example; // (-5 - (5^5)) / 5  = -626

    example.ChangeExpression("(42)-((42))");
    example.Compute();
    cout<<example; // (42)-((42)) = 0

    example.ChangeExpression("2^(2^3)");
    example.Compute();
    cout<<example; // 2^(2^3) = 256

    Calculator example2("-5+6-5+6^3");
    example2.Compute();
    cout<<example2; // -5+6-5+6^3 = 212

    cout<<(example2 + example)<<"\n"; // 468

    example2.ChangeExpression("-2 * 3^2^3 - 3"); // -2 * 3^2^3 - 3 = -13125
    example2.Compute();
    cout<<example2;


    string usersTest;
    getline(cin, usersTest);
    Calculator test(usersTest);
    test.Compute();
    cout<<test;


    return 0;
}
