#include <iostream>
#include <fstream>
#include <ctime>
#include <algorithm>
#include <cmath>
#include <vector>
#include <unordered_set>
using namespace std;

//#pragma comment(linker, "/STACK:10240000000,10240000000")
//#pragma comment(linker, "/STACK:10737418240000000000000")
//#pragma GCC optimize(3)

vector<vector<int>> Adjacency; // 邻接表
vector<vector<int>> Edge;      // 边集
vector<int> visit;             // 访问数组
vector<int> father;            // 父亲结点,并查集
vector<int> depth;             // 深度
vector<int> Tree;              // 最近公共祖先

int cut1 = -1, cut2 = -1; // 割点1,割点2
int v, e;                 // 点数,边数
int tree_edge;
int bridge = 0;

struct Hash_edge
{
    size_t operator()(const vector<int> vv) const
    {
        // int temp1=(v1[0]<v1[1])?(v1[0]):(v1[1]);
        // int temp2=(v1[0]>v1[1])?(v1[0]):(v1[1]);
        int temp1, temp2;
        if (vv[0] < vv[1])
        {
            temp1 = vv[0];
            temp2 = vv[1];
        }
        else if (vv[0] > vv[1])
        {
            temp1 = vv[1];
            temp2 = vv[0];
        }
        return temp2 + temp1 * 66;
    }
};

struct edge_equal
{
    bool operator()(const vector<int> v1, vector<int> v2) const
    {
        if ((v1[0] == v2[0] && v1[1] == v2[1]) || (v1[1] == v2[0] && v1[0] == v2[1]))
            return true;
        return false;
    }
};

// 初始化全局变量
void init()
{
    Adjacency.resize(v);
    visit.resize(v);
    father.resize(v);
    Tree.resize(v);
    depth.resize(v);
    Edge.resize(e);
    for (int i = 0; i < v; i++)
    {
        visit[i] = 0;
        depth[i] = 0;
        Tree[i] = -1;
        father[i] = i;
    }
}

void read(int flag) // 读取文件数据
{
    //cout << "START" << endl;
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
            v=a;
            e=b;
            temp=1;
            init();
        }
        else
        {
            Adjacency[a].push_back(b), Adjacency[b].push_back(a); // 二维向量
            Edge[cnt].push_back(a), Edge[cnt].push_back(b);       //计数读入边
            cnt++;
        }
    }
   // cout<<v<<" "<<e<<endl;
    file1.close();
}

//随机生成稀疏图并读取
void read_sparse(int v1,int e1)
{
    v=v1,e=e1;
    
    init();
    unordered_set<vector<int>, Hash_edge, edge_equal> re_edge;//去重边哈希表
    for(int i=0;i<e;i++)
    {
        int vex1=rand()%v;
        int vex2=rand()%v;
        vector<int> ed{vex1,vex2};
        if(re_edge.find(ed)==re_edge.end()&&vex1!=vex2)
        {
            re_edge.insert(ed);
        }
        else    //如果是重边就再生成一条
        {
            i--;
            continue;
        }
        Adjacency[vex1].push_back(vex2);
        Adjacency[vex2].push_back(vex1);
        Edge.push_back(vector<int>{vex1,vex2});
    }
} 

//生成稠密图并读取
void read_dense(int v1)
{
    v=v1;
    e=(v1*(v1-1))/2;
    int cnt;
    init();
    for(int i=0;i<v;i++)
    {
        for(int j=i+1;j<v;j++)
        {
            Adjacency[i].push_back(j);
            Adjacency[j].push_back(i);
            Edge[cnt].push_back(i), Edge[cnt].push_back(j);       //计数读入边
            cnt++;
        }      
    }
} 

// 输入简单图
void simple_graph()
{
    cin >> v >> e;
    init();
    for (int i = 0; i < e; i++)
    {
        int a, b;
        cin >> a >> b;
        Adjacency[a].push_back(b), Adjacency[b].push_back(a); // 二维向量
        Edge[i].push_back(a), Edge[i].push_back(b);
    }
}

void dfs(int num, int d, int f, int root) // 深度优先搜索,如果邻接,则标记为已访问过
{
    visit[num] = 1; // 表示已访问
    depth[num] = d;
    father[num] = f;
    for (int i = 0; i < Adjacency[num].size(); i++) // 遍历该点的邻接表
    {
        if (visit[Adjacency[num][i]] == 0)
        {
            tree_edge++;
            dfs(Adjacency[num][i], d + 1, num, root);
        }
    }
}

void forest()
{
    for (int i = 0; i < v; i++)
    {
        if (visit[i] == 0)
            dfs(i, 0, i, i);
    }
}

void path_compression(int v1, int v2)
{
    if (father[v1] == v2) // 父亲结点时最近公共祖先
        return;
    else
    {
        int temp1 = v1;
        v1 = father[v1];
        father[temp1] = v2;       // v1的父亲结点设置为v2
        path_compression(v1, v2); // 递归压缩
    }
}

void lca(int v1, int v2)
{
    if (father[v1] == v2 || father[v2] == v1)
        return;
    int temp1 = v1;
    int temp2 = v2;
    while (true)
    {
        if (depth[v1] > depth[v2])
        {
            Tree[v1] = 0;
            v1 = father[v1];
        }
        else if (depth[v1] < depth[v2])
        {
            Tree[v2] = 0;
            v2 = father[v2];
        }
        else
        {
            if (v1 != v2)
            {
                Tree[v1] = 0;
                Tree[v2] = 0;
                v1 = father[v1];
                v2 = father[v2];
            }
            else
                break;
        }
    }
    path_compression(temp1, v1);
    path_compression(temp2, v2);
}

void cnt_Tree()
{
    for (int i = 0; i < v; i++)
    {
        init();
        forest();
        for (int i = 0; i < Adjacency[i].size(); i++)
        {
        }
    }
}

/*
int cnt_origin()    //计算未割边之前的连通分量
{
    int cnt=0;
    for(int i=0;i<visit.size();i++)
    {
        visit[i]=0;
    }
    for(int i=0;i<v;i++)    //遍历每个点,若未访问则调用dfs
    {
        if(visit[i]==0)
        {
            dfs(i);
            cnt++;
        }
    }
    return cnt;
}
*/

int disjoint_find(int x)
{
    while (father[x] != x) // 路径压缩,让父亲结点成为根节点
    {
        father[x] = father[father[x]];
        x = father[x];
    }
    return x;
}

// edgeSet:生成树的边集
void spanningdepth(int current, int present, vector<vector<int>> &edgeSet)
{
    if (present == -1)
        return;
    edgeSet.push_back(vector<int>{present, current});
    visit[current] = 1;
    for (int i = 0; i < Adjacency[current].size(); i++)
    {
        if (visit[Adjacency[current][i]] != 1)
            spanningdepth(Adjacency[current][i], current, edgeSet);
    }
}

// 获得生成树与对应深度
void depth_relation(int current, int cu_father, int d)
{
    visit[current] = 1;
    Tree[current] = cu_father;
    depth[current] = d;
    for (int i = 0; i < Adjacency[current].size(); i++)
    {
        if (visit[Adjacency[current][i]] == 0)
            depth_relation(Adjacency[current][i], current, d + 1);
    }
}

unordered_set<vector<int>, Hash_edge, edge_equal> tree_edgeSet;
unordered_set<vector<int>, Hash_edge, edge_equal> ring_edgeSet; // 环边的边集
void disjoint_lca()                                        // 并查集+lca+路径压缩
{
    init();
    for (int i = 0; i < v; i++)
    {
        if (visit[i] == 0)
            depth_relation(i, i, 0);
    }

    for (int i = 0; i < v; i++) // 边集插入
    {
        tree_edgeSet.insert(vector<int>{Tree[i], i});
    }
    for (int i = 0; i < Edge.size(); i++)
    {
        if (tree_edgeSet.find(Edge[i]) == tree_edgeSet.end()) //重边
        {
            int temp1, temp2;
            int t1, t2;
            temp1 = Edge[i][0];
            temp2 = Edge[i][1];
            ring_edgeSet.insert(vector<int>{temp1, temp2});//emplace效率更高
            if (depth[temp2] > depth[temp1])    //令temp1为较深的结点
                swap(temp1, temp2);

            if(Tree[temp1]==Tree[temp2])    //重边里的点祖先相同
            {
                ring_edgeSet.insert(vector<int>{temp1,Tree[temp1]});
                ring_edgeSet.insert(vector<int>{temp2,Tree[temp2]});
                continue;
            }

            while (depth[temp2] < depth[temp1])
            {
                t1 = temp1;
                temp1 = Tree[temp1];
                ring_edgeSet.insert(vector<int>{t1, temp1});
            }            
            while (Tree[temp1] != Tree[temp2])
            {
                t1 = temp1;
                t2 = temp2;
                temp1 = Tree[temp1];
                temp2 = Tree[temp2];
                ring_edgeSet.insert(vector<int>{t1, temp1});
                ring_edgeSet.insert(vector<int>{t2, temp2});
            }
            int lca = Tree[temp1];
            temp1 = Edge[i][0];
            temp2 = Edge[i][1];
            while (Tree[temp1] != lca)
            {
                int dad = Tree[temp1];
                Tree[temp1] = lca;
                depth[temp1] = depth[lca] + 1;
                temp1 = dad;
            }
            while (Tree[temp2] != lca)
            {
                int dad = Tree[temp2];
                Tree[temp2] = lca;
                depth[temp2] = depth[lca] + 1;
                temp2 = dad;
            }
        }
    }
    for (int i = 0; i < e; i++)
    {
        if (ring_edgeSet.find(Edge[i]) == ring_edgeSet.end())
        {
            bridge++;
            //cout << Edge[i][0] << "---" << Edge[i][1] << " is a brigde" << endl;
        }
    }
    //cout << "The number of the bridge is " << bridge << endl;
}

int main()
{
    clock_t time_start,time_end; 
    int point[4]={10,100,1000,10000};
    int dence[4]={100,200,300,400};
    int cir[4]={1,1,1,1};
    double cost_time;
    
    for(int i=0;i<4;i++)
    {
        cout<<"The number of the point is :"<<point[i]<<endl;
       
        time_start=clock();
        read_dense(dence[i]);
        disjoint_lca();
        // for(int j=0;j<cir[i];j++)
        // {
        //         read(i+1);  //读稀疏图
        //         disjoint_lca();
        // }
        time_end=clock();
        cost_time=(float)(time_end-time_start)*1000/CLOCKS_PER_SEC/cir[i];
        cout<<"The cost_time of the reference="<<cost_time<<"ms"<<endl;
        cout<<endl;
    }
    
    // for(int i=0;i<100;i++)
    // {
    //     read(5);  
    //     disjoint_lca(); 
    // }
    // time_end=clock();
    // cost_time=(double)(time_end-time_start)*1000/CLOCKS_PER_SEC;
    // cout<<"The cost_time of the disjoint_lca="<<cost_time/100<<"ms"<<endl;
    // cout<<endl;
    system("pause");
}