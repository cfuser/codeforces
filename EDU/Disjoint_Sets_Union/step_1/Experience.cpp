#include<stdio.h>
#include<stdlib.h>
#include<algorithm>
#include<iostream>
#include<cstring>
using namespace std;
const int N = 2e5 + 5;
struct Node
{
	int p;
	int r;
	int reverse;
	int add;
};
Node node[N];
int merge(int x, int y) // y points to x
{
	node[y].p = x;
	node[y].reverse = node[x].add;
	return 0;
}
int assign(int x,int y) // x assigns to y
{
	node[y].p = x;
}
int get(int x)
{
	if (x == node[x].p) return x;
	else
	{
		int y = get(node[x].p);
		//node[x].p = y;
		//assign(y, x);
		return y;
	}
}
int sum(int x)
{
	int y = get(x);
	if (y == x) return node[y].add;
	else return node[x].add - node[x].reverse + sum(node[x].p);
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
		node[i].reverse = 0;
		node[i].add = 0;
	}
	for (int i = 0; i < m; i++)
	{
		string str;
		cin >> str;
		if (str == "join")
		{
			int x, y;
			cin >> x >> y;
			_union(x, y);
		}
		else if (str == "add")
		{
			int x, y;
			cin >> x >> y;
			x = get(x);
			node[x].add += y;
		}
		else if (str == "get")
		{
			int x, y;
			cin >> x;
			y = sum(x);
			cout << y << endl;
		}
	}
	return 0;
}
