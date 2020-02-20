#include<stdio.h>
#include<stdlib.h>
#include<algorithm>
#include<iostream>
#include<cstring>
using namespace std;
const int N=200005;
int main()
{
	int T;
	scanf("%d",&T);
	while (T--)
	{
		string str;
		int n,temp=0;
		int seq[N];
		cin>>n>>str;
		for (int i=n-2;i>=0;)
		{
			int j=i,k;
			while (j>=0 && str[j]=='<') j--;
			k=j-1;
			for (j;j<=i;j++) seq[j+1]=++temp;
			i=k;
		}
		if (temp!=n) seq[0]=++temp;
		for (int i=0;i<n;i++) cout<<seq[i]<<" ";cout<<endl;
		temp=n;
		for (int i=n-2;i>=0;)
		{
			int j=i,k;
			while (j>=0 && str[j]=='>') j--;
			k=j-1;
			for (j;j<=i;j++) seq[j+1]=temp--;
			i=k;
		}
		if (temp!=0) seq[0]=1; 
		for (int i=0;i<n;i++) cout<<seq[i]<<" ";cout<<endl;
	}
	return 0;
} 
