#include <stdio.h>

const int MSIZE = 10;
bool m[MSIZE][MSIZE];

int N;
int result;

void dfs(int x, int y)
{
    if (x < 0 || x >= N || y < 0 || y >= N)
        return;

    if (!m[y][x])
        return;
    
    m[y][x] = false;
    result++;

    dfs(x+1, y);
    dfs(x-1, y);
    dfs(x, y+1);
    dfs(x, y-1);
}

int main()
{
    scanf("%d ", &N);

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
        {
            char c;
            scanf("%c ", &c);

            if (c == '.')
                m[i][j] = true;
        }

    int x, y;
    scanf("%d %d ", &y, &x);
    y--;
    x--;

    dfs(x, y);
    printf("%d\n", result);

    return 0;
}

