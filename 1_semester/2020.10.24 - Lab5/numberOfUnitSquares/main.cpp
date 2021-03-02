#include <iostream>
#include<vector>
using std::cin,
      std::cout,
      std::vector,
      std::min,
      std::ios_base;

bool checkIfFits(vector<vector<int>> sums, int i0, int j0, int i1, int j1)
{
    int neededSum = (i1 - i0 + 1)*(j1 - j0 + 1);
    int big = sums[i1][j1],
        up = (((i0 - 1) >= 0) ? sums[i0 - 1][j1] : 0),
        left = (((j0 - 1) >= 0) ? sums[i1][j0 - 1] : 0),
        diagonal = (((j0 - 1) >= 0 && (i0 - 1)>=0) ? sums[i0 - 1][j0 - 1] : 0);

    return (neededSum == (big + diagonal- up - left));
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, m;
    cin>>n>>m;

    // initializing input
    vector<vector<bool>> input;

    // filling input
    for (int row = 0; row < n; row++)
    {
        vector<bool> temp;
        for (int col = 0; col < m; col++)
        {
            bool tmp;
            cin>>tmp;
            temp.push_back(tmp);
        }
        input.push_back(temp);
    }


    // initializing prefix sums array (dp[i][j])
    vector<vector<int>> prefixSum;
    for (int row = 0; row < n; row++)
    {
        vector<int> temp(m);
        prefixSum.push_back(temp);
    }

    // initializing first row and first column in prefix sum array (dp)
    prefixSum[0][0] = (input[0][0]);

    for (int col = 1; col < m; col++)
        prefixSum[0][col] = prefixSum[0][col - 1] + (input[0][col]);

    for (int row = 1; row < n; row++)
        prefixSum[row][0] = prefixSum[row - 1][0] + (input[row][0]);


    for (int row = 1; row < n; row++)
    {
        for (int col = 1; col < m; col++)
        {
            prefixSum[row][col] = prefixSum[row - 1][col] + prefixSum[row][col - 1] - prefixSum[row - 1][col - 1] + (input[row][col]);
        }
    }
    int answer = 0;
    for (int row = 0; row < n; row ++)
    {
        for (int col = 0; col < m; col ++)
        {
            if (input[row][col] == 0)
                continue;
            else
            {
                int leftI = row,
                    leftJ = col;

                int delta = min((m - col - 1), (n - row - 1));

                int rightI = leftI + delta,
                    rightJ = leftJ + delta;

                int middI,
                    middJ;

                middI = (leftI + rightI) / 2;
                middJ = (leftJ + rightJ) / 2;

                while (leftI < rightI && leftJ < rightJ)
                {
                    if (middI == leftI && middJ == leftJ && (leftI == rightI - 1))
                    {
                        if (checkIfFits(prefixSum, row, col, rightI, rightJ) == true)
                        {
                            break;
                        }
                        else
                        {
                            rightI = leftI;
                            rightJ = leftJ;
                            break;
                        }
                    }
                    middI = (leftI + rightI) / 2;
                    middJ = (leftJ + rightJ) / 2;

                    if (checkIfFits(prefixSum, row, col, middI, middJ) == true)
                    {
                        leftI = middI;
                        leftJ = middJ;
                    }
                    else
                    {
                        rightI = middI;
                        rightJ = middJ;
                    }
                }

                answer += (rightI - row + 1);
            }
        }
    }


    cout<<answer;

    return 0;
}
