#include<iostream>
#include<algorithm>
#include<ctime>
#include<cmath>
#include<random>
using namespace std;

int **memory;

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
        /*
        二分搜索替代线性搜索
        不是用二分查找寻找楼层,而是用二分搜索,利用函数性质找到结果
        k,n不变时superEggDrop(k,n-i)随i增加递减
        superEggDrop(k-1,i-1)随i增加递增
        所以根据函数图像,当两者相等时,其交点即为所求结果
        */
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

int  main()
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
    cout<<"At least as many times as needed: "<<dichotomy(k,n)<<endl;
    system("pause");
}