#include<bits/stdc++.h>
using namespace std;
int n;
long long m;
vector<vector<int>> a;
vector<long long> ans;
bool good(long long t)
{
	long long num = 0;
	for (int i = 0; i < n; i++)
	{
		ans[i] = t / (a[i][0] * a[i][1] + a[i][2]) *a[i][1];
		ans[i] += (long long)min(t % (a[i][0] * a[i][1] + a[i][2]) / a[i][0], (long long)a[i][1]);
		num += ans[i];
	}
	return num >= m;
}
int main()
{
	ios_base::sync_with_stdio(false);
	cin >> m >> n;
	a.resize(n);
	ans.resize(n);
	for (int i = 0; i < n; i++)
	{
		int t, z, y;
		cin >> t >> z >> y;
		a[i] = {t, z, y};
	} 
	long long l = 0, r = 1; // l is bad, r is good
	while (!good(r)) r *= 2;
	if (m == 0) r = 0;
	while (r > l + 1)
	{
		long long mid = (l + r) / 2;
		if (good(mid)) r = mid;
			else l = mid;
	}
	cout << r << endl;
	good(r);
	long long tot = 0;
	for (int i = 0; i < n; i++)
	{
		tot += ans[i];
		if (tot > m)
		{
			ans[i] -= (tot - m);
			tot = m;
		}
	}
	for (int i = 0; i < n; i++) cout << ans[i] << " "; cout << endl;
	return 0;
}

