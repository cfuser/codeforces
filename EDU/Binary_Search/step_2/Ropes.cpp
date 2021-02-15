#include<bits/stdc++.h>
using namespace std;
int n, k;
vector<int> a;
bool good(double x)
{
	int s = 0;
	for (int i = 0; i < n; i++) s += floor(a[i] / x);
	return s >= k;
}
int main()
{
	ios_base::sync_with_stdio(false);
	cin >> n >> k;
	a.resize(n);
	for (int i = 0; i < n; i++) cin >> a[i];
	double l = 0, r = 1e8;
	for (int t = 0; t < 100; t++)
	{
		double m = (l + r) / 2;
		if (good(m)) l = m;
			else r = m;
	}
	cout << setprecision(20) << l << endl;
	return 0;
}
