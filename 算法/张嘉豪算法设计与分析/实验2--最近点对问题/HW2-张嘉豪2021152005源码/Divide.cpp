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
}temp[1000000];

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

double distance(Point p1,Point p2)  //计算两个点的距离
{
    double x=p1.x-p2.x;
    double y=p1.y-p2.y;
    double result=sqrt(x*x+y*y);
    return result;
}

bool cmp_x(Point p1,Point p2)       //x升序排序
{
    return p1.x<p2.x;
}
bool cmp_y(Point p1,Point p2)       //y升序排序
{
    return p1.y<p2.y;
}

double divide_merge(Point *p,int low,int high) 
{
    if (low==high)      //1个点
    return 10000000;
    if(high-low==1)     //2个点
    return distance(p[low],p[high]);
    else if(high-low==2)               //3个点
    {
        double d1=distance(p[low],p[low+1]);
        double d2=distance(p[low+1],p[low+2]);
        double d3=distance(p[low],p[low+2]);
        double temp=min(d1,d2);
        return min(d3,temp);
    }
    
    int mid=(low+high)/2;
    double left_min,right_min,d=100000; //d存放两区域最小距离中较小的一位    
    int index=0;                        //集合计数
    //Point *temp=new Point[100];       //点集合

    left_min=divide_merge(p,low,mid);        //递归求左区域最小距离
    right_min=divide_merge(p,mid+1,high);    //右区域
    if(left_min==0)
    left_min=100000;
    else if(right_min==0)
    right_min=100000;
    if(left_min!=100000&&right_min!=100000)
    d=min(left_min,right_min);          

    for(int i=low;i<=high;i++)
    {
        if(abs(p[mid].x-p[i].x)<=d)
        temp[index++]=p[i];
    }
    sort(temp,temp+index,cmp_y);  //y坐标升序排序

    for (int i=0;i<index;i++) 
    {
        for (int j=i+1;j<index&&j<i+7;j++) 
        {
            if(temp[j].y-temp[i].y>d)
            break;
            if(distance(temp[i],temp[j])!=0)
            d=min(d,distance(temp[i],temp[j]));
        }
    }
    return d;
}


int main() 
{
    clock_t time_start,time_end;
    int num[5]={100,1000,10000,100000,1000000};
    double cost_time[20];
    double average_time=0;
    cout<<"Divide Algorithm: "<<endl<<endl;
    for(int i=0;i<5;i++)
    {
        cout<<"Num="<<num[i]<<":";
        Point *p=new Point[num[i]];
        for(int j=0;j<20;j++)
        {
            time_start=clock();
            for(int k=0;k<1000000/num[i];k++)
            {
                RandomPoint(p,num[i]);
                sort(p,p+num[i],cmp_x);
                double result=divide_merge(p,0,num[i]-1);
            }
            time_end=clock();
            cost_time[j]=(double)(time_end-time_start)*1000/CLOCKS_PER_SEC/(1000000/num[i]);
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
