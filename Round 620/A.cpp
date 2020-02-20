#include<stdio.h>
#include<stdlib.h>
#include<algorithm>
#include<iostream>
#include<cstring>
using namespace std;
int main()
{
	int T;
	scanf("%d",&T);
	while (T--)
	{
		int x,y,a,b;
		scanf("%d%d%d%d",&x,&y,&a,&b);
		if ((y-x)%(a+b)==0) cout<<(y-x)/(a+b)<<endl;else cout<<-1<<endl;
	}
	return 0;
} 
