#include<bits/stdc++.h>
using namespace std;
const long long N = 2e2 + 5;
const long long M = 10;
const long long MO = 1e9 + 7;
vector<long long> edge[N];
long long child_num[N], vis[N], fa[N][M], depth[N];
long long prob[N][N];
long long MO_[N];
long long d[2];

long long fast_pow(long long x, long long y)
{
	if (y == 1) return x;
	long long res = fast_pow(x, y / 2) % MO;
	res = res * res % MO;
	if (y % 2) res = res * x % MO;
	return res; 
}
//const long long MO_2 = fast_pow(2, MO - 2);

long long lca(int u, int v)
{
	if (depth[u] < depth[v]) swap(u, v);
	int deep = M - 1;
	while (depth[u] > depth[v])
	{
		if (depth[fa[u][deep]] >= depth[v]) u = fa[u][deep];
		deep -= 1;
	}
	deep = M - 1;
	if (u == v) return u;
	while (deep >= 0)
	{
		if (fa[u][deep] != fa[v][deep])
		{
			u = fa[u][deep];
			v = fa[v][deep];
		}
		deep -= 1;
	}
	return fa[u][0];
}

void dfs(int root)
{
	int deep = 0;
	while (fa[fa[root][deep]][deep] != 0)
	{
		fa[root][deep + 1] = fa[fa[root][deep]][deep];
		deep += 1;
	}
	vis[root] = 1;
	child_num[root] = 1;
	for (int i = 0; i < edge[root].size(); i++)
	{
		int v = edge[root][i];
		if (vis[v] == 0)
		{
			depth[v] = depth[root] + 1;
			fa[v][0] = root;
			dfs(v);
			child_num[root] += child_num[v];
		}
	}
	
}

void prob_dfs(int x, int y)
{
	if (x == 0 || y == 0 || prob[x][y] != 0) return ;
	prob_dfs(x - 1, y);
	prob_dfs(x, y - 1);
	prob[x][y] = (prob[x - 1][y] + prob[x][y - 1]) % MO * MO_[2] % MO;
}

void precalculate()
{
	prob[0][0] = -1;
	for (int i = 1; i < N; i++)
	{
		prob[i][0] = 1;
		prob[0][i] = 0;
	}
	//prob_dfs(N - 1, N - 1);
	for (int i = 1; i < N; i++)
		for (int j = 1; j < N; j++)
		prob[i][j] = (prob[i - 1][j] + prob[i][j - 1]) % MO * MO_[2] % MO;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	//long long MO_n = fast_pow(n, MO - 2);
	
	//for (int i = 1; i <= n; i++) MO_[i] = fast_pow(i, MO - 2);
	MO_[2] = fast_pow(2, MO - 2);
	MO_[n] = fast_pow(n, MO - 2);
	//cout << 1 * MO_[2] % MO << endl;
	//cout << 1 * MO_[4] % MO << endl;
	precalculate();
	//cout << prob[1][1] << endl;
	int temp = 0;
	for (int i = 1; i < n; i++)
	{
		int u, v;
		cin >> u >> v;
		edge[u].push_back(v);
		edge[v].push_back(u);
	}
	depth[0] = 0; depth[1] = 1;
	fa[1][0] = 0;
	dfs(1);
	long long ans = 0;
	//long long prev_ans = 0;
	for (int i = 1; i <= n; i++)
		for (int j = i + 1; j <= n; j++)
		{
			int root = lca(i, j), LEN = depth[i] - depth[root] + depth[j] - depth[root];
			int u = i, v = j, root_child_num = n, prev_child = 0;
			while (u != root)
			{
				d[0] = depth[i] - depth[u];
				d[1] = LEN - d[0];
				ans = (ans + (child_num[u] - prev_child) * MO_[n] % MO * prob[d[0]][d[1]] % MO) % MO;
				if (fa[u][0] == root) root_child_num -= child_num[u];
				prev_child = child_num[u];
				u = fa[u][0];
			}
			u = i, v = j, prev_child = 0;
			while (v != root)
			{
				d[1] = depth[j] - depth[v];
				d[0] = LEN - d[1];
				ans = (ans + (child_num[v] - prev_child) * MO_[n] % MO * prob[d[0]][d[1]] % MO) % MO;
				if (fa[v][0] == root) root_child_num -= child_num[v];
				prev_child = child_num[v];
				v = fa[v][0];
			}
			u = i, v = j;
			ans = (ans + (root_child_num * MO_[n] % MO * prob[depth[u] - depth[root]][depth[v] - depth[root]]) % MO ) % MO;
			//cout << i << " " << j << " " << (ans - prev_ans + MO) % MO << endl;
			//prev_ans = ans;
			//if (n == 200 && i == n - 1) cout << ans << endl;
		}
	cout << ans << endl;
	return 0;
}
