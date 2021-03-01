#include <iostream>
#include<vector>

using std::cin,
      std::cout,
      std::vector,
      std::min,
      std::ios_base;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, m;
    cin>>n>>m;

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

    // SOLUTION: O (N * M)

    // prefix sums array (dp[i][j])
    vector<vector<int>> prefixSum;

    for (int row = 0; row < n; row ++)
    {
        vector<int> temp(m);
        prefixSum.push_back(temp);
    }

    // first row and first column in prefix sum array (dp)
    prefixSum[0][0] = input[0][0];

    for (int col = 1; col < m; col++)
    {
        prefixSum[0][col] = input[0][col];
    }

    for (int row = 1; row < n; row++)
    {
        prefixSum[row][0] = input[row][0];
    }


    // dp
    for (int row = 1; row < n; row ++)
    {
        for (int col = 1; col < m; col ++)
        {
            if (input[row][col] == 0)
            {
                prefixSum[row][col] = 0;
            }
            else
            {
                prefixSum[row][col] = min(min(prefixSum[row - 1][col], prefixSum[row - 1][col - 1]), prefixSum[row][col - 1]) + input[row][col];
            }
        }
    }

    int answer = 0;

    for (int row = 0; row < n; row ++)
    {
        for (int col = 0; col < m; col ++)
        {
            answer += prefixSum[row][col];
        }
    }

    cout<<answer;

    return 0;
}
