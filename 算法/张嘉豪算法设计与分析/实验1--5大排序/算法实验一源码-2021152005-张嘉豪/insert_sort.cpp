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

//插入排序
//每次插入一个数,从后往前比较,直至插入到合适位置
void insert_sort(int *a,int num)
{
    for(int i=1;i<num;i++)
    {
        int key=a[i];
        int j=i-1;
        while(j>=0&&a[j]>key)   //若小于,则j移动继续往前比
        {
            a[j+1]=a[j];
            j--;
        }
        a[j+1]=key;
    }
}

int main()
{
    clock_t time_start,time_end;
    int num[5]={10,100,1000,10000,100000};
    double cost_time[20];
    double average_time=0;
    cout<<"insert sort:"<<endl<<endl;
    for(int i=0;i<5;i++)    //测试10到100000
    {
        cout<<"size="<<num[i];
        int *a=new int[num[i]];
        int *b=new int[num[i]];
        for(int j=0;j<20;j++)//测试20组数据的平均值
        {
            time_start=clock();
            for(int k=0;k<100000/num[i];k++)//数据量小时,循环多次计时
            {                     
                random(a,num[i]);
                insert_sort(a,num[i]); 
            }
            time_end=clock();
            //输出
            cost_time[j]=(float)(time_end-time_start)*1000/CLOCKS_PER_SEC/(100000/num[i]);
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