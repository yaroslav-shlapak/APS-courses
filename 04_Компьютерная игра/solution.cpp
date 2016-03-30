//http://acmp.ru/index.asp?main=task&id_task=29
#include <stdio.h>

template<typename T> T abs(T t1)
{
    return t1 < 0 ? -t1 : t1;
}

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

int main()
{
    int N;
    scanf("%d ", &N);

    int p[2];
    int y[2];
    for (int i = 0; i < N; i++)
    {
        int cy;
        scanf("%d ", &cy);

        int cp;
        if (i == 0)
            cp = 0;
        else if (i == 1)
            cp = p[0] + abs(cy - y[0]);
        else
            cp = min(p[0] + abs(cy - y[0]), p[1] + 3 * abs(cy - y[1]));

        y[1] = y[0];
        y[0] = cy;

        p[1] = p[0];
        p[0] = cp;
    }

    printf("%d\n", p[0]);
    return 0;
}


