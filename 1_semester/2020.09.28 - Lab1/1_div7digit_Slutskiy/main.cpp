#include <stdio.h>

unsigned long long N, K;
unsigned long long pow10 (unsigned long long N)
{
    unsigned long long answer = 1;

    for (unsigned long long i = 0; i<N; i++)
    {
        answer *= 10;
    }

    return answer;
}
int main()
{
    scanf("%lld", &N);
    scanf("%lld", &K);

    K %= 7;
    N %= 6;

    N = (N == 0) ? 6 : N;

    printf("%lld", ((K * pow10(N)) / 7) % 10);
    return 0;
}
