#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e7 + 5;
#pragma comment(linker, "/STACK:1024000000000,1024000000000")
//#pragma comment(linker, "/STACK:10737418240000000000000")
#pragma GCC optimize(3)

int n, m, cnt=0, ans=0;
int head[MAXN], dfn[MAXN], low[MAXN], fa[MAXN], vis[MAXN];
struct Edge
{
    public:
    int to, nxt;
} e[MAXN];

void addEdge(int u, int v)
{
    e[++cnt].to = v;
    e[cnt].nxt = head[u];
    head[u] = cnt;
}

void read(int flag) // 读取文件数据
{
    cout << "START" << endl;
    ifstream file1;
    switch (flag)
    {
        case 1:
            file1.open("C:\\Users\\78047\\Desktop\\vsc\\.vscode\\Experiment5\\sparse_graph_10.txt");
            break;
        case 2:
            file1.open("C:\\Users\\78047\\Desktop\\vsc\\.vscode\\Experiment5\\sparse_graph_100.txt");
            break;
        case 3:
            file1.open("C:\\Users\\78047\\Desktop\\vsc\\.vscode\\Experiment5\\sparse_graph_1000.txt");
            break;
        case 4:
            file1.open("C:\\Users\\78047\\Desktop\\vsc\\.vscode\\Experiment5\\sparse_graph_10000.txt");
            break;
        case 5:
            file1.open("C:\\Users\\78047\\Desktop\\vsc\\.vscode\\Experiment5\\mediumDG.txt");
            break;
        case 6:
            file1.open("C:\\Users\\78047\\Desktop\\vsc\\.vscode\\Experiment5\\largeG.txt");
            break;
        default:
            break;
    }
    if (!file1.is_open())
        cout << "Error!" << endl;
    int temp=0;
    int cnt=0;
    string str;
    while (getline(file1,str))
    {
        int ifTwo=1;
        int a=0,b=0,i;
        for(i=0;i<str.length();i++)
        {
            while(isdigit(str[i]))      //找到第一个数,开始读,置ifTWO为2
            {
                ifTwo=2;
                a=a*10+str[i++]-'0';    
            }
            if(ifTwo==2)                //读完后,循环结束开始读下一个数
            break;
        }
        
        i++;    //停止的时候,i++即为第二个数字开头的位置
        for(i;i<str.length();i++)       //读下一个数
        {
            while(isdigit(str[i]))
            {
                b=b*10+str[i++]-'0';
            }
        }
        if(temp==0)     //特判读入边数和点数
        {
            n=a;
            m=b;
            temp=1;
        }
        else
        {
            for (int i = 1; i <= m; i++)
            {

                addEdge(a, b);
                addEdge(b, a);
            }
        }
    }
    //cout<<v<<" "<<e<<endl;
    file1.close();
}

void tarjan(int u)
{
    dfn[u] = low[u] = ++cnt;
    vis[u] = 1;
    for (int i = head[u]; i; i = e[i].nxt)
    {
        int v = e[i].to;
        if (!dfn[v])
        {
            tarjan(v);
            low[u] = min(low[u], low[v]);
            if (low[v] > dfn[u])
                ans++;
        }
        else if (vis[v])
        {
            low[u] = min(low[u], dfn[v]);
        }
    }
    vis[u] = 0;
}

int find(int x)
{
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}

void merge(int x, int y)
{
    int fx = find(x), fy = find(y);
    if (fx != fy)
        fa[fx] = fy;
}

void bfs(int s)
{
    queue<int> q;
    q.push(s);
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int i = head[u]; i; i = e[i].nxt)
        {
            int v = e[i].to;
            if (find(u) != find(v))
            {
                merge(u, v);
                q.push(v);
            }
        }
    }
}

int main()
{
    //scanf("%d%d", &n, &m);
    cout<<MAXN<<endl;
    read(6);
    for (int i = 1; i <= n; i++)
        fa[i] = i;
    // for (int i = 1; i <= m; i++)
    // {
    //     int u, v;
    //     scanf("%d%d", &u, &v);
    //     addEdge(u, v);
    //     addEdge(v, u);
    // }
    for (int i = 1; i <= n; i++)
    {
        if (!dfn[i])
            tarjan(i);
    }
    for (int i = 1; i <= n; i++)
    {
        if (find(i) == i)
        {
            bfs(i);
            ans++;
        }
    }
    printf("%d\n", ans-1);
    system("pause");
}