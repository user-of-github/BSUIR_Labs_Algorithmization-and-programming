/* Дано целое неотрицательное число X, не превышающее longint.
Вывести количество и сумму цифр этого числа. */
#include <fstream>

using namespace std;

int main()
{
    ifstream read("input.txt");
    ofstream write("output.txt");

    unsigned long long X;

    read>>X;

    char numberOfDigits = ((X == 0) ? 1 : 0),
         sumOfDigits = 0;

    while (X > 0)
    {
        sumOfDigits += X%10;
        numberOfDigits ++;

        X /= 10;
    }

    write<<((int)numberOfDigits)<<" "<<((int)sumOfDigits);


    return 0;
}
