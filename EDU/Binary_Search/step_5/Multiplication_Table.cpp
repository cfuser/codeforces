#include<bits/stdc++.h>
using namespace std;
vector<int> a, b;
vector<int> ans;
int n;
long long k;

bool good(long long x)
{
	long long num = 0;
	for (int i = 1; i <= n; i++)
	{
		if (x > i) num += min((x - 1) / i, (long long)n);
	}
	return num <= (long long)k;
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
	//for (int i = 0; i < n; i++) cin >> a[i] >> b[i];
	long long l = 0, r = (long long)n * n + 1;
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




