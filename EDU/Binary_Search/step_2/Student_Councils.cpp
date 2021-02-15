#include<bits/stdc++.h>
using namespace std;
int n, k;
vector<int> a;
bool good(long long x)
{
	long long tot = k * x;
	for (int i = 0; i < n; i++)
	{
		tot -= min(x, (long long)a[i]);
	}
	return tot <= 0;
}
int main()
{
	ios_base::sync_with_stdio(false);
	cin >> k;
	cin >> n;
	a.resize(n);
	for (int i = 0; i < n; i++) cin >> a[i];
	long long l = 0, r = 1;
	while (good(r)) r *= 2;
	while (r > l + 1)
	{
		long long m = (l + r) / 2;
		if (good(m)) l = m;
			else r = m;
	}
	cout << l << endl;
	return 0;
}

