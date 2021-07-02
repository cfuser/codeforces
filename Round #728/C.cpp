#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
long long a[N];
int main()
{
	int T;
	cin >> T;
	while (T--)
	{
		int n;
		cin >> n;
		for (int i = 0; i < n; i++) cin >> a[i];
		sort(a, a + n);
		long long ans = 0, cost = 0;
		for (int i = 1; i < n; i++)
		{
			cost += a[i - 1];
			ans += (cost - a[i] * i);
		}
		ans += a[n - 1];
		cout << ans << endl;
	}
	return 0;
}
