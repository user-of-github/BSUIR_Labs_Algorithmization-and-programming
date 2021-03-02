#include <iostream>
#include<vector>
#include<algorithm>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);


    int N;
    cin>>N;
    vector<long long> MAIN(N);

    for (int i = 0; i < N; i++)
        cin>>MAIN[i];

    vector<int> result;

    int counter = 0, k = 0;
    while (counter < N)
    {
        k = 0;
        int start = counter;
        while(MAIN[counter] == MAIN[start] && counter < N)
            counter++;
        k += (counter - start);
        if (k > 1)
            result.push_back(k);
    }

    if (result.size() == 0)
        cout<<"0 0 0";
    else
    {
        sort(result.begin(), result.end());
        cout<<(result.size())<<" "<<result[result.size() - 1]<<" "<<result[0];
    }


    return 0;
}
