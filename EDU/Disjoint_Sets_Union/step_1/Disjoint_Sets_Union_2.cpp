#include<stdio.h>
#include<stdlib.h>
#include<algorithm>
#include<iostream>
#include<cstring>
using namespace std;
const int N = 3e5 + 5;
struct Node
{
	int p;
	int r;
	int maxn;
	int minn;
	int num;
};
Node node[N];
int merge(int x, int y) // y points to x
{
	node[y].p = x;
	node[x].maxn = max(node[x].maxn, node[y].maxn);
	node[x].minn = min(node[x].minn, node[y].minn);
	node[x].num = node[x].num + node[y].num;
}
int assign(int x,int y) // x assigns to y
{
	node[y].p = x;
	node[y].maxn = node[x].maxn;
	node[y].minn = node[x].minn;
	node[y].num = node[x].num;
}
int get(int x)
{
	if (x == node[x].p) return x;
	else
	{
		int y = get(node[x].p);
		//assign(y, x);
		return y;
	}
}
void _union(int x,int y)
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
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
	{
		node[i].p = i;
		node[i].r = 0;
		node[i].num = 1;
		node[i].maxn = i;
		node[i].minn = i;
	}
	for (int i = 0; i < m; i++)
	{
		string str;
		cin >> str;
		if (str == "union")
		{
			int x, y;
			cin >> x >> y;
			_union(x, y);
		}
		else if (str == "get")
		{
			int x, y;
			cin >> x;
			y = get(x);
			cout << node[y].minn << " " << node[y].maxn << " " << node[y].num << endl;
		}
	}
	return 0;
}
