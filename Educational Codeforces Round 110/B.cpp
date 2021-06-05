#include<bits/stdc++.h>
using namespace std;
int gcd(int x, int y)
{
	if (x > y) swap(x, y);
	if (y % x == 0) return x;
	else return gcd(y % x, x);
}
int main()
{
	int T;
	cin >> T;
	while (T--)
	{
		int n, ans = 0;
		cin >> n;
		vector<int> odd, even, num(n);
		for (int i = 0; i < n; i++)
		{
			int x;
			cin >> x;
			if (x % 2) odd.push_back(x);
			else even.push_back(x);
		}
		for (int i = 0; i < even.size(); i++) num[i] = even[i];
		for (int i = 0; i < odd.size(); i++) num[i + even.size()] = odd[i];
		for (int i = 0; i < n; i++)
			for (int j = i + 1; j < n; j++)
			if (gcd(num[i], 2 * num[j]) > 1) ans += 1;
		cout << ans << endl;
	}
	return 0;
}
