#include<stdio.h>
#include<stdlib.h>
#include<algorithm>
#include<iostream>
#include<cstring>
#include<vector>
#include<stack>
#include<math.h>
using namespace std;
const int N = 5e4 + 5; 
int unit;
struct Node
{
	int p;
	int r;
	int size;
};
Node node[N];
struct Edge
{
	int x;
	int node_x;
	int y;
	int node_y;
	int con;
};
Edge edge[N];
/*
struct Monkey
{
	int l, r;
};
Monkey monkey[N];
*/
//int monkey[N][2];
bool cmp(const vector<int> &a, const vector<int> &b)
{
	return a[0] / unit < b[0] / unit || a[0] / unit == b[0] / unit && a[1] < b[1];
}
int merge(int x, int y) // y points to x
{
	node[y].p = x;
	//node[x].size += node[y].size;
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
	/*if (node[x].size > node[y].size)
	{
		merge(x, y);
	}
	else
	{
		merge(y, x);
	}*/
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
	//ios_base::sync_with_stdio(false);
	//cin.tie(0);
	//cout.tie(0); 
	int n, m, edge_h, edge_t;
	scanf("%d%d", &n, &m); // cin >> n >> m;
	for (int i = 1; i <= n + 1; i++)
	{
		node[i].p = i;
		node[i].r = 0;
		node[i].size = 1;
		//node[i].maxn = i;
	}
	stack<vector<int>> s;
	vector<vector<int>> op(m + 5, vector<int>(2));
	int com = n;
	for (int i = 0; i< m; i++)
	{
		int x, y;
		scanf("%d%d", &x, &y); // cin >> x >> y;
		op[i] = {x, y};
		//op.push_back({x, y});
	}
	int q;
	scanf("%d", &q); // cin >> q;
	vector<vector<int>> query(q, vector<int>(3));
	vector<int> ans(q, 0);
	for (int i = 0; i < q; i++)
	{
		int l, r;
		scanf("%d%d", &l, &r); // cin >> l >> r;
		query[i] = vector<int>({l - 1, r - 1, i});
	}
	unit = (int)sqrt(m);
	sort(query.begin(), query.end(), cmp);
	int index = 0;
	for (index = 0; index < q; index++)
	{
		int l = query[index][0], r = query[index][1], group = l / unit;
		//edge_ h = edge_t = 0;
		vector<int> operation;
		while (group == r / unit)
		{
			com = n;
			for (int i = l; i <= r; i++)
			{
				int x = op[i][0], y = op[i][1];
				x = get(x); y = get(y);
				int con;
				vector<int> temp{x, node[x].r, y, node[y].r, con = _union(x, y)};
				temp.push_back(con);
				if (con) s.push(temp);
				if (con) com -= 1;
			}
			ans[query[index][2]] = com;
			operation = s.top();
			while (!s.empty())
			{
				node[operation[0]].p = operation[0]; node[operation[0]].r = operation[1];
				node[operation[2]].p = operation[2]; node[operation[2]].r = operation[3];
				if (operation[4] == 1) com += 1;
				s.pop();
				if (!s.empty()) operation = s.top();
			}
			index += 1;
			if (index >= q) break;
			l = query[index][0], r = query[index][1];
		}
		if (index >= q) break;
		com = n;
		l = query[index][0], r = query[index][1];
		int h, t = l / unit * unit + unit;
		h = t;
		while (l / unit == group && r / unit > l / unit)
		{
			for (int i = t; i <= r; i++)
			{
				int x = op[i][0], y = op[i][1];
				x = get(x); y = get(y);
				int con;
				vector<int> temp{x, node[x].r, y, node[y].r, con = _union(x, y)};
				if (con) s.push(temp);
				if (con) com -= 1;
			}
			s.push({0, 0, 0, 0, 0});
			for (int i = l; i < h; i++)
			{
				int x = op[i][0], y = op[i][1];
				x = get(x); y = get(y);
				int con;
				vector<int> temp{x, node[x].r, y, node[y].r, con = _union(x, y)};
				if (con) s.push(temp);
				if (con) com -= 1;
			}
			ans[query[index][2]] = com;
			operation = s.top();
			while (operation[0] != 0)
			{
				node[operation[0]].p = operation[0]; node[operation[0]].r = operation[1];
				node[operation[2]].p = operation[2]; node[operation[2]].r = operation[3];
				if (operation[4] == 1) com += 1;
				s.pop();
				operation
				 = s.top();
			}
			s.pop();
			t = r + 1;
			index += 1;
			if (index >= q) break;
			l = query[index][0], r = query[index][1];
		}
		while (!s.empty())
		{
			operation = s.top();
			s.pop();
			node[operation[0]].p = operation[0]; node[operation[0]].r = operation[1];
			node[operation[2]].p = operation[2]; node[operation[2]].r = operation[3];
			if (operation[4] == 1) com += 1;
		}
		index -= 1;
	}
	for (int i = 0; i < q; i++) printf("%d\n", ans[i]);
	return 0;
}

