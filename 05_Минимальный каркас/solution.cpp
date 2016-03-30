#include <stdio.h>

template<typename T>
void swap(T& t1, T& t2)
{
    T temp = t1;
    t1 = t2;
    t2 = temp;
}

template<typename T, int MSIZE>
class Heap
{
    T m_data[MSIZE];
    int m_size;

public:
    Heap() : m_size(0) {}

    void push(const T& newData)
    {
        m_data[m_size++] = newData;
        bubbleUp(m_size-1);
    }

    T pop()
    {
        T temp = m_data[0];
        m_data[0] = m_data[--m_size];

        bubbleDown(0);
        return temp;
    }

    int size()
    {
        return m_size;
    }

private:
    void bubbleUp(int c)
    {
        if (c == 0)
            return;

        int p = (c - 1) / 2;
        if (m_data[c] < m_data[p])
        {
            swap(m_data[c], m_data[p]);
            bubbleUp(p);
        }
    }

    void bubbleDown(int c)
    {
        int l = c * 2 + 1;
        int r = c * 2 + 2;

        int m = c;
        if (l < m_size && m_data[l] < m_data[m])
            m = l;
        if (r < m_size && m_data[r] < m_data[m])
            m = r;

        if (m != c)
        {
            swap(m_data[c], m_data[m]);
            bubbleDown(m);
        }
    }
};

template<typename T, int MSIZE>
class Queue
{
    T m_data[MSIZE];
    int m_read;
    int m_write;

public:
    Queue() : m_read(0), m_write(0) {}

    void push(const T& newData)
    {
        m_data[m_write++] = newData;
    }

    T pop()
    {
        return m_data[m_read++];
    }

    int size()
    {
        return m_write - m_read;
    }
};

template<typename T, int MSIZE>
class Stack
{
    T m_data[MSIZE];
    int m_size;

public:
    Stack() : m_size(0) {}

    void push(const T& newData)
    {
        m_data[m_size++] = newData;
    }

    T pop()
    {
        return m_data[--m_size];
    }

    int size()
    {
        return m_size;
    }
};

struct Edge
{
    Edge() : a(0), b(0), w(0)
    {
    }

    Edge(int aa, int bb, int ww) : a(aa), b(bb), w(ww)
    {
    }

    int a;
    int b;
    int w;

    bool operator<(const Edge& edge) const
    {
        if (a < edge.a)
            return true;
        else if (a == edge.a && b > edge.b)
            return true;
        else
            return false;
    }
};

struct Task
{
    Task() : a(0), w(0), p(0)
    {
    }

    Task(int aa, int ww, int pp) : a(aa), w(ww), p(pp)
    {
    }

    int a;
    int p;
    int w;

    bool operator<(const Task& task) const
    {
        if (w < task.w)
            return true;
        else
            return false;
    }
};

const int N_MAX = 20000;
const int M_MAX = 100000;

int N, M;
int A, B;
Heap<Edge, M_MAX * 2> edgesHeap;

Edge edges[M_MAX * 2];
int edgesPos[N_MAX];

Heap<Task, M_MAX * 2> tasksHeap;
Queue<Task, M_MAX * 2> tasksQueue;
Stack<Task, M_MAX * 2> tasksStack;

bool visited[N_MAX];
int dist[N_MAX];
int path[N_MAX];

int prim()
{
    tasksHeap.push(Task(0, 0, -1));

    int result = 0;
    while (tasksHeap.size() > 0)
    {
        Task c = tasksHeap.pop();

        if (visited[c.a])
            continue;

        visited[c.a] = true;
        result += c.w;
        //printf("%d %d\n", c.a, c.p);

        int p = edgesPos[c.a];
        while (p < M * 2 && edges[p].a == c.a)
        {
            if (!visited[edges[p].b])
                tasksHeap.push(Task(edges[p].b, edges[p].w, c.a));
            p++;
        }
    }

    return result;
}

int dijkstra(int a, int b)
{
    tasksHeap.push(Task(a, 0, -1));

    while (tasksHeap.size() > 0 && !visited[b])
    {
        Task c = tasksHeap.pop();
        //printf("%d %d %d\n", c.a, c.p, c.w);

        if (visited[c.a])
            continue;

        visited[c.a] = true;
        dist[c.a] = c.w;
        path[c.a] = c.p;

        int p = edgesPos[c.a];
        while (p < M * 2 && edges[p].a == c.a)
        {
            if (!visited[edges[p].b])
                tasksHeap.push(Task(edges[p].b, c.w + edges[p].w, c.a));
            p++;
        }
    }

    int c = b;
    while (c != -1)
    {
        printf("%d\n", c);
        c = path[c];
    }

    return dist[b];
}

int bfs(int a, int b)
{
    tasksQueue.push(Task(a, 0, -1));

    while (tasksQueue.size() > 0 && !visited[b])
    {
        Task c = tasksQueue.pop();
        //printf("%d %d %d\n", c.a, c.p, c.w);

        if (visited[c.a])
            continue;

        visited[c.a] = true;
        dist[c.a] = c.w;
        path[c.a] = c.p;

        int p = edgesPos[c.a];
        while (p < M * 2 && edges[p].a == c.a)
        {
            if (!visited[edges[p].b])
                tasksQueue.push(Task(edges[p].b, c.w + 1, c.a));
            p++;
        }
    }

    int c = b;
    while (c != -1)
    {
        printf("%d\n", c);
        c = path[c];
    }

    return dist[b];
}

int dfs(int a, int b)
{
    tasksStack.push(Task(a, 0, -1));

    while (tasksStack.size() > 0 && !visited[b])
    {
        Task c = tasksStack.pop();
        //printf("%d %d %d\n", c.a, c.p, c.w);

        if (visited[c.a])
            continue;

        visited[c.a] = true;
        dist[c.a] = c.w;
        path[c.a] = c.p;

        int p = edgesPos[c.a];
        while (p < M * 2 && edges[p].a == c.a)
        {
            if (!visited[edges[p].b])
                tasksStack.push(Task(edges[p].b, c.w + 1, c.a));

            p++;
        }
    }

    int c = b;
    while (c != -1)
    {
        printf("%d\n", c);
        c = path[c];
    }

    return dist[b];
}

int main()
{
    scanf("%d %d ", &N, &M);
    scanf("%d %d ", &A, &B);
    A--;
    B--;
    
    for (int i = 0; i < M; i++)
    {
        int a, b, w;
        scanf("%d %d %d ", &a, &b, &w);
        a--;
        b--;

        edgesHeap.push(Edge(a, b, w));
        edgesHeap.push(Edge(b, a, w));
    }

    int prev = -1;
    int j = 0;
    while (edgesHeap.size() > 0)
    {
        Edge c = edgesHeap.pop();
        edges[j] = c;

        if (c.a != prev)
        {
            edgesPos[c.a] = j;
            prev = c.a;
        }
        j++;
    }
    
    //printf("%d\n", prim());
    //printf("%d\n", dijkstra(A, B));
    //printf("%d\n", bfs(A, B));
    printf("%d\n", dfs(A, B));
    return 0;
}

