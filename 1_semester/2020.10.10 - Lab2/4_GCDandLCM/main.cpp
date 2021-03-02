
#include<fstream>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);

    ifstream cin("input.txt");
    ofstream cout("output.txt");

    cin.tie(NULL);
    cout.tie(NULL);

    unsigned long long X, Y;
    cin>>X>>Y;

    unsigned long long X_copy = X,
                       Y_copy = Y;

    while (X_copy != 0 && Y_copy != 0)
    {
        if (X_copy > Y_copy)
            X_copy %= Y_copy;
        else
            Y_copy %= X_copy;
    }

    cout<<(X_copy + Y_copy)<<" "<<((X * Y) / (X_copy + Y_copy));

    return 0;
}
