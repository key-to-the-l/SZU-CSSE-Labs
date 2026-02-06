#include<iostream>
#include<iomanip>
#include<ctime>
#include<algorithm>
#include<random>
#include<cmath>
using namespace std;

struct Point
{
    double x;
    double y;
};

void RandomPoint(Point *p,int num)
{
    srand(time(0));
    for(int i=0;i<num;i++)
    {
        double a,b;
        p[i].x=rand()%300000-100000;    //使数据集中在[-200000,200000]的区间内
        p[i].y=rand()%300000-100000;    //如果需要生成浮点数的话,乘上一个[0,1]区间的随机数即可
    }
}

double distance(Point p1,Point p2)
{
    double x=p1.x-p2.x;
    double y=p1.y-p2.y;
    double result=sqrt(x*x+y*y);
    return result;
}

void Brute_force(Point *p,int num)
{
    double result=10000;
    for(int i=0;i<num;i++)
    {
        for(int j=i+1;j<num;j++)
        {
            double temp=distance(p[i],p[j]); 
            if(temp<result&&temp!=0)        //等于0说明重叠
            {
                result=temp;
            }
        }
    }
}

int main()
{
    clock_t time_start,time_end;
    int num[4]={100,1000,10000,100000};
    double cost_time[20];
    double average_time=0;
    cout<<"Brute force: "<<endl<<endl;
    for(int i=0;i<4;i++)
    {
        cout<<"Num="<<num[i];
        Point *p=new Point[num[i]];
        for(int j=0;j<20;j++)
        {
            time_start=clock();
            for(int k=0;k<100000/num[i];k++)
            {
                RandomPoint(p,num[i]);
                Brute_force(p,num[i]);
            }
            time_end=clock();
            cost_time[j]=(double)(time_end-time_start)*1000/CLOCKS_PER_SEC/(100000/num[i]);
            if(j%10==0) //输出每一次的时间
            cout<<endl;
            cout<<cost_time[j]<<"  ";
            average_time+=cost_time[j];
        }
        cout<<endl;
        cout<<"average time="<<average_time/20<<"ms";
        cout<<endl<<endl;
    }
    system("pause");
}