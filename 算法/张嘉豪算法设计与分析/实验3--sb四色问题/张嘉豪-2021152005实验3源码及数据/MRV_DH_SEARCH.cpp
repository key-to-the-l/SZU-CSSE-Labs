#include<iostream>
#include<fstream>
#include<ctime>
#include<algorithm>
using namespace std;

int matrix[10000][10000];
int color[10000];       //颜色状态
int vNum,n=50,m=4;     // n个顶点, m种颜色
int cnt=0;          //方案数
clock_t time_start,time_end; 

struct Node //点的结构体
{
    int degree;         //度数
    int id;             //原始下标
    int enableColor;    //可选颜色数
}node[1000];

void read()         //读取文件数据
{
    cout<<"START"<<endl;
    ifstream file1;
    file1.open("C:\\Users\\78047\\Desktop\\vsc\\.vscode\\Experiment3\\50_m16.txt");//50个点,4颜色
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

bool cmp(Node n1,Node n2)   //按度数降序排序
{
    return n1.degree>n2.degree;
}

bool checkNode(int num,int clr)                        //判断num点能否涂clr这种颜色,num是原下标
{
    for(int i=1;i<=n;i++)  
    {
        if(color[i]==clr&&matrix[num][i]==1)     //如果邻接矩阵的元素为1,说明两地相连
        return false;                            //如果已经有邻接点涂了这种颜色,说明不能  
    }
    return true;
}

int MRV_find()
{   
    int min=10000;
    int index=0;
    for(int i=1;i<=n;i++)        //找出可涂颜色数最少且没涂过颜色的点,返回下标
    {     
        if(node[i].enableColor<min&&color[node[i].id]==0)
        {
            min=node[i].enableColor;
            index=node[i].id;
        }
    }
    return index;
}

void MRV_DH_SEARCH(int num)     //MRV和DH剪枝优化
{
    if(num>n)           //所有点的颜色都涂完
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
    sort(node+1,node+1+n,cmp);  //DH
    int Coloring_point=MRV_find();   //找到涂色点的下标
    if(Coloring_point==0)       //找不到回溯
    {
        return;
    }
    
    for(int i=1;i<=m;i++)    //遍历不同颜色的情况
    {
        if(i==2&&num==1)    //对称优化
        break;
        int temp=0;             //记录不能涂色点的当前层数所在位置
        int flag=1;             //判断涂色后邻接点是否能继续涂色
        if(checkNode(Coloring_point,i))      
        {       
            for(int j=1;j<=n;j++)           //对邻接点的度数,可涂颜色数进行修改
            {
                if(matrix[Coloring_point][j]==1)    //j是原来的下标
                {
                    int index;              //存储邻接点现在的下标
                    for(int k=1;k<=n;k++)   
                    {
                        if(j==node[k].id)
                        {
                            index=k;
                            break;
                        }
                    }
                    node[index].degree--;   //邻接点度数--
                    if(checkNode(j,i))      //如果邻接点可以涂该颜色,则颜色--
                    {
                        node[index].enableColor--;
                        if(node[index].enableColor==0)
                        {
                            temp=j;
                            flag=0;
                            break;
                        }
                    }
                }
            }
            if(flag==0)                  //如果不能涂色,恢复度数与颜色,回溯
            {
                 for(int j=1;j<=temp;j++)
                {
                    if(matrix[Coloring_point][j]==1)
                    {
                        int index;              //存储邻接点现在的下标
                        for(int k=1;k<=n;k++)   
                        {
                            if(j==node[k].id)
                            {
                                index=k;
                                break;
                            }
                        }
                        node[index].degree++;   //邻接点度数--
                        if(checkNode(j,i))      //如果邻接点可以涂该颜色,则颜色--
                        {
                            node[index].enableColor++;
                        }
                    }
                }
                return;
            }
            else
            {
                color[Coloring_point]=i;
                MRV_DH_SEARCH(num+1);     //开始涂下一个点,即进入下一层

                color[Coloring_point]=0;         //回溯,修改的变化重置
                for(int j=1;j<=n;j++)           //对邻接点的度数,可涂颜色数进行修改
                {
                    if(matrix[Coloring_point][j]==1)
                    {
                        int index;              //存储邻接点现在的下标
                        for(int k=1;k<=n;k++)
                        {
                            if(j==node[k].id)
                            {
                                index=k;
                                break;
                            }
                        }
                        node[index].degree++;   //度数和颜色++
                        if(checkNode(j,i))      //如果邻接点可以涂该颜色,则颜色--
                        {
                            node[index].enableColor++;
                        }
                    }
                }
            }     
        }
    }
}

int main()
{
    cout<<"Map Size: "<<n<<endl;
    cout<<"Color Number: "<<m<<endl;
    cout<<endl;
    for(int i=1;i<=n;i++)     //初始化
    {
        node[i].id=i;
        color[i]=0;
        node[i].degree=0;
        node[i].enableColor=m;
        for(int j=1;j<=n;j++)
        {
            matrix[i][j]=0;
        }
    }
    read();

    for(int i=1;i<=n;i++)     //初始化
    {
        for(int j=1;j<=n;j++)
        node[i].degree+=matrix[i][j];
    }

    double cost_time; 

    time_start=clock();
    MRV_DH_SEARCH(1);
    time_end=clock();
    cost_time=(double)(time_end-time_start)*1000/CLOCKS_PER_SEC;
    
    cout<<"The verage time of the MRV_DH_SEARCH="<<cost_time<<"ms"<<endl;
    cout<<"The number of solutions: "<<cnt*m<<endl;
    system("pause");
}