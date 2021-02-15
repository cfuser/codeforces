#include<bits/stdc++.h>
using namespace std;
int w, h, n;
bool good(long long x)
{
	return (x / w) * (x / h) >= n;
}
int main()
{
	ios_base::sync_with_stdio(false);
	cin >> w >> h >> n;
	long long l = 0, r = 1;
	while (!good(r)) r *= 2;
	while (r > l + 1)
	{
		long long m = (l + r) / 2;
		if (good(m)) r = m;
			else l = m;
	}
	cout << r << endl;
	return 0;
}

