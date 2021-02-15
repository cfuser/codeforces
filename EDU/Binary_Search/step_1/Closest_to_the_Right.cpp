#include<bits/stdc++.h>
using namespace std;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, k;
	cin >> n >> k;
	vector<int> a(n);
	for (int i = 0; i < n; i++) cin >> a[i];
	for (int i = 0; i < k; i++)
	{
		int x;
		cin >> x;
		int l = -1, r = n; // a[l] < x, a[r] >= x
		bool ok = false;
		while (r > l + 1)
		{
			int m = (l + r) / 2;
			if (a[m] < x) l = m;
				else if (a[m] >= x) r = m;
		}
		cout << r + 1 << endl;
	}
	return 0;
}


