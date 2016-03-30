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

const int MSIZE = 300;

const int size = 12;

class LongInt
{
    int t[size];

public:
    LongInt(int v)
    {
        for (int i = 0; i < size; i++)
            t[i] = 0;
        t[0] = v;
    }
    
    LongInt()
    {
        for (int i = 0; i < size; i++)
            t[i] = 0;
    }

    LongInt& operator=(LongInt b)
    {
        long long temp = 0;
        for (int i = 0; i < size; i++)
            t[i] = b.t[i];

        return *this;
    }

    LongInt& operator+=(LongInt b)
    {
        long long temp = 0;
        for (int i = 0; i < size; i++)
        {
            temp += t[i] + b.t[i];
            t[i] = temp % 1000000000;
            temp = temp / 1000000000;
        }

        return *this;
    }

    void print()
    {
        int p = size - 1;
        while (t[p] == 0 && p > 0)
            p--;

        printf("%d", t[p--]);
        while (p >= 0)
        {
            printf("%09d", t[p--]);
        }
    }
};



LongInt result[MSIZE+1];

int main()
{
    int K, N;
    scanf("%d %d ", &K, &N);

    result[0] = LongInt(1);
    for (int i = 1; i <= N; i++)
    {
        LongInt r = LongInt(0);
        for (int j = max(0, i - K); j < i; j++)
        {
            r += result[j];
        }

        result[i] = r;
    }

    result[N].print();
    printf("\n");

    return 0;
}


