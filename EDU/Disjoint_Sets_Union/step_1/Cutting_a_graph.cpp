#include<stdio.h>
#include<stdlib.h>
#include<algorithm>
#include<iostream>
#include<cstring>
#include<vector>
using namespace std;
const int N = 5e4 + 5;
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
		assign(y, x);
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
	cout.tie(0); 
	int n, m, k;
	cin >> n >> m >> k;
	for (int i = 1; i <= n; i++)
	{
		node[i].p = i;
		node[i].r = 0;
		node[i].reverse = 0;
		node[i].add = 0;
	}
	for (int i = 0; i < m; i++)
	{
		int u, v;
		cin >> u >> v;
	}
	vector< pair< string, pair<int, int> > >op;
	vector<string> ans;
	for (int i = 0; i < k; i++)
	{
		string str;
		int x, y;
		cin >> str >> x >> y;
		op.push_back( {str, {x, y}} );
	}
	for (int i = k - 1; i >= 0; i--)
	{
		string str = op[i].first;
		int x = op[i].second.first, y = op[i].second.second;
		if (str == "cut")
		{
			_union(x, y);
		}
		else if (str == "ask")
		{
			if (get(x) == get(y)) ans.push_back("YES");
			else ans.push_back("NO");
		}
	}
	int size = ans.size();
	for (int i = size - 1; i >= 0; i--) cout << ans[i] << endl;
	return 0;
}
