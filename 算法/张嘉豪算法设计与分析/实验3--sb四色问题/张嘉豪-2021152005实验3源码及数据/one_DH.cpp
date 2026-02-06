#include<iostream>
#include<fstream>
#include<ctime>
#include<algorithm>
#include<bits/stdc++.h>
using namespace std;

int matrix[10000][10000];
int color[10000];
int vNum,n=50,m=4;     // n个顶点, m种颜色
int cnt=0;          //方案数
clock_t time_start,time_end;

struct Node //点的结构体
{
    int color;      //该点颜色
    int degree;     //度数
    int id;         //原始下标
}node[10000];

void read()         //读取文件数据
{
    cout<<"START"<<endl;
    ifstream file1;
    file1.open("C:\\Users\\78047\\Desktop\\vsc\\.vscode\\Experiment3\\50_m16.txt");   //50个点,4颜色
    //file1.open("C:\\Users\\78047\\Desktop\\vsc\\.vscode\\Experiment3\\le450_5a.col");
    //file1.open("C:\\Users\\78047\\Desktop\\vsc\\.vscode\\Experiment3\\le450_15b.col");
    //file1.open("C:\\Users\\78047\\Desktop\\vsc\\.vscode\\Experiment3\\le450_25a.col");
    if(!file1.is_open())
    cout<<"Error!"<<endl;
    string str;
    bool temp=true;
    int cnt2=0;
    while (getline(file1,str))
    {
        if(temp)        //找到edge这句话的位置,然后开始读数字
        {
            if(str=="p edge 450 5714")
            {
                temp=false;
            }
            continue;        
        }
        int a=0,b=0,ifTwo=1;
        int i;
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
        matrix[a][b]=matrix[b][a]=1;
    } 
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            node[i].degree+=matrix[i][j];
        }
    }
    //cout<<node[1].degree<<" "<<node[2].degree<<endl;
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

bool checkNode(int num) //结构体点检查函数
{
    for(int i=1;i<=num;i++)  
    {
        if(matrix[node[i].id][node[num].id]==1&&node[node[i].id].color==node[node[num].id].color)     //如果邻接矩阵的元素为1,说明两地相连
        return false;                                   //如果两地颜色相同,说明错误
    }
    return true;
}

void one_DH(int num)     //贪心剪枝优化
{
    if(num>n)        //所有地点的颜色都涂完
    {
        cnt++;
        if(cnt==5000000)
        {
            clock_t t_temp;
            t_temp=clock();
            cout<<"Time to get the 500w solution:";
            cout<<fixed<<(t_temp-time_end)*1000/CLOCKS_PER_SEC<<"ms"<<endl;
        }
        return;
    }
    for(int i=1;i<=m;i++)    //遍历不同颜色的情况
    {
        node[node[num].id].color=i;       
        if(checkNode(num))      
        {
            one_DH(num+1);     //开始涂下一个点
        }
        node[node[num].id].color=0;   //回溯,颜色重置
    }
}

bool cmp(Node n1,Node n2)   //按度数降序排序
{
    return n1.degree>n2.degree;
}

int main()
{
    cout<<"Map Size: "<<n<<endl;
    cout<<"Color Number: "<<m<<endl;
    cout<<endl;
    for(int i;i<=n;i++)
    {
        node[i].id=i;
        color[i]=0;
        node[i].color=0;
        node[i].degree=0;
    }
    read();  
    double cost_time;
    

    sort(node+1,node+1+n,cmp);
    time_start=clock();
    one_DH(1);
    time_end=clock();
    cost_time=(double)(time_end-time_start)*1000/CLOCKS_PER_SEC;
    cout<<fixed<<setprecision(6)<<"The verage time of the one_DH="<<cost_time<<"ms"<<endl;
    cout<<"The number of solutions: "<<cnt<<endl;
    system("pause");
}