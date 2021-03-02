/* I wanted to solve the task without using arrays !! Just with counting while inputing
 (With array it is simple, you know)
 + 2 previous wrong attemps where wrong because I didn't understand requirements :(*/
#include <iostream>

using namespace std;

int main()
{
    int numberOfPenalties = 0,
        sumOfGoals = 0,
        numberOfFails = 0;

    bool attempt, // we need just 0 or 1 value
         firstFail = false,
         secondFail = false;

    cin>>numberOfPenalties;

    for (int counter = 1; counter <= numberOfPenalties; counter++)
    {
        cin>>attempt;

        if (secondFail == false && firstFail == true && attempt == false)
            secondFail = true;

        if (firstFail == false && attempt == false)
            firstFail = true;

        numberOfFails += (int(!attempt));

        if (firstFail == true && secondFail == false)
            sumOfGoals += (int)attempt;


    }

    if (numberOfFails == 0 && numberOfPenalties != 0)
        cout<<"-1\n";
    else if (numberOfFails == 1)
        cout<<"-2\n";
    else
        cout<<sumOfGoals<<"\n";

    return 0;
}
