#include <bits/stdc++.h>
#include <vector>
#include <iostream>
#include <cstring>
#include <queue>
#include <ctime>
using namespace std;

struct EDGE
{
    int for_point;  // 正向节点
    int capacity;   // 路径容量
    int back_point; // 反向边的节点
};

vector<EDGE> edge[100000];
int level[30000];   // 分层图
int arc[100000];    // 优化边
bool visit[100000]; // 访问数组
queue<int> q;
int a = 10, b = 10, m = 10, n = 10;     
//论文数：m，评审数：n， 论文安排数：a， 评审评阅数：b

void random() // 生成随机m,n
{
    srand(time(0));
    int x, y;
    m = rand() % 10000; // 限制在[1,10000]范围内
    n = rand() % 10000;
}

void bfs_dinic() // bfs获得分层图
{
    for (int i = 0; i < 30000; i++)
    {
        level[i] = -1;
    }
    level[0] = 0;
    q.push(0);
    while (!q.empty())
    {
        int temp = q.front(); // 头节点
        q.pop();
        for (int i = 0; i < edge[temp].size(); i++)
        {
            EDGE &e = edge[temp][i];
            if (e.capacity > 0 && level[e.for_point] == -1)
            {
                level[e.for_point] = level[temp] + 1;
                q.push(e.for_point);
            }
        }
    }
}
int dfs_dinic(int num, int ca)
{
    if (num == m + n + 1)
        return ca;
    for (int &i = arc[num]; i < edge[num].size(); ++i) // 标记避免重复
    {
        EDGE &e = edge[num][i];
        if (e.capacity > 0 && level[e.for_point] > level[num])
        {
            int temp = dfs_dinic(e.for_point, min(ca, e.capacity));
            if (temp > 0) // 更新
            {
                e.capacity -= temp;
                edge[e.for_point][e.back_point].capacity += temp;
                return temp;
            }
        }
    }
    return 0;
}

void init() // 初始化函数，建立边与节点
{
    for (int i = 1; i <= m; i++)
    {
        EDGE temp;
        temp.for_point = i;
        temp.capacity = a;
        temp.back_point = edge[i].size();
        edge[0].push_back(temp);
        temp.for_point = 0;
        temp.capacity = 0;
        temp.back_point = edge[0].size() - 1;
        edge[i].push_back(temp);
    }
    for (int i = 1; i <= m; i++)
    {
        for (int j = m + 1; j <= m + n; j++)
        {
            EDGE temp;
            temp.for_point = j;
            temp.capacity = 1;
            temp.back_point = edge[j].size();
            edge[i].push_back(temp);
            temp.for_point = i;
            temp.capacity = 0;
            temp.back_point = edge[i].size() - 1;
            edge[j].push_back(temp);
        }
    }
    for (int i = m + 1; i <= m + n; i++)
    {
        EDGE temp;
        temp.for_point = m + n + 1;
        temp.capacity = b;
        temp.back_point = edge[m + n + 1].size();
        edge[i].push_back(temp);
        temp.for_point = i, temp.capacity = 0;
        temp.back_point = edge[i].size() - 1;
        edge[m + n + 1].push_back(temp);
    }
}

int Dinic()
{
    int result = 0;
    while (1)
    {
        int bottleneck = 0;
        bfs_dinic();              // 获得分层图
        if (level[m + n + 1] < 0) // 不能连通汇点
            break;
        memset(arc, 0, sizeof(arc)); // 初始化
        while (1)                    // 寻找增广路径
        {
            bottleneck = dfs_dinic(0, 6666666); // 寻找瓶颈量
            if (!bottleneck)
                break;
            result += bottleneck;
        }
    }
    return result;
}

int dfs_ff(int num, int ca)
{
    if (num == m + n + 1)
        return ca;
    visit[num] = true;
    for (int i = 0; i < edge[num].size(); ++i)
    {
        EDGE &e = edge[num][i];
        if (!visit[e.for_point] && e.capacity > 0)
        {
            int temp = dfs_ff(e.for_point, min(ca, e.capacity)); // 寻找瓶颈量
            if (temp > 0)                                        // 更新
            {
                e.capacity -= temp;
                edge[e.for_point][e.back_point].capacity += temp;
                return temp;
            }
        }
    }
    return 0;
}

int Ford_Fulkerson()
{
    int result = 0;
    while (1) // 寻找增广路径
    {
        memset(visit, 0, sizeof(visit));
        int bottleneck = dfs_ff(0, 666666);
        if (!bottleneck)
            break;
        result += bottleneck;
    }
    return result;
}

int matrix[10100][10100]; // 邻接矩阵
int min_flow[20000];      // 最小流数组
int pre_point[20000];     // 增广路径上的前驱节点

int bfs_ek() // bfs
{
    for (int i = 0; i < 20000; i++)
    {
        pre_point[i] = -1;
    }
    min_flow[0] = 666666;
    pre_point[0] = 0;
    queue<int> q;
    q.push(0);
    while (!q.empty())
    {
        int temp = q.front();
        q.pop();
        if (temp == m + n + 1)
            break;
        for (int i = 0; i <= m + n + 1; i++)
        {
            if (i != 0 && matrix[temp][i] > 0 && pre_point[i] == -1) // 搜索未访问的邻接点
            {
                pre_point[i] = temp;                                // 记录前驱
                min_flow[i] = min(min_flow[temp], matrix[temp][i]); // 寻找瓶颈
                q.push(i);
            }
        }
    }
    if (pre_point[m + n + 1] == -1)
        return -1; // 如果与汇点不连通
    return min_flow[m + n + 1];
}

int Edmond_Karp()
{
    int bottleneck = 0;
    int result = 0;
    while (bottleneck = bfs_ek() != -1) // 寻找增广路径
    {
        int temp = m + n + 1;
        while (temp != 0) // 不断查看前驱来更新
        {
            int before = pre_point[temp];
            matrix[temp][before] += bottleneck;
            matrix[before][temp] -= bottleneck;
        }
        result += bottleneck;
    }
    return result;
}

void test_ff()
{
    clock_t time_start, time_end;
    double one_time, cost_time;
    cout << "a=" << a << ", b=" << b << ", m=" << m << ", n=" << n << endl;
    for (int i = 0; i < 20; i++)
    {
        init();
        time_start = clock();
        Ford_Fulkerson();
        time_end = clock();
        one_time = (time_end - time_start) * 1000 / CLOCKS_PER_SEC;
        //        if(i<2)
        //        cout<<fixed<<"one_time: "<<one_time<<endl;
        cost_time += one_time;
    }
    init();
    //cout << "The max min_flow = " << Ford_Fulkerson() << endl;
    cout << "The cost_time of the Ford_Fulkerson=" << cost_time / 20 << "ms" << endl;
}

void test_dinic()
{
    clock_t time_start, time_end;
    double one_time, cost_time = 0;
    cout << "a=" << a << ", b=" << b << ", m=" << m << ", n=" << n << endl;
    for (int i = 0; i < 1; i++)
    {
        init();
        time_start = clock();
        Dinic();
        time_end = clock();
        one_time = (time_end - time_start) * 1000 / CLOCKS_PER_SEC;
        //        if(i<10)
        //        capacityout<<fixed<<"one_time: "<<one_time<<endl;
        cost_time += one_time;
    }
    init();
    //cout << "The max min_flow = " << Dinic() << endl;
    cout << "The cost_time of the Dinic=" << cost_time / 1 << "ms" << endl;
}

void test_ek()
{
    clock_t time_start,time_end; 
    double one_time,cost_time=0;
    cout<<"a="<<a<<", b="<<b<<", m="<<m<<", n="<<n<<endl;
    for(int i=0;i<1;i++)
    {
        init();
        time_start=clock();
        Edmond_Karp();
        time_end=clock();
        one_time=(time_end-time_start)*1000/CLOCKS_PER_SEC;
        // if(i<10)
        // cout<<fixed<<"one_time: "<<one_time<<endl;
        cost_time+=one_time;
    }
    // init();
    // cout<<"The max min_flow = "<<Edmond_Karp()<<endl;
    cout<<"The cost_time of the Edmond_Karp="<<cost_time/1<<"ms"<<endl;
}

int main()
{
    test_ff();
    cout << endl;
    test_ek();
    cout<<endl;
    test_dinic();
    system("pause");
}