#include<stdio.h>

int N, M, X, Y, L;

const int MSIZE = 50;

int m[MSIZE][MSIZE];
bool visited[MSIZE][MSIZE];

const int UP = 1;
const int DOWN = 2;
const int LEFT = 4;
const int RIGHT = 8;

const int SEG[] = 
{
    0, 
    UP|DOWN|LEFT|RIGHT,
    UP|DOWN,
    LEFT|RIGHT,
    UP|RIGHT,
    DOWN|RIGHT,
    DOWN|LEFT,
    UP|LEFT
};

struct Task
{
    Task(int xx, int yy, int ll)
    {
        x = xx;
        y = yy;
        l = ll;
    }

    Task()
    {
        x = 0;
        y = 0;
        l = 0;
    }

    int x;
    int y;
    int l;
};

Task tasks[MSIZE*MSIZE];
int tasksReadPtr;
int tasksWritePtr;

void addTask(int x, int y, int l, int mask)
{
    if (x < 0 || x >= M || y < 0 || y >= N)
        return;

    if (l > L)
        return;

    if (visited[y][x])
        return;

    if ((m[y][x] & mask) == 0)
        return;

    tasks[tasksWritePtr++] = Task(x, y, l);
    visited[y][x] = true;
}

int main()
{
    scanf("%d %d ", &N, &M);
    scanf("%d %d ", &Y, &X);
    scanf("%d ", &L);

    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
        {
            char c;
            scanf("%c ", &c);
            m[i][j] = SEG[c - '0'];
        }
        
    addTask(X, Y, 1, UP|DOWN|LEFT|RIGHT);

    int result = 0;
    while (tasksWritePtr != tasksReadPtr)
    {
        Task t = tasks[tasksReadPtr++];
        result++;
        
        int segType = m[t.y][t.x];

        if ((segType & UP) != 0)
            addTask(t.x, t.y-1, t.l+1, DOWN);
        if ((segType & DOWN) != 0)
            addTask(t.x, t.y+1, t.l+1, UP);
        if ((segType & LEFT) != 0)
            addTask(t.x-1, t.y, t.l+1, RIGHT);
        if ((segType & RIGHT) != 0)
            addTask(t.x+1, t.y, t.l+1, LEFT);
    }

    printf("%d\n", result);
    /*
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            printf("%x ", m[i][j]);
        }
        printf("\n");
    }*/

    return 0;
}