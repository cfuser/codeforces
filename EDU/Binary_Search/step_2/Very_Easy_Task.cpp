#include<bits/stdc++.h>
using namespace std;
int n, x, y;
bool good(long long t)
{
	return (t / x) + (t / y) >= n;
}
int main()
{
	ios_base::sync_with_stdio(false);
	cin >> n >> x >> y;
	if (x > y) swap(x, y);
	n -= 1;
	long long l = 0, r = 1; // l is bad, r is good
	while (!good(r)) r *= 2;
	if (n == 0) r = 0;
	while (r > l + 1)
	{
		long long m = (l + r) / 2;
		if (good(m)) r = m;
			else l = m;
	}
	cout << r + x << endl;
	return 0;
}
