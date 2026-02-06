#include<iostream>
#include<algorithm>
#include<ctime>
#include<cmath>
#include<random>
using namespace std;

int **memory;   //备忘录存储已经计算过的情况，避免重复

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

int main()
{
    int k,n;
    cin>>k>>n;
    memory=new int*[k+1];
    for(int i=1;i<=k;i++)   //初始化备忘录
    {
        memory[i]=new int[n+1];
    }
    for(int i=1;i<=k;i++)   
    {
        for(int j=1;j<=n;j++)
        memory[i][j]=0;
    }
    cout<<"At least as many times as needed: "<<dp_memory(k,n)<<endl;
    system("pause");
}