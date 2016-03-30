#include <stdio.h>

struct Point
{
    Point(int xx, int yy) : x(xx), y(yy) {}
    Point() : x(0), y(0) {}

    int x;
    int y;
};

const int MAX_SIZE = 40;

int N;
char m[MAX_SIZE][MAX_SIZE];

Point todo[MAX_SIZE*MAX_SIZE];
int todoRead;
int todoWrite;

Point path[MAX_SIZE][MAX_SIZE];
bool visited[MAX_SIZE][MAX_SIZE];

void addTask(const Point& c, const Point& p)
{
    if (c.x < 0 || c.x >= N || c.y < 0 || c.y >= N)
        return;

    if (m[c.y][c.x] == 'O')
        return;

    if (visited[c.y][c.x])
        return;

    visited[c.y][c.x] = true;
    path[c.y][c.x] = p;
    todo[todoWrite++] = c;
}

int main()
{
    scanf("%d ", &N);

    Point start;
    Point end;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            scanf("%c ", &m[i][j]);

            if (m[i][j] == '@')
                start = Point(j, i);

            if (m[i][j] == 'X')
                end = Point(j, i);
        }
    }

    addTask(start, Point(-1, -1));

    while (todoRead < todoWrite && !visited[end.y][end.x])
    {
        Point c = todo[todoRead++];

        addTask(Point(c.x+1, c.y), c);
        addTask(Point(c.x-1, c.y), c);
        addTask(Point(c.x, c.y+1), c);
        addTask(Point(c.x, c.y-1), c);
    }

    if (!visited[end.y][end.x])
    {
        printf("N\n");
    }
    else
    {
        printf("Y\n");
        
        Point c = end;
        while (c.x != -1)
        {
            m[c.y][c.x] = '+';            
            c = path[c.y][c.x];
        }

        m[start.y][start.x] = '@';            

        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
                printf("%c", m[i][j]);
            printf("\n");
        }
    }

    return 0;
}
