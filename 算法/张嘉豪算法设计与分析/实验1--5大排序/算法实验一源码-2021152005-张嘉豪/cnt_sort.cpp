#include<iostream>
#include<ctime>
#include<random>
using namespace std;

void random(int *a,int num) //生成随机数数据
{
    for(int i=0;i<num;i++)
    {
        a[i]=rand();
    }
}

void cnt_sort(int *a,int num)//计数排序
{
    int max=0;
    int temp=0;
    for(int i=0;i<num;i++)
    {
        if(a[i]>max)
        max=a[i];
    }
    int *cnt=new int[max+1];
    for(int i=0;i<max+1;i++)
    {
        cnt[i]=0;
    }
    for(int i=0;i<num;i++)
    {
        cnt[a[i]]++;
    }
    for(int i=0;i<=max;i++)
    {
        while(cnt[i]>0)
        {
            a[temp]=i;
            temp++;
            cnt[i]--;
        }
    }
}

int main()
{
    int num=100000000;
    int *a=new int[num];
    clock_t time_start,time_end;
    double cost_time[20];
    double average_time=0;
    cout<<"count sort:"<<endl;
    cout<<"size=100000000"<<endl;
    for(int j=0;j<20;j++)//测试20组数据的平均值
    {
        time_start=clock();
        for(int k=0;k<1;k++)//数据量小时,循环多次计时
        {                     
            random(a,num);
            cnt_sort(a,num); 
        }
        time_end=clock();
        //输出
        cost_time[j]=(double)(time_end-time_start)*1000/CLOCKS_PER_SEC;
        if(j%10==0) //输出每一次的时间
        cout<<endl;
        cout<<cost_time[j]<<"  ";
        average_time+=cost_time[j];
    }
    cout<<endl;
    cout<<"average time="<<average_time/20<<"ms";
    cout<<endl<<endl;

    // for(int i=0;i<num;i++)
    // {
    //     cout<<a[i]<<" ";
    // }
    system("pause");
}