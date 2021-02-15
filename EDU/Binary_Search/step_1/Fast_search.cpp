#include<bits/stdc++.h>
using namespace std;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, k;
	cin >> n;
	vector<int> a(n + 2);
	a[0] = INT_MIN; a[n + 1] = INT_MAX;
	for (int i = 1; i <= n; i++) cin >> a[i];
	sort(a.begin(), a.end());
	cin >> k;
	/*vector<vector<int>> q;
	for (int i = 0; i < k; i++)
	{
		int l, r;
		cin >> l >> r;
		q.push_back({l, r});
	}*/
	for (int i = 0; i < k; i++)
	{
		int x, y, bound_l, bound_r;
		cin >> x >> y;
		x -= 1; y += 1;
		int l = 0, r = n + 1; // a[l] <= x, a[r] > x
		while (r > l + 1)
		{
			int m = (l + r) / 2;
			if (a[m] <= x) l = m;
				else if (a[m] > x) r = m;
		}
		//if (a[l + 1] == x + 1) l += 1;
		bound_l = l + 1;
		
		l = 0, r = n + 1;
		while (r > l + 1)
		{
			int m = (l + r) / 2;
			if (a[m] < y) l = m;
				else if (a[m] >= y) r = m;
		}
		//if (a[r - 1] == y - 1) r -= 1;
		bound_r = r - 1;
		
		//cout << bound_l << " " << a[bound_l] << " " << bound_r << " " << a[bound_r] << endl;
		cout << bound_r - bound_l + 1 << " ";
	}
	cout << endl;
	return 0;
}


