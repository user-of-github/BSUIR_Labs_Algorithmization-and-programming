#include <iostream>

using std::cin,
      std::cout,
      std::ios_base;


int length, numberOnes;

unsigned long long numberOfSequences(int currentOnes, int currentLength)
{
    if (currentLength == length)
    {
        if (currentOnes == numberOnes)
            return 1;
        else
            return 0;
    }

    if (currentOnes > numberOnes)
            return 0;

    return numberOfSequences(currentOnes + 1, currentLength) + numberOfSequences(currentOnes, currentLength);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);


    cin>>length>>numberOnes;
    cout<<numberOfSequences(0, 0);
    return 0;
}
