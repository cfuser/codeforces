#include<stdio.h>
#include<stdlib.h>
#include<algorithm>
#include<iostream>
#include<cstring>
#include<vector>
using namespace std;
const int N = 3e5 + 5; 
struct Node
{
	int p;
	int r;
	int depth;
	int add;
};
Node node[N];
/*
struct Monkey
{
	int l, r;
};
Monkey monkey[N];
*/
//int monkey[N][2];
int merge(int x, int y,int add) // y points to x
{
	node[y].p = x;
	if (add == 1) node[y].add += 1 - node[x].add;
	else if (add == -1)
	{
		node[x].add += 1;
		node[y].add -= node[x].add;
	}
	return 0;
}
int assign(int x, int y) // x assigns to y
{
	node[y].depth = node[node[y].p].depth + node[y].add;
	node[y].add = 0;
	node[y].p = x;
	//node[y].maxn = node[x].maxn;
	return 0;
}
int get(int x)
{
	if (node[x].p == x)
	{
		//node[x].depth = node[x].depth + node[x].add;
		//node[x].add = 0;
		return x;
	}
	int y = get(node[x].p);
	//node[x].p = y;
	//assign(y, x);
	return y;
}
int get_Sum(int x)
{
	if (node[x].p == x) return node[x].add;
	else return node[x].add + get_Sum(node[x].p);
}
void _union(int x, int y)
{
	x = get(x);
	y = get(y);
	if (x == y) return ;
	if (node[x].r == node[y].r) node[x].r++;
	if (node[x].r > node[y].r)
	{
		merge(x, y, 1);
	}
	else
	{
		merge(y, x, -1);
	}
}
/*
int get_Ans(int x)
{
	if (node[x].time != INT_MAX) return node[x].time; 
	node[x].time = get_Ans(node[x].p);
	return node[x].time;
}
*/
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0); 
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
	{
		node[i].p = i;
		node[i].r = 0;
		node[i].add = 0;
	}
	for (int i = 0; i < m; i++)
	{
		int x;
		cin >> x;
		if (x == 1)
		{
			int y, z;
			cin >> y >> z;
			y = get(y);
			z = get(z);
			_union(z, y);
		}
		else if (x == 2)
		{
			int y;
			cin >> y;
			printf("%d\n", get_Sum(y));
		}
	}
	return 0;
}

