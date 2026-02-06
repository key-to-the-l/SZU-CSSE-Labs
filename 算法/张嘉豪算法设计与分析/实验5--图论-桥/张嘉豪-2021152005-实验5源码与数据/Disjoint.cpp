#include<iostream>
#include<ctime>
#include<algorithm>
#include<cmath>
#include<vector>
#include<bits/stdc++.h>
using namespace std;

vector<vector<int>> Adjacency;  //邻接表
vector<vector<int>> Edge;       //边集
vector<int> visit;              //访问数组
vector<int> father;             //父亲结点,用于并查集
vector<int> spanningTree_edge;  //生成树边集
int cut1=-1,cut2=-1;            //割点1,割点2
int v,e;                        //点数,边数

void init()
{
    Adjacency.resize(v);
    visit.resize(v);
    Edge.resize(e);
    father.resize(v);
    for(int i=0;i<v;i++)        
    {
        visit[i]=0; 
        father[i]=0;
    }
}

void simple_graph()
{
    cin>>v>>e;
    Adjacency.resize(v);
    visit.resize(v);
    father.resize(v);
    Edge.resize(e);
    for(int i=0;i<v;i++)        //初始化
    {
        visit[i]=0;
        father[i]=i;    
    }
    for(int i=0;i<e;i++)
    {
        int a,b;
        cin>>a>>b;
        Adjacency[a].push_back(b),Adjacency[b].push_back(a);  //二维向量
        Edge[i].push_back(a),Edge[i].push_back(b);
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
    //cout<<v<<" "<<e<<endl;
    file1.close();
}

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

void dfs(int num)   //深度优先搜索,如果邻接,则标记为已访问过
{
    visit[num]=1;   //表示已访问
    //cout<<cut1<<" "<<cut2<<endl;
    for(int i=0;i<Adjacency[num].size();i++)    //遍历该点的邻接表
    {
        if(visit[Adjacency[num][i]]==0)
        {
            if((num!=cut1||Adjacency[num][i]!=cut2)&&(num!=cut2||Adjacency[num][i]!=cut1)) //如果遍历的边不为割边
            {
                
                dfs(Adjacency[num][i]); //继续访问
            }    
        }
    }
}

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

int disjoint_find(int x)
{
    while(father[x]!=x) //路径压缩,让父亲结点成为根节点
    {
        father[x]=father[father[x]];
        x=father[x];
    }
    return x;
}

void disjoint()     //基准法思想,用并查集求连通分量数
{
    int cnt1=cnt_origin();          //初始化
    int bridge=0;
    for(int i=0;i<e;i++)
    {    
        int cnt2=v;
        for(int i=0;i<v;i++)        //初始化
        {
            father[i]=i;    
        }
        for(int j=0;j<e;j++)
        {
            if(j==i) continue;  //跳过第i条边
            int set1=disjoint_find(Edge[j][0]);
            int set2=disjoint_find(Edge[j][1]);
            if(set1!=set2)
            {
                father[set1]=set2;
                cnt2--;         //合并
            } 
        }
        //cout<<cnt2<<" ";
        if(cnt2>cnt1)
        bridge++;
    }
    //cout<<"The number of the connected component is "<<cnt1<<endl;
    //cout<<"The number of the bridge is "<<bridge<<endl;
}

int main()
{
    clock_t time_start,time_end; 
    int point[4]={10,100,1000,10000};
    int cir[4]={100,10,5,1};
    int dence[4]={100,200,300,400};
    double cost_time;
    for(int i=0;i<4;i++)
    {
        cout<<"The number of the point is :"<<point[i]<<endl; 
        time_start=clock();
        read_dense(dence[i]);
        disjoint();
        // for(int j=0;j<cir[i];j++)
        // {
        //         //read(i+1);  //读稀疏图
        //         disjoint();
        // }
        time_end=clock();
        cost_time=(float)(time_end-time_start)*1000/CLOCKS_PER_SEC/cir[i];
        cout<<"The cost_time of the reference="<<cost_time<<"ms"<<endl;
        cout<<endl;
    }
    // time_start=clock();
    // simple_graph();
    // for(int i=0;i<100;i++)
    // {
    //     read(5);  
    //     disjoint(); 
    // }
    // time_end=clock();
    // cost_time=(double)(time_end-time_start)*1000/CLOCKS_PER_SEC;
    // cout<<"The cost_time of the disjoint="<<cost_time/100<<"ms"<<endl;
    // cout<<endl;
    system("pause");
}