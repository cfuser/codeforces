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
	int minn;
	int time; 
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
	node[x].minn = min(node[y].minn, node[x].minn);
	return 0;
}
int assign(int x, int y) // x assigns to y
{
	//node[y].p = x;
	node[y].minn = node[x].minn;
	return 0;
}
int get(int x)
{
	if (x == node[x].p) return x;
	else
	{
		int y = get(node[x].p);
		//node[x].p = y;
		assign(y, x);
		return y;
	}
}
void _union(int x, int y, int time)
{
	x = get(x);
	y = get(y);
	if (x == y) return ;
	if (node[x].minn == 1) node[y].time = time;
		else if (node[y].minn == 1) node[x].time = time;
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
int get_Ans(int x)
{
	if (node[x].time != INT_MAX) return node[x].time; 
	node[x].time = get_Ans(node[x].p);
	return node[x].time;
}
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
		node[i].minn = i;
		node[i].time = INT_MAX;
	}
	node[1].time = -1;
	int monkey[n + 5][2];
	memset(monkey, 0, sizeof(monkey));
	for (int i = 1; i <= n; i++)
	{
		int x, y;
		cin >> x >> y;
		monkey[i][0] = x;
		monkey[i][1] = y;
	}
	vector< pair<int, int> > op;
	int vis[n + 5][2];
	memset(vis, 0, sizeof(vis));
	//node[1].r = 1;
	for (int i = 0; i < m; i++)
	{
		int x, y;
		cin >> x >> y;
		op.push_back( {x, y - 1} );
		vis[x][y - 1] = 1;
	}
	for (int i = 1; i <= n; i++)
	{
		if (vis[i][0] == 0 && monkey[i][0] != -1) _union(i, monkey[i][0], -1);
		if (vis[i][1] == 0 && monkey[i][1] != -1) _union(i, monkey[i][1], -1);
	}
	for (int i = m - 1; i >= 0; i--)
	{
		int x = op[i].first, y = op[i].second;
		if (vis[x][y] == 1)
		{
			_union(x, monkey[x][y], i);	
		}
	}
	for (int i = 1; i <= n; i++) cout << get_Ans(i) << endl;
	return 0;
}
