#include<bits/stdc++.h>
using namespace std;
const int MO = 998244353;
long long fast_power(int x)
{
	if (x == 0) return 1;
	long long y = fast_power(x / 2);
	return y * y % MO * (x % 2 + 1) % MO;
}
int main()
{
	int n, m, num = 0;
	long long ans = 0;
	cin >> n >> m;
	int a[n][m];
	memset(a, 0, sizeof(a));
	for (int i = 0; i < n; i++)
	{
		string str;
		cin >> str;
		for (int j = 0; j < m; j++)
		{
			if (str[j] == '*') a[i][j] = 0;
			else
			{
				a[i][j] = 1;
				num += 1;
			}
		}
	}
	
	long long ti[num + 1];
	ti[0] = 1;
	for (int i = 1; i <= num; i++) ti[i] = ti[i - 1] * 2 % MO;
	
	long long f[num + 1][3];
	memset(f, 0, sizeof(f));
	f[0][0] = 1; f[0][1] = 0; f[0][2] = 0;
	for (int i = 1; i <= num; i++)
	{
		f[i][0] = (f[i - 1][0] + f[i - 1][1] + f[i - 1][2]) % MO;
		f[i][1] = (f[i - 1][0] + f[i - 1][2]) % MO;
		f[i][2] = (f[i - 1][1]) % MO;
	}
	
	long long dp[num + 1][4];
	memset(dp, 0, sizeof(dp));
	dp[0][0] = 0; dp[0][1] = 0; dp[0][2] = 0; dp[0][3] = 0;
	dp[1][0] = 0; dp[1][1] = 0; dp[1][2] = 0; dp[1][3] = 0;
	for (int i = 2; i <= num; i++)
	{
		dp[i][0] = (dp[i - 1][0] + dp[i - 1][1] + dp[i - 1][2]) % MO;
		dp[i][1] = (dp[i - 1][0] + dp[i - 1][2]) % MO;
		dp[i][2] = (dp[i - 1][1] + (f[i - 2][0] + f[i - 2][2])) % MO;
		dp[i][3] = (dp[i][0] + dp[i][1] + dp[i][2]) % MO;
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		if (a[i][j] == 1)
		{
			int k = j;
			while (k + 1 < m && a[i][k + 1] == 1) k += 1;
			ans = (ans + ti[num - (k - j + 1)] * dp[k - j + 1][3]) % MO;
			j = k;
		}
	}
	
	for (int j = 0; j < m; j++)
	{
		for (int i = 0; i < n; i++)
		if (a[i][j] == 1)
		{
			int k = i;
			while (k + 1 < n && a[k + 1][j] == 1) k += 1;
			ans = (ans + ti[num - (k - i + 1)] * dp[k - i + 1][3]) % MO;
			i = k;
		}
	}
	
	cout << ans << endl; 
	return 0;
}
