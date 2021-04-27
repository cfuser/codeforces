#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
int vis[N];
int p, num, n;
int gcd(int x, int y)
{
	if (y % x == 0) return x;
	else return gcd(y % x, x);
}
int main()
{
	cin >> n;
	memset(vis, 0, sizeof(vis));
	p = 1;
	for (int i = 1; i < n; i++)
	if (gcd(i, n) == 1)
	{
		vis[i] = 1;
		p = (long long)p * i % n;
		num += 1;
	}
	if (p != 1)
	{
		vis[p] = 0;
		num -= 1;
	}
	cout << num << endl;
	for (int i = 1; i < n; i++)
	if (vis[i] == 1)
	{
		cout << i << " ";
	}
	cout << endl;
	return 0;
}
