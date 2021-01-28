#include<stdio.h>
#include<stdlib.h>
#include<algorithm>
#include<iostream>
#include<cstring>
#include<vector>
using namespace std;
const int N = 2e5 + 5; 
struct Node
{
	int p;
	int r;
	int maxn;
	int next;
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
int merge(int x, int y) // y points to x
{
	node[y].p = x;
	node[x].maxn = max(node[x].maxn, node[y].maxn);
	return 0;
}
int assign(int x, int y) // x assigns to y
{
	node[y].p = x;
	//node[y].maxn = node[x].maxn;
	return 0;
}
int get(int x)
{
	if (node[x].p == x) return x;
	int y = get(node[x].p);
	//node[x].p = y;
	assign(y, x);
	return y;
}
void _union(int x, int y)
{
	x = get(x);
	y = get(y);
	if (x == y) return ;
	if (node[x].r == node[y].r) node[x].r++;
	if (node[x].r > node[y].r)
	{
		merge(x, y);
	}
	else
	{
		merge(y, x);
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
		node[i].maxn = i;
		node[i].next = i + 1;
	}
	for (int i = 0; i< m; i++)
	{
		int k, x, y;
		cin >> k >> x >> y;
		if (k == 1)
		{
			x = get(x);
			y = get(y);
			_union(x, y);
		}
		else if (k == 2)
		{
			for (int i = x + 1, next; i <= y; i = next)
			{
				_union(i - 1, i);
				next = node[i].next;
				node[i].next = node[y].next;
			}
		}
		else if (k == 3)
		{
			x = get(x);
			y = get(y);
			if (x == y) printf("YES\n");
			else printf("NO\n");
		}
	}
	return 0;
}



