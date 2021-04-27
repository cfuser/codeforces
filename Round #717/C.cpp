#include<bits/stdc++.h>
using namespace std;
const int N = 1e2 + 5;
const int Max = 2e5 + 5;
int n;
int a[N], dp[Max];
int main()
{
	cin >> n;
	for (int i = 0; i < n; i++) cin >> a[i];
	int sum = 0;
	for (int i = 0; i < n; i++) sum += a[i];
	if (sum % 2 == 1)
	{
		cout << 0 << endl;
		return 0;
	}
	memset(dp, 0, sizeof(dp));
	dp[0] = 1;
	for (int i = 0; i < n; i++)
		for (int j = sum; j >= a[i]; j--)
		if (dp[j - a[i]]) dp[j] = 1;
	if (dp[sum / 2] == 0)
	{
		cout << 0 << endl;
		return 0;
	}
	for (int i = 0; i <n; i++) 
	if (!(a[i] % 2 == sum % 2 && dp[(sum - a[i]) / 2] == 1))
	{
		cout << 1 << endl << i + 1 << endl;
		return 0;
	}
	//return 0;
}
