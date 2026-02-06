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

//归并排序
//先划分,再分治,比较合并
void merge_sort(int *a,int *b,int left,int right,int mid)//合并排序
{
    int i=left,j=left;
    int k=mid+1;
    while(i!=mid+1&&k!=right+1)
    {
        if(a[i]>a[k])//从左右序列的首位数据开始比较,将小的放入中间数组b,依次进行
        b[j++]=a[k++];
        else
        b[j++]=a[i++];
    }
    while(i!=mid+1) //遍历左序列剩下的
    b[j++]=a[i++];
    while(k!=right+1)//遍历右序列剩下的
    b[j++]=a[k++];
    for(int l=left;l<=right;l++)//赋值到a数组
    a[l]=b[l];
}
void merge_partition(int *a,int *b,int left,int right)//递归划分
{
    int mid=(right+left)/2; 
    if(left<right)
    {        
        merge_partition(a,b,left,mid);//左边划分
        merge_partition(a,b,mid+1,right);//右边划分
        merge_sort(a,b,left,right,mid);//排序合并
    }
}

int main()
{
    clock_t time_start,time_end;
    int num[7]={10,100,1000,10000,100000,1000000,10000000};
    double cost_time[20];
    double average_time=0;
    cout<<"merge sort:"<<endl<<endl;
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
                merge_partition(a,b,0,num[i]-1); 
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