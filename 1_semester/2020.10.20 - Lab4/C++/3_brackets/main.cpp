#include <iostream>
#include<stack>
#include<vector>
#include<algorithm>
// O(n) (линия)
int main()
{
    const std::string TEMPLATE = "()[]{}<>";

    /*std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);*/

    std::string input;
    std::getline(std::cin, input);

    std::stack<char> MAIN;


    for (short counter = 0; counter < input.size(); counter++)
    {
        if (MAIN.empty())
        {
            MAIN.push(input[counter]);
        }
        else
        {
            short indexSymbol = TEMPLATE.find(input[counter]),
                  indexTop = TEMPLATE.find(MAIN.top());

            if ((indexSymbol == (indexTop + 1)) && (indexSymbol % 2 == 1))
                MAIN.pop();
            else
                MAIN.push(input[counter]);
        }
    }
    /* short indexSymbol = TEMPLATE.find(input[counter]),
                      indexTop = TEMPLATE.find(MAIN.top());

                if ((indexSymbol == (indexTop + 1)) && (indexSymbol % 2 == 1))
                    MAIN.pop();
                else
                    MAIN.push(input[counter]);
                    */

    if (MAIN.empty())
    {
        std::cout<<"Correct brackets sequence\n";
    }
    else
    {
        std::cout<<"Uncorrect sequence of brackets\n";
        /* вот здесь что-то странное
        std::vector<char> leftBrackets(MAIN.size());
        while(!MAIN.empty())
        {
            if (TEMPLATE.find(MAIN.top()) != std::string::npos)
                leftBrackets.push_back(MAIN.top());
            MAIN.pop();
        }
        reverse(leftBrackets.begin(), leftBrackets.end());

        int k_opening = 0,
            k_closing = 0;

        for (int counter = 0; counter < leftBrackets.size(); counter ++)
        {
            k_opening += (TEMPLATE.find(leftBrackets[counter]) % 2 == 0 ? 1 : 0);
            k_closing += (TEMPLATE.find(leftBrackets[counter]) % 2 == 1 ? 1 : 0);
            std::cout<<leftBrackets[counter]<<" "<<k_opening<<" "<<k_closing<<"\n";
        }

        std::cout<<"You need to add "<<(std::max(k_closing, k_opening) - std::min(k_closing, k_opening))<<" brackets\n";
        */
    }

    return 0;
}
