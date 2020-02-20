#include<stdio.h>
#include<stdlib.h>
#include<algorithm>
#include<iostream>
#include<cstring>
using namespace std;
const int N=105;
int main()
{
	int T;
	scanf("%d",&T);
	while (T--)
	{
		int n,m;
		int time[N]={0},t[N][2];
		bool practice=true;
		scanf("%d%d",&n,&m);
		t[0][0]=t[0][1]=m;
		for (int i=1;i<=n;i++)
		{
			scanf("%d%d%d",&time[i],&t[i][0],&t[i][1]);
			t[i][0]=max(t[i][0],t[i-1][0]-(time[i]-time[i-1]));
			t[i][1]=min(t[i][1],t[i-1][1]+(time[i]-time[i-1]));
			if (t[i][0]>t[i][1]) practice=false;
		}
		if (practice) cout<<"YES"<<endl;
		else cout<<"NO"<<endl;
	}
	return 0;
} 
