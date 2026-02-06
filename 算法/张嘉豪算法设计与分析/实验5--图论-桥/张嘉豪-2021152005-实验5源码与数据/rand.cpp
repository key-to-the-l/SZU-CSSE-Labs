#include<iostream>
#include<fstream>
#include<ctime>
#include<algorithm>
using namespace std;

struct Edge
{
    int a;
    int b;
}edge[400000];
int n=4000;      //点数,影响随机数生成范围
int matrix[10000][10000];

void random(int vNum)       //生成随机边,并改变邻接矩阵
{
    srand(time(0));
    int x,y,cnt=0;
    while(cnt!=vNum)
    {
        x=rand()%n;       //限制在[1,n]范围内
        y=rand()%n;
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
    int vNum=8000;
    ofstream ofs;
    ofs.open("0.1_sparse_graph_4000.txt",ios::out);
    random(vNum);
    sort(edge,edge+vNum,cmp);
    ofs<<n<<" "<<vNum<<endl;
    for(int i=0;i<vNum;i++)
    {
        ofs<<edge[i].a<<" "<<edge[i].b<<endl;
    }
    ofs.close();
    //system("pause");
}