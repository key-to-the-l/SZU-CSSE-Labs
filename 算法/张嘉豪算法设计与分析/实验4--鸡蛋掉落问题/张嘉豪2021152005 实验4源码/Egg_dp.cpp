#include<iostream>
#include<algorithm>
#include<ctime>
#include<cmath>
#include<random>
using namespace std;

int start;


//理解什么是至少扔鸡蛋的次数
//至少：最坏情况下搜索的最优策略(最少次数)
//n个鸡蛋，模拟从每一层开始扔鸡蛋，门槛层在最坏情况下，计算需要多少次，
//比较得到最坏情况下，所需次数最小的结果，即为最优策略

int superEggDrop_dp(int k,int n)   //状态:k个鸡蛋n层楼
{
    if(k==1||n==1||n==0)
    return n;
    int minCnt=n;
    for(int i=1;i<=n;i++)   //遍历模拟从第1层到第n层扔鸡蛋,找出其最坏情况,最后比较得到较小的次数
    {
        int temp=max(superEggDrop_dp(k-1,i-1),superEggDrop_dp(k,n-i));
        /*
        在第i层楼扔鸡蛋后,分为两种情况,鸡蛋碎与鸡蛋没碎
        鸡蛋碎了,则鸡蛋数-1,下一次搜索1至i-1层,一共i-1层
        没碎则鸡蛋数不变,下一次搜索i+1至n层,一共n-i层
        无论搜索的层数范围如何,关注需要搜索层数的大小即可
        求最坏情况扔鸡蛋的次数,选择更大的情况
        */
        minCnt=min(minCnt,1+temp);//temp+1表示从第i层扔鸡蛋，次数+1；
        
    }
    return minCnt;
}

int main()
{
    int k,n;
    cin>>k>>n;
    cout<<"At least as many times as needed: "<<superEggDrop_dp(k,n)<<endl;
    system("pause");
}   