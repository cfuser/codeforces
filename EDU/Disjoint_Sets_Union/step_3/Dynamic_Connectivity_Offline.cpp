#include<stdio.h>
#include<stdlib.h>
#include<algorithm>
#include<iostream>
#include<cstring>
#include<vector>
#include<stack>
using namespace std;
const int N = 3e5 + 5; 
struct Node
{
	int p;
	int r;
};
Node node[N];
bool need[N];
vector<vector<int>> seg[4 * N];
/*
struct Monkey
{
	int l, r;
};
Monkey monkey[N];
*/
//int monkey[N][2];
void add(int v, int l, int r, int x, int y, int t_h, int t_t)
{
	if (l >= t_t || r <= t_h) return ;
	if (l >= t_h && r <= t_t)
	{
		seg[v].push_back({x, y, t_h, t_t});
		return ;
	}
	int m = (l + r) / 2;
	add(2 * v, l, m, x, y, t_h, t_t);
	add(2 * v + 1, m, r, x, y, t_h, t_t);
	return ;
}
bool cmp(const vector<int> &a, const vector<int> &b)
{
	return a[1] < b[1] || (a[1] == b[1] && a[2] < b[2]) || (a[1] == b[1] && a[2] == b[2] && a[3] < b[3]);
}
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
bool equal(vector<int> a, vector<int> b)
{
	return a[1] == b[1] && a[2] == b[2];
}
bool in(int l, int r, int l_bound, int r_bound)
{
	return l >= l_bound && r <= r_bound;
}
bool intersect(int l, int r, int l_bound, int r_bound)
{
	return !(l >= r_bound || r <= l_bound); 
}
stack<vector<int>> s;
void work(int v, int l, int r, int com)
{
	//cout << l << " " << r << " " << com << endl;
	/*if (l == r - 1)
	{
		int len = seg[v].size();
		if (l == 8)
		{
			cout << endl;
			for (int i = 0; i < len; i++) cout << seg[v][i][0] << " " << seg[v][i][1] << " " << seg[v][i][2] << " " << seg[v][i][3] << endl;
			cout << endl;
		}
		for (int i = 0; i < len; i++)
		{
			if (seg[v][i][0] == 0 && seg[v][i][2] == l)
			{
				printf("%d\n", com);
			}
		}
		return ;
	}*/
	int cnt = 0;
	//vector<vector<int>> query_l;
	//vector<vector<int>> query_r;
	int len = seg[v].size(), m = (l + r) / 2;
	for (int i = 0; i < len; i++)
	{
		if (seg[v][i][0] != 0 && in(l, r, seg[v][i][2], seg[v][i][3]))
		{
			int x = get(seg[v][i][0]), y = get(seg[v][i][1]);
			int con;
			vector<int> temp{x, node[x].r, y, node[y].r, con = _union(x, y)};
			if (con) s.push(temp);
			if (con) com -= 1;
			cnt += con;
		}
		/*if (query[i][0] == 0 && in(query[i][2], query[i][3], l, m) || query[i][0] != 0 && intersect(l, m, query[i][2], query[i][3]))
		{
			query_l.push_back(query[i]);
		}
		if (query[i][0] == 0 && in(query[i][2], query[i][3], m, r) || query[i][0] != 0 && intersect(m, r, query[i][2], query[i][3]))
		{
			query_r.push_back(query[i]);
		}*/
		
	}
	if (l == r - 1)
	{
		/*for (int i = 0; i < len; i++)
		{
			if (query[i][0] == 0 && query[i][2] == l)
			{
				printf("%d\n", com);
			}
		}*/
		if (need[l]) printf("%d\n", com);
	}
	else
	{
		work(2 * v    , l, m, com);//work(2 * v, l, m, query_l, com);
		work(2 * v + 1, m, r, com);//work(2 * v + 1, m, r, query_r, com);
	}
	while (cnt--)
	{
		vector<int> operation = s.top();
		node[operation[0]].p = operation[0]; node[operation[0]].r = operation[1];
		node[operation[2]].p = operation[2]; node[operation[2]].r = operation[3];
		if (operation[4] == 1) com += 1;
		s.pop();
		if (!s.empty()) operation = s.top();
	}
	return ;
}
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
	deque<vector<int>> deq;
	int com = n;
	memset(need, 0, sizeof(need));
	for (int i = 0; i < m; i++)
	{
		string str;
		cin >> str;
		if (str == "?")
		{
			need[i] = 1;
		}
		else if (str == "+")
		{
			int x, y;
			cin >> x >> y;
			deq.push_back({1, min(x, y), max(x, y), i});
		}
		else if (str == "-")
		{
			int x, y;
			cin >> x >> y;
			deq.push_back({2, min(x, y), max(x, y), i});
		}
	}
	sort(deq.begin(), deq.end(), cmp);
	//for (int i = 0; i < deq.size(); i++) cout << deq[i][0] << " " << deq[i][1] << " " << deq[i][2] << " " << deq[i][3] << endl; 
	//cout << endl;
	vector<vector<int>> query(m, vector<int>(4)); 
	for (int i = 0; i < deq.size();)
	{
		//vector<int> op = deq.front();
		//deq.pop_back()
		if (deq[i][0] == 0)
		{
			//query[i] = {0, 0, op[i][3], op[i][3]};
			i += 1; 
		}
		else
		{
			int j = i;
			for (; j + 1 < deq.size(); j += 2)
			if (equal(deq[i], deq[j + 1]))
			{
				//query[i] = {deq[i][1], deq[i][2], deq[j][3], deq[j + 1][3]};
				add(1, 0, m, deq[i][1], deq[i][2], deq[j][3], deq[j + 1][3]);
			}
			else break;
			if (j < deq.size() && equal(deq[i], deq[j]))
			{
				//query[i] = {deq[i][1], deq[i][2], deq[j][3], m};
				add(1, 0, m, deq[i][1], deq[i][2], deq[j][3], m);
				j += 1;
			}
			i = j;
		}
	}
	deq.clear();
	//for (int i = 0; i < query.size(); i++) cout << query[i][0] << " " << query[i][1] << " " << query[i][2] << " " << query[i][3] << endl;
	//cout << endl;
	if (m != 0) work(1, 0, m, com);//work(0, m, query, com);
	return 0;
}


