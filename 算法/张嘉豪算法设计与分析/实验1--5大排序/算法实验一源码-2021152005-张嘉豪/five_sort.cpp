#include<iostream>
#include<ctime>
#include<random>
#include <iomanip>
using namespace std;

void random(int *a,int num) //生成随机数数据
{
    //srand(time(0));     //设置随机种子保证每组测试数据都不同
    for(int i=0;i<num;i++)
    {
        a[i]=rand();
        //cout<<a[i]<<" ";
    }
    //cout<<endl;
}

//选择排序
//每次排序都找到最小的放到最前端,然后从剩下的数据中继续重复该步骤
void seletion_sort(int *a,int num)
{
    clock_t time_start=clock();
    int index=0;
    for(int i=0;i<num-1;i++)    //遍历num-1次
    {
        int min=100000;
        for(int j=i;j<num;j++)  //遍历找到最小项
        {
            if(a[j]<min)
            {
                min=a[j];
                index=j;
            } 
        }
        a[index]=a[i];
        a[i]=min;
    }

    clock_t time_end=clock();
    cout<<"seletion sort time cost: "<<endl;
    double cost_time=(float)(time_end-time_start)*1000/CLOCKS_PER_SEC;
    cout<<cost_time<<"ms"<<endl;

    // cout<<"result:"<<endl;
    // for(int i=0;i<num;i++)
    // {
    //     if(i%16==0&&i!=0)
    //     cout<<endl;
    //     cout<<a[i]<<" ";
    // }
    // cout<<endl;
}

//冒泡排序
//相邻两位数相比,将大数放在后面,每次遍历即将最大值放到末尾
void bubble_sort(int *a,int num)
{
    clock_t time_start,time_end;
    time_start=clock();
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

    time_end=clock();
    cout<<"bubble sort time cost: "<<endl;
    double cost_time=(double)(time_end-time_start)/CLOCKS_PER_SEC*1000;
    cout<<cost_time<<"ms"<<endl;

    // cout<<"result:"<<endl;
    // for(int i=0;i<num;i++)
    // {
    //     if(i%16==0&&i!=0)
    //     cout<<endl;
    //     cout<<a[i]<<" ";
    // }
    // cout<<endl;
}

//插入排序
//每次插入一个数,从后往前比较,直至插入到合适位置
void insert_sort(int *a,int num)
{
    clock_t time_start,time_end;
    time_start=clock();
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

    time_end=clock();
    cout<<"insert sort time cost: "<<endl;
    double cost_time=(double)(time_end-time_start)*1000/CLOCKS_PER_SEC;
    cout<<cost_time<<"ms"<<endl;

    //cout<<"result:"<<endl;
    // for(int i=0;i<num;i++)
    // {
    //     if(i%16==0&&i!=0)
    //     cout<<endl;
    //     cout<<a[i]<<" ";
    // }
    // cout<<endl;
}

//归并排序
//先划分,再分治,比较合并
void merge_sort(int *a,int *b,int left,int right,int mid)
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

    //cout<<"result:"<<endl;
    // for(int l=0;l<=right;l++)
    // {
    //     if(l%16==0&&l!=0)
    //     cout<<endl;
    //     cout<<a[l]<<" ";
    // }
    // cout<<endl;
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
    int num,t;
    cin>>t;
    while(t--)
    {
        cin>>num;
        int *a=new int[num]; 
        int *b=new int[num];

        random(a,num);    
        seletion_sort(a,num);

        random(a,num);
        bubble_sort(a,num);

        random(a,num);
        insert_sort(a,num); 

        clock_t time_start,time_end;
        time_start=clock();
        for(int j=0;j<(100000/num);j++)
        {
            random(a,num);
            merge_partition(a,b,0,num-1);
        }
        time_end=clock();
        cout<<"merge sort time cost: "<<endl;
        double cost_time=(double)(time_end-time_start)*1000/CLOCKS_PER_SEC/(100000/num);
        cout<<cost_time<<"ms"<<endl;  

        time_start=clock();
        for(int j=0;j<(100000/num);j++)
        {
            random(a,num);
            quick_sort(a,0,num-1);
        }
        time_end=clock();
        cout<<"quick sort time cost: "<<endl;
        cost_time=(double)(time_end-time_start)*1000/CLOCKS_PER_SEC/(100000/num);
        cout<<cost_time<<"ms"<<endl;  
        cout<<endl;
        // cout<<"result:"<<endl;
        // for(int i=0;i<num;i++)
        // {
        //     if(i%16==0&&i!=0)
        //     cout<<endl;
        //     cout<<a[i]<<" ";
        // }
        
    }
    system("pause");
}