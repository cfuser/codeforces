#include<bits/stdc++.h>
using namespace std;
const int N = 3e5 + 5;
int a[N], ans[N], num[N];
int unit;
vector<vector<int> > query;
bool cmp(const vector<int> &a, const vector<int> &b)
{
	return a[0] / unit < b[0] / unit || a[0] / unit == b[0] / unit && a[1] < b[1];
}
bool work(int x, int y)
{
	return (x + 1) / 2 >= y;
}
int getAns(int length, int num)
{
	if (work(length, num)) return 1;
	int l = 1, r = num, mid = (l + r) / 2;
	while (l < r)
	{
		if (work(length - mid + 1, num - mid + 1))
		{
			r = mid;
		}
		else
		{
			l = mid + 1;
		}
		mid = (l + r) / 2;
	}
	return r;
}
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, q;
	cin >> n >> q;
	//query.resize(q);
	for (int i = 0; i < n; i++) cin >> a[i];
	unit = sqrt(n);
	for (int i = 0; i < q; i++)
	{
		int l, r;
		cin >> l >> r;
		query.push_back(vector<int>({l - 1, r - 1, i}));// = {l, r, i};
	}
	sort(query.begin(), query.end(), cmp);
	memset(num, 0, sizeof(num));
	int maxm = 0;
	for (int index = 0; index < q; index++)
	{
		int l = query[index][0], r = query[index][1], group = l / unit;
		while (index < q && group == query[index][1] / unit)
		{
			l = query[index][0], r = query[index][1];
			maxm = 0;
			for (int i = l; i <= r; i++)
			{
				num[a[i]]++;
				maxm = max(maxm, num[a[i]]);
			}
			ans[query[index][2]] = getAns(r - l + 1, maxm);
			for (int i = l; i <= r; i++)
			{
				num[a[i]]--;
			}
			index += 1;
		}
		if (index >= q) break;
		l = query[index][0], r = query[index][1];
		int h = l / unit * unit + unit - 1, t = h + 1;
		maxm = 0;
		while (index < q && query[index][0] / unit == group)
		{
			l = query[index][0], r = query[index][1];
			for (int i = t; i <= r; i++)
			{
				num[a[i]]++;
				maxm = max(maxm, num[a[i]]);
			}
			int tempMax = maxm;
			for (int i = l; i <= h; i++)
			{
				num[a[i]]++;
				tempMax = max(tempMax, num[a[i]]);
			}
			ans[query[index][2]] = getAns(r - l + 1, tempMax);
			for (int i = l; i <= h; i++)
			{
				num[a[i]]--;
			}
			index += 1;
			t = r + 1;
		}
		t = h + 1;
		for (int i = t; i <= r; i++)
		{
			num[a[i]]--;
		}
		index -= 1;
	}
	for (int i = 0; i < q; i++) cout << ans[i] << endl;
	return 0;
}
