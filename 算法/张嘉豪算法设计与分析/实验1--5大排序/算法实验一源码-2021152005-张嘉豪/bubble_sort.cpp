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

//冒泡排序
//相邻两位数相比,将大数放在后面,每次遍历即将最大值放到末尾
void bubble_sort(int *a,int num)
{
    int temp=0;
    for(int i=0;i<num-1;i++)  //i控制排序次数,也即已排数据的数量
    {
        for(int j=0;j<num-i-1;j++)//比较到num-1-i停止
        {
            if(a[j]>a[j+1])
            {
                temp=a[j+1];
                a[j+1]=a[j];
                a[j]=temp;
            }
        }
    }
}

int main()
{
    clock_t time_start,time_end;
    int num[5]={10,100,1000,10000,100000};
    double cost_time[20];
    double average_time=0;
    cout<<"bubble sort:"<<endl<<endl;
    for(int i=0;i<5;i++)    //测试10到100000
    {
        cout<<"size="<<num[i];
        int *a=new int[num[i]];
        for(int j=0;j<20;j++)//测试20组数据的平均值
        {
            for(int k=0;k<100000/num[i];k++)//数据量小时,循环多次计时
            {                     
                random(a,num[i]);
                bubble_sort(a,num[i]); 
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