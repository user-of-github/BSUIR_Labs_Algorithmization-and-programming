/* „исло назовЄм красивым, если
в его дес€тичной записи на чЄтных позици€х сто€т чЄтные
цифры, а на нечЄтных Ц нечЄтные. ÷ифры 0, 2, 4, 6, 8 считаютс€ чЄтными,
остальные цифры Ц нечЄтными. Ќумераци€ позиций цифр в числе начинаетс€
с единицы и ведЄтс€ справа налево.

¬ам требуетс€ определить, сколько из N введЄнных чисел €вл€ютс€ красивыми. */

#include <iostream>
#include<algorithm>

using namespace std;

const string NUMERALS[2] = {"13579", "02468"}; // 0 - нечЄтные, 1 - чЄтные

bool checkIfBeautiful (string data)
{
    for (int counter = 0; counter < data.size(); counter ++)
    {
        if (NUMERALS[counter % 2].find(data[counter]) == string::npos)
            return false;
    }
    return true;
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int N, numberOfBeautifulNumbers = 0;
    cin>>N;

    string input;
    for (int counter = 1; counter <= (int)N; counter++)
    {
        cin>>input;
        reverse(input.begin(), input.end());

        if(checkIfBeautiful(input))
            numberOfBeautifulNumbers++;
    }

    cout<<numberOfBeautifulNumbers;
    return 0;
}
