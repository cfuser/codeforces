#include<bits/stdc++.h>
using namespace std;
vector<int> a, b;
vector<int> ans;
int n;
long long k;

bool good(long long x)
{
	long long num = 0;
	int l = 0, r = 0;
	if (a[l] + b[r] > x) return num <= k;
	while (l < n && a[l] <= x) l += 1;
	l -= 1;
	for (r = 0; r < n; r++)
	{
		while (l >= 0 && a[l] + b[r] >= x) l -= 1;
		num += l + 1;
	}
	return num <= k;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> k;
	k -= 1;
	a.resize(n);
	b.resize(n);
	for (int i = 0; i < n; i++) cin >> a[i];
	for (int i = 0; i < n; i++) cin >> b[i];
	sort(a.begin(), a.end());
	sort(b.begin(), b.end());
	long long l = 0, r = LLONG_MAX;
	//while (good(r)) r *= 2;	
	while (r > l + 1)
	{
		long long m = (l + r) / 2;
		if (good(m)) l = m;
		else r = m;
	}
	cout << l << endl;
	return 0;
}




