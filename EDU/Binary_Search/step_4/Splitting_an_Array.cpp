#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
int n, m;
vector<int> a;
vector<double> intersect(vector<double> boundary, vector<double> bound_i)
{
	return vector<double> {max(boundary[0], bound_i[0]), min(boundary[1], bound_i[1])};
}
bool good(long long x)
{
	int num = 0;
	long long sum = 0;
	for (int i = 0; i < n; i++)
	if (a[i] > x) return false;
	else
	{
		num += 1;
		int j = i;
		while (j < n && sum + a[j] <= x)
		{
			sum += a[j];
			j += 1;
		}
		i = j - 1;
		sum = 0;
	}
	return num <= m;
}
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m;
	a.resize(n);
	for (int i = 0; i < n; i++) cin >> a[i];
	long long l = 0, r = 1;
	while (!good(r)) r *= 2;
	while (r - l > 1)
	{
		long long m = (l + r) / 2;
		if (!good(m)) l = m;
		else r = m;
	}
	cout << r << endl;
	return 0;
}


