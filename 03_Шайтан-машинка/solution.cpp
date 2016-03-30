#include <stdio.h>

const int MAX_SIZE = 10000;

int distance[MAX_SIZE];

int todo[MAX_SIZE];
int todoReadPos = 0;
int todoWritePos = 0;

int N, M;

void addTask(int x, int d)
{
    if (x < 0 || x > 9999)
        return;

    if (distance[x])
        return;

    todo[todoWritePos++] = x;
    distance[x] = d;
}

int main()
{
    int a, b;
    scanf("%d %d ", &a, &b);

    addTask(a, 1);

    while (todoReadPos < todoWritePos && distance[b] == 0)
    {
        int c = todo[todoReadPos++];
        int d = distance[c] + 1;

        addTask(c * 3, d);
        addTask(c - 2, d);

        int s = c % 10 + c / 10 % 10 + c / 100 % 10 + c / 1000 % 10;
        addTask(c + s, d);
    }

    printf("%d\n", distance[b] - 1);
    return 0;
}
