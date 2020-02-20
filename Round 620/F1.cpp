#include<stdio.h>
#include<stdlib.h>
#include<algorithm>
#include<iostream>
#include<cstring>
#include<deque>
using namespace std;
const int N=55;
const int M=20005;
int a[N][M],rev_a[N][M],sum[N][M],rev_sum[N][M],dp[N][M],lmax[N][M],rmax[N][M];
struct Node
{
	int num;
	int pos;
	bool operator>(const Node b) const
	{
		return num>b.num || (num==b.num && pos>b.pos);
	}
};
int SecSum(int sum[N][M],int i,int j,int k,int m)
{
	if (j<0) j=0;
	if (k>m) k=m;
	return sum[i][k]-sum[i][j-1];
}
int main()
{
	memset(sum,0,sizeof(sum));
	memset(rev_sum,0,sizeof(rev_sum));
	memset(dp,0,sizeof(dp));
	int n,m,K;
	cin>>n>>m>>K;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
		{
			cin>>a[i][j];
			rev_a[i][m-j+1]=a[i][j];
		}
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
			sum[i][j]=sum[i][j-1]+a[i][j],rev_sum[i][j]=rev_sum[i][j-1]+rev_a[i][j];
	for (int i=1;i<=n;i++)
	{
		deque <Node> Q_front,Q_back;
		for (int j=1;j<=m-K+1;j++)
		{
			int UncoveredSum=SecSum(sum,i,j,j+K-1,m)+SecSum(sum,i+1,j,j+K-1,m);
			if (i==1)
			{
				dp[i][j]=UncoveredSum;
				continue;
			}
			{
				Node node;
				node.num=dp[i-1][j]-SecSum(sum,i,1,j+K-1,m);node.pos=j;
				while (!Q_front.empty() && Q_front[0].pos<=j-K) Q_front.pop_front();
				while (!Q_front.empty() && node>Q_front[Q_front.size()-1]) Q_front.pop_back();
				Q_front.push_back(node);
				dp[i][j]=max(dp[i][j],Q_front[0].num+SecSum(sum,i,1,j-1,m)+UncoveredSum);
			}
			{
				int k=m-j+1;
				int UncoveredSum=SecSum(sum,i,k-K+1,k,m)+SecSum(sum,i+1,k-K+1,k,m);
				Node node;
				node.num=dp[i-1][k-K+1]-SecSum(rev_sum,i,1,j+K-1,m);node.pos=j;
				while (!Q_back.empty() && Q_back[0].pos<=j-K) Q_back.pop_front();
				while (!Q_back.empty() && node>Q_back[Q_back.size()-1]) Q_back.pop_back();
				Q_back.push_back(node);
				dp[i][k-K+1]=max(dp[i][k-K+1],Q_back[0].num+SecSum(rev_sum,i,1,j-1,m)+UncoveredSum);
			}
			if (j>K) dp[i][j]=max(dp[i][j],lmax[i-1][j-K]+UncoveredSum);
			if (j<m-K+1) dp[i][j]=max(dp[i][j],rmax[i-1][j+K]+UncoveredSum);
		}
		for (int j=1;j<=m-K+1;j++) lmax[i][j]=max(lmax[i][j-1],dp[i][j]);
		for (int j=m-K+1;j>=1;j--) rmax[i][j]=max(rmax[i][j+1],dp[i][j]);
		//cout<<"dp["<<i<<"]: ";for (int j=1;j<=m;j++) cout<<dp[i][j]<<" ";cout<<endl;
		//cout<<"lmax["<<i<<"]: ";for (int j=1;j<=m;j++) cout<<lmax[i][j]<<" ";cout<<endl;
		//cout<<"rmax["<<i<<"]: ";for (int j=1;j<=m;j++) cout<<rmax[i][j]<<" ";cout<<endl;
	}
	//for (int i=1;i<=n;i++)
	cout<<lmax[n][m-K+1]<<endl;
	return 0;
} 
