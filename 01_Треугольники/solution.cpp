#include <stdio.h>

const int MSIZE = 500;

int N, M;
int m[MSIZE][MSIZE];
int block[4][7];
int bx0, bx1, by0, by1;

int triangles[4][3][2] = 
{
    {{0,1}, {1,0}, {1,1}},
    {{0,0}, {0,1}, {1,1}},
    {{0,0}, {1,0}, {1,1}},
    {{0,0}, {0,1}, {1,0}},
};

bool isTriange(int x, int y, int t)
{
    for (int i = 0; i < 3; i++)
        if (block[y+triangles[t][i][1]][x+triangles[t][i][0]] != 1)
            return false;

    return true;
}

void removeTriange(int x, int y, int t)
{
    for (int i = 0; i < 3; i++)
        block[y+triangles[t][i][1]][x+triangles[t][i][0]] = 0;
}

void addTriange(int x, int y, int t)
{
    for (int i = 0; i < 3; i++)
        block[y+triangles[t][i][1]][x+triangles[t][i][0]] = 1;
}

int dfs(int x, int y, int bx, int by)
{
    if (x < 0 || x >= M || y < 0 || y >= N)
        return 0;

    if (m[y][x] == 0)
        return 0;

    m[y][x] = 0;
    block[by][bx] = 1;

    if (bx < bx0)
        bx0 = bx;
    if (bx > bx1)
        bx1 = bx;
    if (by < by0)
        by0 = by;
    if (by > by1)
        by1 = by;

    int result = 1;
    result += dfs(x+1, y, bx+1, by);
    result += dfs(x-1, y, bx-1, by);
    result += dfs(x, y+1, bx, by+1);
    result += dfs(x, y-1, bx, by-1);

    return result;
}

int result[4];
bool findTriangles(int size)
{
    for (int i = by0; i < by1; i++)
        for (int j = bx0; j < bx1; j++)
            for (int t = 0; t < 4; t++)
                if (isTriange(j, i, t))
                {
                    removeTriange(j, i, t);
                    result[t]++;
                    size -= 3;

                    if (size == 0)
                        return true;
                    else if (findTriangles(size))
                        return true;

                    addTriange(j, i, t);
                    result[t]--;
                    size += 3;
                }

    return false;
}

void removeBlock(int x, int y)
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 7; j++)
            block[i][j] = 0;

    bx0 = 6;
    bx1 = 0;
    by0 = 3;
    by1 = 0;

    int size = dfs(x, y, 3, 0);

    findTriangles(size);

    /*
    printf("%d\n", size);
    for (int i = by0; i <= by1; i++)
    {
        for (int j = bx0; j <= bx1; j++)
            printf("%d", block[i][j]);
        printf("\n");
    }*/
}

int main()
{
    scanf("%d %d ", &N, &M);

    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
        {
            char c;
            scanf("%c ", &c);
            m[i][j] = c == '*' ? 1 : 0;
        }

    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            if (m[i][j] == 1)
                removeBlock(j, i);
/*
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
            printf("%d", m[i][j]);
        printf("\n");
    }*/

    printf("%d %d %d %d\n", result[0], result[1], result[2], result[3]);
    return 0;
}
