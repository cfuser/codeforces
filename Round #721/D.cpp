#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
int vis[N], fa[N];
long long child_num[N];
vector<int> edge[N];
void preprocess(int n)
{
	memset(vis, 0, sizeof(vis));
	vis[0] = 1;
	memset(child_num, 0, sizeof(child_num));
	memset(fa, 0, sizeof(fa));
	for (int i = 0; i < n; i++)
	edge[i].clear(); 
	return ;
}
void dfs(int u)
{
	child_num[u] = 1;
	for (int i = 0; i < edge[u].size(); i++)
	{
		int v = edge[u][i];
		if (vis[v] == 0)
		{
			vis[v] = 1;
			fa[v] = u;
			dfs(v);
			child_num[u] += child_num[v];
		}
	}
	return ;
}
long long update(int u, int &l, int &r)
{
	int v = u;
	if (vis[u] == 1) return -1;
	while (vis[v] == 0)
	{
		vis[v] = 1;
		if (fa[v] == 0) child_num[0] -= child_num[v];
		v = fa[v];
	}
	if (v != l && v != r) return 0;
	else
	{
		if (v == l)
		{
			l = u;
			return child_num[u] * child_num[r];
		}
		else
		{
			r = u;
			return child_num[u] * child_num[l];
		}
	}
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int T;
	cin >> T;
	while (T--)
	{
		int n;
		cin >> n;
		preprocess(n);
		for (int i = 1; i < n; i++)
		{
			int x, y;
			cin >> x >> y;
			edge[x].push_back(y);
			edge[y].push_back(x);
		}
		dfs(0);
		memset(vis, 0, sizeof(vis));
		int l = 0, r = 0;
		vis[0] = 1;
		long long dp[n + 1];
		memset(dp, 0, sizeof(dp));
		for (int i = 0; i < edge[0].size(); i++)
		{
			long long child = child_num[edge[0][i]];
			dp[0] += child * (child - 1) / 2;
		}
		long long P = (long long)n * (n - 1) / 2 - dp[0], P_plus = 0;
		for (int i = 1; i < n; i++)
		{
			P_plus = update(i, l, r);
			if (P_plus != -1)
			{
				dp[i] = P - P_plus;
				P = P_plus;
			}
			else
			{
				P_plus = P;
				dp[i] = 0;
			}
			if (P == 0) break;
		}
		dp[n] = P_plus;
		for (int i = 0; i <= n; i++) cout << dp[i] << " ";
		cout << endl;
	}
	return 0;
}
