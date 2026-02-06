#include<iostream>
#include<fstream>
#include<ctime>
#include<algorithm>
using namespace std;

struct Edge
{
    int a;
    int b;
}edge[1000];
int n=200;      //点数,影响随机数生成范围
int matrix[1000][1000];

void random(int vNum)       //生成随机边,并改变邻接矩阵
{
    srand(time(0));
    int x,y,cnt=0;
    while(cnt!=vNum)
    {
        x=rand()%n+1;       //限制在[1,n]范围内
        y=rand()%n+1;
        if(x<y&&matrix[x][y]!=1)    //不重复
        {
            edge[cnt].a=x;
            edge[cnt].b=y;
            matrix[x][y]=1;
            cnt++;
        }  
    } 
}

bool cmp(Edge e1,Edge e2)
{
    if(e1.a==e2.a)
    return e1.b<e2.b;
    return e1.a<e2.a;
}

int main()
{
    int vNum=900;
    ofstream ofs;
    ofs.open("200p_900e_4a.txt",ios::out);
    random(vNum);
    sort(edge,edge+vNum,cmp);
    ofs<<"p edge 450 5714"<<endl;
    for(int i=0;i<vNum;i++)
    {
        ofs<<edge[i].a<<" "<<edge[i].b<<endl;
    }
    ofs.close();
    //system("pause");
}