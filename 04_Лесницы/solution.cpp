#include <stdio.h>

template<typename T>
T min(const T& a, const T& b)
{
    return a < b ? a : b;
}

template<typename T>
T max(const T& a, const T& b)
{
    return a > b ? a : b;
}

const int MAX_SIZE = 500;
int N;

long long t[MAX_SIZE+1][MAX_SIZE+1];

void solve()
{
    scanf("%d", &N);

    long long result = 0;
    for (int i = 1; i <= N; i++)
    {
        result = 0;
        for (int j = 1; j < i; j++)
        {
            long long r = 0;
            for (int k = j + 1; k < N; k++)
                r += t[i-j][k];
            t[i][j] = r;
            result += r;
        }
        t[i][i] = 1;
    }

    printf("%lld\n", result);
}

int main()
{
    solve();
    return 0;
}
