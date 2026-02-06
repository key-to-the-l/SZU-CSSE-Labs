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

//选择排序
//每次排序都找到最小的放到最前端,然后从剩下的数据中继续重复该步骤
void seletion_sort(int *a,int num)
{
    int index=0;
    for(int i=0;i<num-1;i++)    //遍历num-1次
    {
        int min=100000;
        for(int j=i;j<num;j++)
        {
            if(a[j]<min)        //遍历找到最小项
            {
                min=a[j];
                index=j;
            } 
        }
        a[index]=a[i];
        a[i]=min;
    }
}

int main()
{
    clock_t time_start,time_end;
    int num[5]={10,100,1000,10000,100000};
    double cost_time[20];
    double average_time=0;
    cout<<"selection sort:"<<endl<<endl;
    for(int i=0;i<5;i++)    //测试10到100000
    {
        cout<<"size="<<num[i];                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                
        int *a=new int[num[i]];
        for(int j=0;j<20;j++)   //测试20组数据的平均值
        {
            time_start=clock();
            for(int k=0;k<100000/num[i];k++)//数据量小时,循环多次计时
            {                     
                random(a,num[i]);
                seletion_sort(a,num[i]); 
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