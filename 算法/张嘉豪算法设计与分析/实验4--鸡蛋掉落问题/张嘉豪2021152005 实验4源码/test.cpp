#include<iostream>
#include<algorithm>
#include<ctime>
#include<cmath>
#include<random>
#include<bits/stdc++.h>
using namespace std;

int k=100;
int f[4]={10,100,1000,10000};
int **memory;   //备忘录存储已经计算过的情况，避免重复

int SuperEggDrop(int k,int n)   //状态:k个鸡蛋n层楼
{
    int frequency;    //次数
    for(frequency=1;;frequency++)  //最坏情况下能测试到的最高层数小于n时,省略循环条件
    {
        for(int i=1;i<=k;i++)       //从i个鸡蛋遍历到k,更新数据
        {
            if(memory[i][frequency]==0&&i-1>=0&&frequency-1>=0)//防止出错
            memory[i][frequency]=memory[i][frequency-1]+memory[i-1][frequency-1]+1;
            if(memory[i][frequency]>=n) //放在for循环中出错
            {
                return frequency;
            }
        }
        
    }
}

int dichotomy(int k,int n)  //状态:k个鸡蛋n层楼
{
    if(k==1||n==1||n==0)
    return n;
    if(memory[k][n]!=0)
    return memory[k][n];
    int minCnt=n;
    int low=1,high=n;
    int mid;
    while(low<=high)    
    {
        mid=(low+high)/2;
        int temp1=dichotomy(k,n-mid);   //鸡蛋未碎的状态
        int temp2=dichotomy(k-1,mid-1); //鸡蛋碎了的状态
        if(temp2<temp1)     //没碎所需扔鸡蛋的次数较多,更新所需查找的最低层数
        {
            low=mid+1;
            minCnt=min(minCnt,temp1+1);
        }
        else                //碎了所需扔鸡蛋的次数较多,更新所需查找的最高层数
        {
            high=mid-1;
            minCnt=min(minCnt,temp2+1);
        }
    }
    memory[k][n]=minCnt;
    return minCnt;
}

int dp_memory(int k,int n)   //状态:k个鸡蛋n层楼
{
    if(k==1||n==1||n==0)
    return n;
    if(memory[k][n]!=0)
    return memory[k][n];
    int minCnt=n;
    for(int i=1;i<=n;i++)   //遍历模拟从第1层到第n层扔鸡蛋,找出其最坏情况,最后比较得到较小的次数
    {
        int temp=max(dp_memory(k-1,i-1),dp_memory(k,n-i));
        minCnt=min(minCnt,1+temp);//temp+1表示从第i层扔鸡蛋，次数+1； 
        memory[k][n]=minCnt;
    }  
    return minCnt;
}

void test_dp()
{
    clock_t time_start,time_end;
    cout<<"dp_memory"<<endl;
    for(int i=0;i<4;i++)
    {
        for(int o=0;o<=k;o++)   
        {
            for(int p=0;p<=f[i];p++)
            memory[o][p]=0;
        }
        time_start=clock();
        cout<<"At least as many times as needed: ";
        cout<<dp_memory(k,f[i])<<endl;
        time_end=clock();
        double cost_time=(double)(time_end-time_start)*1000/CLOCKS_PER_SEC;
        cout<<"dp_memory time cost: ";    
        cout<<fixed<<setprecision(4)<<cost_time<<"ms"<<endl<<endl;
    }
    cout<<endl;
}

void test_dichotomy()
{
    clock_t time_start,time_end;
    double average_time=0;
    int ans;
    cout<<"dichotomy"<<endl;
    for(int i=0;i<4;i++)
    {
        time_start=clock();
        cout<<"At least as many times as needed: ";
        for(int j=0;j<10;j++)
        {
            for(int o=0;o<=k;o++)   //初始化
            {
                for(int p=0;p<=10001;p++)
                memory[o][p]=0;
            }
            ans=dichotomy(k,f[i]);
        }
        cout<<ans<<endl;
        time_end=clock();
        double cost_time=(double)(time_end-time_start)*1000/CLOCKS_PER_SEC;
        cout<<"dichotomy time cost: ";
        cout<<cost_time/10<<"ms"<<endl<<endl;
    }
    cout<<endl;
}

void test_super()
{
    clock_t time_start,time_end;
    cout<<"dp[k][m]"<<endl;
    for(int i=0;i<4;i++)
    {
        time_start=clock();
        int ans;
        cout<<"At least as many times as needed: ";
        for(int j=0;j<10;j++)
        {
            for(int o=0;o<=k;o++)   
            {
                for(int p=0;p<=10001;p++)
                memory[o][p]=0;
            }
            ans=SuperEggDrop(k,f[i]);
        }
        cout<<ans<<endl;
        time_end=clock();
        double cost_time=(double)(time_end-time_start)*1000/CLOCKS_PER_SEC;
        cout<<"dp[k][m] time cost: ";
        cout<<cost_time/10<<"ms"<<endl<<endl;
    }
    cout<<endl;
}

int main()
{
    memory=new int*[k+1];
    for(int i=0;i<=k;i++)   //初始化备忘录
    {
        memory[i]=new int[10001];
    }
    for(int i=0;i<=k;i++)   
    {
        for(int j=0;j<=10001;j++)
        memory[i][j]=0;
    }
    test_dp();
    //test_dichotomy();
    //test_super();

    system("pause");
}