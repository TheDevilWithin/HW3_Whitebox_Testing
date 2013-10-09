#include <cstdlib>
#include <iostream>
#include<cstring>
using namespace std;

/*
 *
 */

int tmp = 0;
int a = 0;
int b = 0;
int cc;

typedef struct
{
    int N;
    int vexs[20]; //顶点向量
    int AdjMatrix[100][100]; //邻接矩阵
} MGraph;
bool visited[100];
int travel[40];
int total[100][100];
int good[30][40];

int numfn = 0;
int numt = 0;
int num2 = 0;

void DFS(MGraph, int);
int GetFN(MGraph q, int r);
int GetT(MGraph q, int r);
int IsIn(int s[], int size, int a);

void Init(int x)
{
    for (int i = x; i < 40; i++)
    {
        travel[i] = -1;
    }
}

int Judge(int a[])
{
    bool flag = false;
    int j = 0;
    int k = 0;
    int num = 0;
    for (int d = 0; d < 30; d++)
    {
        if (a[d] == -1)
        {
            break;
        }
        num++;
    }
    for (int i = 0; i < num; i++)
    {
        j = a[i];
        k = a[i + 1];
        if (total[j][k] == 0)
        {
            total[j][k] = 1;
            flag = true;
        }
    }
    if (flag == true)
    {
        return 1;
    }
    return -1;
}

void cp(int a[], int b[])
{
    for (int i = 0; i < 30; i++)
    {
        a[i] = b[i];
    }
}

int getsize(int d[])
{
    int i = 0;
    while (d[i] != -1)
    {
        i++;
    }
    return i;
}

void output()
{
    int tmp, j = 0;
    for (int h = cc; h > 0; h--)
    {
        j = 0;
        while (good[j][0] == 111)
        {
            j++;
        }
        tmp = getsize(good[j]);
        for (int i = j + 1; i < cc; i++)
        {
            if ((good[i][0] != 111) && (tmp > getsize(good[i])))
            {
                tmp = getsize(good[i]);
                j = i;
            }
            if ((good[i][0] != 111) && (tmp == getsize(good[i])))
            {
                for (int k = 0; k < tmp; k++)
                {
                    if (good[j][k] > good[i][k])
                    {
                        j = i;
                    }
                }
            }
        }
        int x;
        for (x = 0; x < tmp - 1; x++)
        {
            cout << good[j][x] << ",";
        }
        cout << good[j][x] << endl;
        good[j][0] = 111;
    }
}
void dfs(MGraph q,int start);
int main(int argc, char** argv)
{
    MGraph g;
    memset(g.AdjMatrix, 0, sizeof (g.AdjMatrix));
    memset(g.vexs, -1, sizeof (g.vexs));
    memset(total, 0, sizeof (total));
    memset(visited, 0, sizeof (visited));
    memset(good, -1, sizeof (good));
    memset(travel, -1, sizeof (travel));
    //Init(0);
    int start, i, j, k, num = 0;
    char s1, s2, s3, s4;
    int jn = 0;
    cin >> start;
    while (cin >> i >> s1 >> s2 >> j >> s3 >> s4)
    {
        if (i > tmp)
            tmp = i;
        if (j > tmp)
            tmp = j;
        if (s4 == 'F')
            k = 1;
        else if (s4 == 'T')
        {
            k = 2;
            jn++;
        }
        else if (s4 == 'N')
            k = 3;
        g.AdjMatrix[i][j] = k;
        if (IsIn(g.vexs, 20, i))
            g.vexs[num++] = i;
        if (IsIn(g.vexs, 20, j))
            g.vexs[num++] = j;
    };
    g.N = num;
    cc = jn + 1;
    dfs(g,start);
    cout << "CC=" << cc << endl;
    output();
}

void dfs(MGraph q,int start)
{
    travel[numfn++] = start;
    if (GetFN(q,start) == -1 && GetT(q,start) == -1)
    {

        if (Judge(travel) == 1)
            memcpy(good[num2++],travel,sizeof(travel));
        travel[--numfn] = -1;

        return;
    }
    else
    {
        bool flag = 0;
        for (int i=0; i<numfn-1; i++)
            if (travel[i] == start)
            {
                flag = 1;
                break;
            }
        if (flag)
        {
            if (Judge(travel) == 1)
                memcpy(good[num2++],travel,sizeof(travel));
            travel[--numfn] = -1;
            return;
        }
    }
    if (GetFN(q,start)!=-1)
        dfs(q,GetFN(q,start));
    if (GetT(q,start) != -1)
        dfs(q,GetT(q,start));
    travel[--numfn] = -1;
}

int GetT(MGraph q, int r)
{
    for (int i = 0; i <= tmp + 1; i++)
    {
        if (q.AdjMatrix[r][i] == 2)
        {
            return i;
        }
    }
    return -1;
}

int GetFN(MGraph q, int r)
{
    for (int i = 0; i <= tmp + 1; i++)
    {
        if (q.AdjMatrix[r][i] == 1)
        {
            return i;
        }
        if (q.AdjMatrix[r][i] == 3)
        {
            return i;
        }
    }
    return -1;
}

int IsIn(int s[], int size, int a)
{
    for (int i = 0; i < size; i++)
    {
        if (s[i] == a)
            return i;
    }
    return -1;
}
