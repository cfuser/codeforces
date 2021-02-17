#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
const int edge_MAX = 1e9 + 5;
int n, m, d;
vector<vector<int>> edge[N];
vector<int> num_edge(n, INT_MAX);
vector<int> dir(n, INT_MAX);
vector<double> intersect(vector<double> boundary, vector<double> bound_i)
{
	return vector<double> {max(boundary[0], bound_i[0]), min(boundary[1], bound_i[1])};
}
bool good(long long dis)
{
	queue<int> q;
	num_edge.assign(n, INT_MAX);
	dir.assign(n, INT_MAX);
	num_edge[0] = 0;
	dir[0] = 0;
	q.push(0);
	while (!q.empty())
	{
		int x = q.front();
		q.pop();
		for (int i = 0; i < edge[x].size(); i++)
		{
			int y = edge[x][i][0], z = edge[x][i][1];
			if (z <= dis && num_edge[y] == INT_MAX)
			{
				q.push(y);
				num_edge[y] = num_edge[x] + 1;
				dir[y] = x;
				if (y == n - 1)
				{
					return num_edge[y] <= d;
				}
			}
		}
	}
	return false;
}
void out_path(int dis)
{
	good(dis);
	cout << num_edge[n - 1] << endl;
	stack<int> st;
	int pos = n - 1;
	while (pos != 0)
	{
		st.push(pos);
		pos = dir[pos];
	}
	st.push(0);
	while (!st.empty())
	{
		cout << st.top() + 1 << " ";
		st.pop();
	} 
	cout << endl;
}
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m >> d;
	for (int i = 0; i < m; i++)
	{
		int x, y, z;
		cin >> x >> y >> z;
		edge[x - 1].push_back({y - 1, z});
	}
	int l = 0, r = 1;
	while (!good(r))
	{
		if (r > edge_MAX)
		{
			cout << -1 << endl;
			return 0;
		}
		r *= 2;	
	}
	while (r - l > 1)
	{
		long long m = (l + r) / 2;
		if (!good(m)) l = m;
		else r = m;
	}
	out_path(r);
	return 0;
}


