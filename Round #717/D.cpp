#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
vector<int> prime[N];
int nxt[N], a[N], dp[N][20]; 
int n, q;
int main()
{
	cin >> n >> q;
	for (int i = 0; i < n; i++)
	{
		nxt[i] = n;
		cin >> a[i];
		int x = a[i];
		for (int j = 2; j * j <= x; j++)
		if (x % j == 0)
		{
			if (prime[j].size())
			{
				int size = prime[j].size(), y = prime[j][size - 1];
				nxt[y] = min(nxt[y], i);
			}
			prime[j].push_back(i);
			while (x % j == 0)
			{
				x = x / j;
			}
		}
		if (x != 1)
		{
			if (prime[x].size())
			{
				int size = prime[x].size(), y = prime[x][size - 1];
				nxt[y] = min(nxt[y], i);
			}
			prime[x].push_back(i);
		} 
	}
	//for (int i = 0; i < n; i++) cout << nxt[i] << " ";cout << endl;
	nxt[n] = n;
	for (int i = n - 1; i >= 0; i--) dp[i][0] = nxt[i] = min(nxt[i], nxt[i + 1]);
	dp[n][0] = n;
	for (int i = 1, t = 1; t < n; i++, t *= 2)
	{
		for (int j = 0; j < n; j++)
		dp[j][i] = dp[dp[j][i - 1]][i - 1];
		dp[n][i] = n;
	}
	for (int index = 0; index < q; index++)
	{
		int l, r;
		cin >> l >> r;
		l -= 1; r -= 1;
		int num = 0, sum = 0;
		int depth = log(n) / log(2);
		for (int i = depth; i >= 0; i--)
		{
			if (dp[l][i] <= r)
			{
				sum += 1 << i;
				l = dp[l][i];
			}
		}
		cout << sum + 1 << endl;
	}
	return 0;
}
