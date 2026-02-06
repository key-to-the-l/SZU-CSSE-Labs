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

//快速排序
//取最左边第一个数为基准数,从右往左找小,从左往右找大,找到后交换,直至i==j
void quick_sort(int *a,int left,int right)
{
    if(left>right)
    return;
    int i=left,j=right;
    int key=a[left];
    while(i!=j)
    {
        while(a[j]>key&&j>i)//大于时右指针左移
        j--;
        while(a[i]<=key&&j>i)//小于时左指针右移,因为从最左边开始,所以是<=
        i++;
        if(j>i)
        {
            int temp=a[j];
            a[j]=a[i];
            a[i]=temp;
        }
    }
    a[left]=a[i];//i==j时移动基准数
    a[i]=key;
    quick_sort(a,left,i-1);//基准数左序列递归排序
    quick_sort(a,i+1,right);//基准数右序列递归排序
}

int main()
{
    clock_t time_start,time_end;
    int num[7]={10,100,1000,10000,100000,1000000,10000000};
    double cost_time[20];
    double average_time=0;
    cout<<"quick sort:"<<endl<<endl;
    for(int i=0;i<7;i++)    //测试10到10000000
    {
        cout<<"size="<<num[i];
        int *a=new int[num[i]];
        int *b=new int[num[i]];
        for(int j=0;j<20;j++)//测试20组数据的平均值
        {
            time_start=clock();
            for(int k=0;k<10000000/num[i];k++)//数据量小时,循环多次计时
            {                     
                random(a,num[i]);
                quick_sort(a,0,num[i]-1); 
            }
            time_end=clock();
            //输出
            cost_time[j]=(float)(time_end-time_start)*1000/CLOCKS_PER_SEC/(10000000/num[i]);
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