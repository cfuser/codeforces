#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
int n, k;
vector<int> a;
vector<double> intersect(vector<double> boundary, vector<double> bound_i)
{
	return vector<double> {max(boundary[0], bound_i[0]), min(boundary[1], bound_i[1])};
}
bool good(long long x)
{
	int num = 1;
	long long pos = a[0];
	for (int i = 1; i < n; i++)
	{
		if (a[i] - pos >= x)
		{
			pos = a[i];
			num += 1;
		}
	}
	return num >= k;
}
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> k;
	a.resize(n);
	for (int i = 0; i < n; i++) cin >> a[i];
	long long l = 0, r = 1;
	while (good(r)) r *= 2;
	while (r - l > 1)
	{
		long long m = (l + r) / 2;
		if (good(m)) l = m;
		else r = m;
	}
	cout << l << endl;
	return 0;
}


