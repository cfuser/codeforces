#include<stdio.h>
#include<stdlib.h>
#include<algorithm>
#include<iostream>
#include<cstring>
using namespace std;
const int N = 1e5 + 5;
int p[N], r[N];
int get(int x)
{
	return p[x] = (p[x] == x) ? x : get(p[x]);
}
void _union(int x,int y)
{
	x = get(x);
	y = get(y);
	if (r[x] == r[y]) r[x]++;
	if (r[x] > r[y]) p[y] = x;
	else p[x] = y;
}
int main()
{
	int n, m;
	cin >> n >> m;
	memset(p, 0, sizeof(p));
	memset(r, 0, sizeof(r));
	for (int i = 0; i < n; i++) p[i] = i; 
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
			cin >> x >> y;
			x = get(x);
			y = get(y);
			if (x == y) cout << "YES" << endl;
			else cout << "NO" << endl; 
		}
	}
	return 0;
}
