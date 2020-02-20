#include<stdio.h>
#include<stdlib.h>
#include<algorithm>
#include<iostream>
#include<cstring>
#include<vector>
#include<cmath>
#include<queue>
using namespace std;
const int N=200010;
const int M=20;
struct Edge
{
	int to;
	int next;
};
void addEdge(int *head,Edge *edge,int u,int v,int &cnt)
{
	edge[cnt].to=v;
	edge[cnt].next=head[u];
	head[u]=cnt++;
	return ;
}
void Dfs_Find_Center_Gravity(int x,int *head,Edge *edge,int n,int *ChildNum,int *visit,int &ans,int &pos)
{
	int temp;
	int cur=head[x];
	while (cur!=-1)
	{
		int to=edge[cur].to;
		if (visit[to]==0)
		{
			visit[to]=1;
			Dfs_Find_Center_Gravity(to,head,edge,n,ChildNum,visit,ans,pos);
			temp=max(temp,ChildNum[to]);
			ChildNum[x]+=ChildNum[to]+1;
		}
		cur=edge[cur].next;
	}
	temp=max(temp,n-1-ChildNum[x]);
	if (temp<ans)
	{
		ans=temp;
		pos=x;
	}
	return ;
}
int Find_Center_Gravity(int *head,Edge *edge,int n)
{
	int ans=n,pos=0;
	int ChildNum[N],visit[N];
	memset(ChildNum,0,sizeof(ChildNum));
	memset(visit,0,sizeof(visit));
	visit[1]=1;
	Dfs_Find_Center_Gravity(1,head,edge,n,ChildNum,visit,ans,pos);
	return pos;
}
void Get_Father(int *head,Edge *edge,int n,int root,int **father,int *depth)
{
	int visit[N];
	memset(visit,0,sizeof(visit));
	visit[root]=1;
	queue <int> Q;
	Q.push(root);
	while (!Q.empty())
	{
		int x=Q.front();
		Q.pop();
		int cur=head[x];
		while (cur!=-1)
		{
			int to=edge[cur].to;
			if (visit[to]==0)
			{
				visit[to]=1;
				father[to][0]=x;
				Q.push(to);
				depth[to]=depth[x]+1;
			}
			cur=edge[cur].next;
		}
	}
	for (int deep=0;(1<<deep)<n;deep++)
		for (int i=1;i<=n;i++)
			if (father[father[i][deep]][deep]!=0)
				father[i][deep+1]=father[father[i][deep]][deep];
	return ;
}
int LCA(int x,int y,int **father,int *depth)
{
	if (depth[x]>depth[y]) swap(x,y);
	int delta_depth=depth[y]-depth[x];
	int deep=0;
	while (delta_depth)
	{
		if (delta_depth%2) y=father[y][deep];
		deep++;
		delta_depth/=2;
	}
	if (x==y) return x;
	deep=(int)(log(depth[x]-1)/log(2));
	for (int i=deep;i>=0;i--)
	if (father[x][i]!=father[y][i])
	{
		x=father[x][i];
		y=father[y][i];
	}
	return father[x][0];
}
int dist(int x,int y,int **father,int *depth)
{
	int lca=LCA(x,y,father,depth);
	return depth[x]+depth[y]-2*depth[lca];
}
int main()
{
	Edge *edge=new Edge[N];
	int head[N/2];
	memset(head,-1,sizeof(head));
	int* depth=new int[N];
	int** father=new int*[N];
	for (int i=0;i<N;i++)
	{
		father[i]=new int[M];
		memset(father[i],0,M*sizeof(int));
	}
	int n,gra;
	cin>>n;int cnt=0;
	for (int i=1;i<n;i++)
	{
		int u,v;
		cin>>u>>v;
		addEdge(head,edge,u,v,cnt);
		addEdge(head,edge,v,u,cnt);
	}
	gra=Find_Center_Gravity(head,edge,n);
	//cout<<gra<<endl;
	int root=gra;
	memset(depth,0,sizeof(depth));depth[root]=1;
	Get_Father(head,edge,n,root,father,depth); 
	//for (int i=1;i<=n;i++) cout<<depth[i]<<" ";cout<<endl;
	/*for (int i=1;i<=n;i++)
	{
		int deep=0;
		while (father[i][deep]!=0) 
		{
			cout<<father[i][deep]<<" ";
			deep++;
		}
		cout<<endl;
	}*/
	int q;
	cin>>q;
	while (q--)
	{
		int x,y,a,b,K;
		cin>>x>>y>>a>>b>>K;
		int length_path_1=dist(a,b,father,depth);
		int length_path_2=dist(a,x,father,depth)+1+dist(y,b,father,depth);
		int length_path_3=dist(a,y,father,depth)+1+dist(x,b,father,depth);
		int length_circle=dist(x,y,father,depth)+1;
		//cout<<length_path_1<<" "<<length_path_2<<" "<<length_path_3<<" "<<length_circle<<endl;
		if (K%2==length_path_1%2 && K>=length_path_1)
		{
			cout<<"YES"<<endl;
			continue;
		}
		if (K%2==length_path_2%2 && K>=length_path_2)
		{
			cout<<"YES"<<endl;
			continue;
		}
		if (K%2==length_path_3%2 && K>=length_path_3)
		{
			cout<<"YES"<<endl;
			continue;
		}
		/*if (K%2==(length_path_2+length_circle)%2 && K>=length_path_2+length_circle)
		{
			cout<<"YES"<<endl;
			continue;
		}
		if (K%2==(length_path_3+length_circle)%2 && K>=length_path_3+length_circle)
		{
			cout<<"YES"<<endl;
			continue;
		}*/
		cout<<"NO"<<endl;
	}
}
