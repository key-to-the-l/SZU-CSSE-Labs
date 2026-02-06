#include<iostream>
#include<ctime>
#include<algorithm>
#include<bits/stdc++.h>
using namespace std;

int matrix[10000][10000];
int color[10000];
int vNum,n,m=4;     // n个顶点, m种颜色
int cnt=0;              //方案数

struct Node //点的结构体
{
    int color;
    int degree;
    int id;
}node[10000];

bool check(int num) //普通检查函数, 检查第num个顶点的颜色是否符合要求
{
    for(int i=1;i<=num;i++)  
    {
        if(matrix[i][num]==1&&color[i]==color[num])     //如果邻接矩阵的元素为1,说明两地相连
        return false;                                   //如果两地颜色相同,说明错误
    }
    return true;
}

void DFS(int num)      //未优化的DFS, 第num个点涂色
{
    if(num>n)        //所有地点的颜色都涂完
    {
        cnt++;
        return;
    }
    for(int i=1;i<=m;i++)    //遍历不同颜色的情况
    {
        if(i==2&&num==1)     //小优化, 固定第一个点的颜色, n种颜色的解的数量是对称的
        break;
        color[num]=i;       
        if(check(num))      
        {
            DFS(num+1);     //开始涂下一个点
        }
        color[num]=0;   //回溯,颜色重置
    }
}

void testDFS()      //未优化的DFS测试
{
    clock_t time_start,time_end;
    double cost_time[20];
    double average_time=0;
    for(int j=0;j<20;j++)
    {
        time_start=clock();
        DFS(1);
        time_end=clock();
        cost_time[j]=(double)(time_end-time_start)*1000/CLOCKS_PER_SEC;     //计算一个的时间
        average_time+=cost_time[j];
    }
    cout<<endl;
    cout<<"The verage time of the ordinary DFS=";
    cout<<fixed<<setprecision(5)<<average_time/20<<"ms"<<endl;
    cout<<"The number of solutions: "<<cnt/20*4<<endl;
}

bool checkNode(int num) //结构体点检查函数
{
    for(int i=1;i<=num;i++)  
    {
        if(matrix[node[i].id][node[num].id]==1&&node[node[i].id].color==node[node[num].id].color)     //如果邻接矩阵的元素为1,说明两地相连
        return false;                                   //如果两地颜色相同,说明错误
    }
    return true;
}

void Greed(int num)     //贪心剪枝优化
{
    if(num>n)        //所有地点的颜色都涂完
    {
        cnt++;
        return;
    }
    for(int i=1;i<=m;i++)    //遍历不同颜色的情况
    {
        node[node[num].id].color=i;       
        if(checkNode(num))      
        {
            Greed(num+1);     //开始涂下一个点
        }
        node[node[num].id].color=0;   //回溯,颜色重置
    }
}

void testGreed()        //贪心优化测试
{
    clock_t time_start,time_end;
    double cost_time[20];
    double average_time=0;
    for(int j=0;j<20;j++)
    {
        time_start=clock();
        Greed(1);
        time_end=clock();
        cost_time[j]=(double)(time_end-time_start)*1000/CLOCKS_PER_SEC;     //计算一个的时间
        average_time+=cost_time[j];
    }
    cout<<endl;
    cout<<"The verage time of the greedy DFS="<<average_time/20<<"ms"<<endl;
    cout<<"The number of solutions: "<<cnt/20<<endl;
}

void MRV_DFS(int num)
{
    if(num>n)        //所有地点的颜色都涂完
    {
        cnt++;
        return;
    }
    for(int i=1;i<=m;i++)    //遍历不同颜色的情况
    {
        node[node[num].id].color=i;       
        if(checkNode(num))      
        {
            Greed(num+1);     //开始涂下一个点
        }
        node[node[num].id].color=0;   //回溯,颜色重置
    }
}   

void input1()       //输入方式1, 边数输入
{
    cin>>n>>vNum;
    for(int i=1;i<=vNum;i++)
    {
        int a,b;
        cin>>a>>b;
        matrix[a][b]=matrix[b][a]=1;
        node[a].degree+=1;
    }
}

void input2()       //输入方式2, 邻接矩阵输入
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            cin>>matrix[i][j];
            node[i].degree+=matrix[i][j];
        }
    }     
}

bool cmp(Node n1,Node n2)   //按度数降序排序
{
    return n1.degree>n2.degree;
}

int main()
{
    /*邻接矩阵
    0 1 1 1 0 0 0 0 0
    1 0 1 1 0 0 1 0 0
    1 1 0 1 0 0 0 0 0
    1 1 1 0 1 1 1 0 0
    0 0 0 1 0 1 0 0 1
    0 0 0 1 1 0 1 1 1
    0 1 1 1 0 1 0 1 0
    0 0 0 0 0 1 1 0 1
    0 0 0 0 1 1 0 1 0
    */ 
    //input1();                 //输入点数,边数,边
    input2();               //输入点数,邻接矩阵
    for(int i=1;i<=n;i++)      //初始化
    {
        node[i].id=i;
        color[i]=0;
        node[i].color=0;
        node[i].degree=0;
    }
    cout<<endl;
    cout<<"Map Size: "<<n<<endl;
    cout<<"Color Number: "<<m<<endl;

    testDFS();      //普通DFS测试

    //cnt=0;          //贪心DFS测试
    //sort(node+1,node+n+1,cmp);
    //testGreed();
    system("pause");
}