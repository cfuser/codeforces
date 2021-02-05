#include<stdio.h>
#include<stdlib.h>
#include<algorithm>
#include<iostream>
#include<cstring>
#include<vector>
#include<stack>
using namespace std;
const int N = 2e5 + 5; 
struct Node
{
	int p;
	int r;
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
	//node[x].maxn = max(node[x].maxn, node[y].maxn);
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
	//assign(y, x);
	return y;
}
int _union(int x, int y)
{
	x = get(x);
	y = get(y);
	if (x == y) return 0;
	if (node[x].r == node[y].r) node[x].r++;
	if (node[x].r > node[y].r)
	{
		merge(x, y);
	}
	else
	{
		merge(y, x);
	}
	return 1;
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
		//node[i].maxn = i;
	}
	stack<vector<int>> s;
	int com = n;
	for (int i = 0; i< m; i++)
	{
		string str;
		cin >> str;
		if (str == "persist")
		{
			s.push({1, 0, 0, 0, 0});
		}
		else if (str == "union")
		{
			int x, y;
			cin >> x >> y;
			x = get(x); y = get(y);
			int con;
			s.push({2, x, node[x].r, y, node[y].r, con = _union(x, y)});
			if (con) com -= 1;
			printf("%d\n", com);
		}
		else if (str == "rollback")
		{
			vector<int> op = s.top();
			while (op[0] != 1)
			{
				node[op[1]].p = op[1]; node[op[1]].r = op[2];
				node[op[3]].p = op[3]; node[op[3]].r = op[4];
				if (op[5] == 1) com += 1;
				s.pop();
				op = s.top();
			}
			if (!s.empty()) s.pop();
			printf("%d\n", com);
		}
	}
	return 0;
}


