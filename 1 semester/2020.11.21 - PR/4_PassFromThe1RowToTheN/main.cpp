#include <fstream>

using std::ios_base,
      std::min,
      std::ifstream,
      std::ofstream;

int main()
{
    ifstream cin("input.txt");
    ofstream cout("output.txt");

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    short rows,
          cols;

    cin>>rows>>cols;

    /* creation and filling of matrix */
    int **matrix;

    matrix = new int*[rows];
    for (short row = 0; row < rows; row ++)
        matrix[row] = new int [cols];

    for (short row = 0; row < rows; row ++)
        for (short col = 0; col < cols; col ++)
            cin>>matrix[row][col];

    /* creation of DP array */
    unsigned long long **dp;
    dp = new unsigned long long*[rows];
    for (short row = 0; row < rows; row ++)
        dp[row] = new unsigned long long [cols];

    for (short col = 0; col < cols; col ++)
        dp[0][col] = matrix[0][col];


    /* every value is minimum of its upper (higher) neighbours + its own price */
    for (short row = 1; row < rows; row ++)
    {
        dp[row][0] = min(dp[row - 1][0], dp[row - 1][1]) + matrix[row][0];
        for (short col = 1; col < cols - 1; col ++)
        {
            dp[row][col] = min(dp[row - 1][col - 1], min(dp[row - 1][col], dp[row - 1][col + 1])) + matrix[row][col];
        }
        dp[row][cols - 1] = min(dp[row - 1][cols - 1], dp[row - 1][cols - 2]) + matrix[row][cols - 1];
    }

    unsigned long long min_value = dp[rows - 1][0];
    for (int col = 0; col < cols; col ++)
    {
        if (dp[rows - 1][col] < min_value)
            min_value = dp[rows - 1][col];
    }

    cout<<(min_value);
    return 0;
}
