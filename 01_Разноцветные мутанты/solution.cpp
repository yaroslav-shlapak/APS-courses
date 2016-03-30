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

const int MSIZE = 100000;
Heap<int, MSIZE> heap;
int table[MSIZE][2];
int tableSize;

int main()
{
    int N;
    scanf("%d ", &N);

    for (int i = 0; i < N; i++)
    {
        int c;
        scanf("%d ", &c);
        heap.push(c);
    }

    int prev = -1;
    while (heap.size() != 0)
    {
        int c = heap.pop();
        if (c != prev)
        {
            table[tableSize][0] = c;
            table[tableSize][1] = 1;
            tableSize++;
            prev = c;
        }
        else
        {
            table[tableSize-1][1]++;
        }
    }

    int K;
    scanf("%d ", &K);

    for (int i = 0; i < K; i++)
    {
        int c;
        scanf("%d ", &c);

        int l = 0;
        int r = tableSize-1;
        int result = 0;
        while (l <= r)
        {
            int m = l + (r - l) / 2;

            if (table[m][0] == c)
            {
                result = table[m][1];
                break;
            }
            else if (table[m][0] < c)
            {
                l = m + 1;
            }
            else
            {
                r = m - 1;
            }
        }
        printf("%d ", result);
    }

    return 0;
}