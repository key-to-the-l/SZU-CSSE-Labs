//dp[k][m]+空间优化
#include<iostream>
#include<algorithm>
#include<ctime>
#include<cmath>
#include<random>
using namespace std;

int start;
int *memory;   //备忘录存储已经计算过的情况，避免重复

int SuperEggDrop(int k,int n)   //状态:k个鸡蛋n层楼
{
    int frequency;    //次数
    for(frequency=1;;frequency++)  //最坏情况下能测试到的最高层数小于n时,省略循环条件
    {
        for(int i=k;i>0;i--)       //从i个鸡蛋遍历到k,更新数据
        {
            memory[i]=memory[i]+memory[i-1]+1;
            if(memory[i]>=n) //放在for循环中出错
            {
                return frequency;
            }
        }
        
    }
}

int main()
{
    int k,n;
    cin>>k>>n;
    memory=new int[k+1];
    for(int i=0;i<=k;i++)   //初始化备忘录
    {
        memory[i]=0;
    }
    cout<<"At least as many times as needed: "<<SuperEggDrop(k,n)<<endl;
    system("pause");
}