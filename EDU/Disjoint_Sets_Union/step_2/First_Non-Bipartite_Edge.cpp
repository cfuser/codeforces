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
	int len;
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
int merge(vector<int> x, vector<int> y) // y points to x
{
	node[y[0]].p = x[0];
	node[y[0]].len = (1 + y[1] + x[1]) % 2;
	return 0;
}
int assign(vector<int> x, int y) // x assigns to y
{
	node[y].p = x[0];
	node[y].len = (node[y].len + x[1]) % 2;
	return 0;
}
vector<int> get(int x)
{
	if (node[x].p == x) return vector<int>{x, node[x].len};
	vector<int> y = get(node[x].p);
	//node[x].p = y;
	assign(y, x);
	return vector<int>{node[x].p, node[x].len};
}
bool _union(int x, int y)
{
	vector<int> root_x = get(x), root_y = get(y);
	if (root_x[0] == root_y[0]) return root_x[1] == root_y[1];
	if (node[root_x[0]].r == node[root_y[0]].r) node[root_x[0]].r++;
	if (node[root_x[0]].r > node[root_y[0]].r)
	{
		merge(root_x, root_y);
	}
	else
	{
		merge(root_y, root_x);
	}
	return false;
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
	for (int i = 1; i <= n + 1; i++)
	{
		node[i].p = i;
		node[i].r = 0;
		node[i].len = 0;
	}
	int print = 0;
	for (int i = 0; i< m; i++)
	{
		int x, y;
		cin >> x >> y;
		if (_union(x, y))
		{
			printf("%d\n", i + 1);
			print = 1;
			break;
		}
	}
	if (print == 0) printf("-1\n");
	return 0;
}


