#include <stdio.h>

const int MSIZE = 50;

int N, K, A, B, D;

int m[MSIZE][MSIZE];
bool visited[MSIZE];
int result;

void dfs(int a, int d)
{
    if (visited[a])
        return;

    if (a == B && d <= D)
    {
        result++;
        return;
    }

    if (d == D)
        return;

    visited[a] = true;

    for (int i = 1; i <= m[a][0]; i++)
        dfs(m[a][i], d + 1);

    visited[a] = false;
}

int main()
{
    scanf("%d %d ", &N, &K);
    scanf("%d %d ", &A, &B);
    scanf("%d ", &D);

    A--;
    B--;

    for (int i = 0; i < K; i++)
    {
        int a, b;
        scanf("%d %d ", &a, &b);
        a--;
        b--;

        m[a][0]++;
        int p = m[a][0];
        m[a][p] = b;
    }

    dfs(A, 0);
    printf("%d", result);
}

