#include<stdio.h>
#include<stdlib.h>
#include<algorithm>
#include<iostream>
#include<cstring>
using namespace std;
const int N=100;
bool IfPalindrome(string s1,string s2,int m)
{
	for (int i=0;i<m;i++)
		if (s1[i]!=s2[m-1-i]) return false;
	return true;
}
int main()
{
	string str[N],Str="";
	int use[N];
	int seq[N];
	int n,m,num=0,pos=-1;
	memset(use,0,sizeof(use));
	scanf("%d%d",&n,&m);
	for (int i=0;i<n;i++) cin>>str[i];
	for (int i=0;i<n;i++)
		for (int j=i+1;j<n;j++)
			if (use[i]==0 && use[j]==0 && IfPalindrome(str[i],str[j],m)) use[i]=use[j]=1,j=n,num+=2,Str+=str[i];
	for (int i=0;i<n;i++)
		if (use[i]==0 && IfPalindrome(str[i],str[i],m)) use[i]=2,num+=1,pos=i,i=n;
	cout<<num*m<<endl;
	cout<<Str;
	if (pos!=-1) cout<<str[pos];
	reverse(Str.begin(),Str.end());
	cout<<Str<<endl;
	return 0;
} 
