#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
long long sum[2], value[N][2];
int vis[N], color[N];
vector<int> edge[N];
string work(int n, int m)
{
	if ((sum[0] - sum[1]) % 2) return "NO";
	sum[0] = 0; sum[1] = 0;
	vis[1] = 1; color[1] = 1; sum[color[1] - 1] += value[1][1] - value[1][0];
	queue<int> q;
	q.push(1);
	while (!q.empty())
	{
		int x = q.front();
		q.pop();
		for (int i = 0; i < edge[x].size(); i++)
		{
			int y = edge[x][i];
			if (vis[y] == 0)
			{
				color[y] = 3 - color[x];
				sum[color[y] - 1] += value[y][1] - value[y][0];
				q.push(y);
				vis[y] = 1;
			}
			else if (color[x] == color[y]) return "YES";
		}
	}
	if (sum[0] == sum[1]) return "YES";
	else return "NO";
}
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int T;
	cin >> T;
	while (T--)
	{
		int n, m;
		cin >> n >> m;
		for (int i = 1; i <= n; i++) edge[i].clear();
		memset(sum, 0, sizeof(sum));
		memset(value, 0, sizeof(value));
		memset(vis, 0, sizeof(vis));
		memset(color, 0, sizeof(color));
		for (int i = 1; i <= n; i++) cin >> value[i][0];
		for (int i = 1; i <= n; i++) cin >> value[i][1];
		for (int i = 0; i < m; i++)
		{
			int x, y;
			cin >> x >> y;
			edge[x].push_back(y);
			edge[y].push_back(x);
		}
		for (int i = 1; i <= n; i++)
		{
			sum[0] += value[i][0];
			sum[1] += value[i][1];
		}
		cout << work(n, m) << endl;
	}
	return 0;
}
