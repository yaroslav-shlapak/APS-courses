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

int sqrti(int n)
{
    int a = 0;
    int b = n + 1;

    while (b - a > 1)
    {
        int m = (a + b) / 2;
        if (m*m > n)
            b = m;
        else
            a = m;
    }

    return a;
}

const int MAX_SIZE = 200;

void solve()
{
    int N, M;
    bool m[MAX_SIZE][MAX_SIZE];

    scanf("%d %d ", &N, &M);

    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++)
        {
            char c;
            scanf("%c ", &c);
            m[i][j] = c == '*' ? true : false;
        }

    int result = -1;
    //int rx = 0, ry = 0;
    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++)
        {
            if (!m[i][j])
                continue;

            int ysize = min(i, M-1-i);
            int xsize = min(j, N-1-j);
            int msize = min(xsize, ysize);

            int size = 0;
            while (size < msize && m[i][j+size+1] && m[i][j-size-1] &&
                   m[i+size+1][j] && m[i-size-1][j])
                size++;

            if (size < result)
                continue;

            for (int y = -size; y <= size; y++)
                for (int x = -size; x <= size; x++)
                {
                    if (!m[i+y][j+x])
                    {
                        int nsize = (int) sqrti(x*x + y*y);
                        if (nsize * nsize == x*x + y*y)
                            nsize--;
                        size = min(size, nsize);
                    }
                }

            if (size > result)
            {
                result = size;
                //rx = j;
                //ry = i;
            }
        }

    printf("%d\n", result);
    //printf("%d %d\n", rx+1, ry+1);
}

int main()
{
    solve();
    return 0;
}
