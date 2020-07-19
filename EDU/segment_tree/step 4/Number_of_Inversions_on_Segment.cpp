#include<bits/stdc++.h>
using namespace std;
struct item
{
	long long inv;
	int num[45];
};
struct segtree
{
	int size;
	vector<item> sums;
	item NEUTRAL_ELEMENT;
	void init(int n)
	{
		NEUTRAL_ELEMENT.inv = 0;
		for (int i = 0; i < 45; i++) NEUTRAL_ELEMENT.num[i] = 0;
		size = 1;
		while (size < n) size *= 2;
		sums.assign(2 * size, NEUTRAL_ELEMENT);
	}
	void build(vector<int> &a, int x, int lx, int rx)
	{
		if (rx - lx == 1)
		{
			if (lx < (int)a.size()) sums[x].num[a[lx]]++;
			return ;
		}
		int mid = (lx + rx) / 2;
		build(a, 2 * x + 1, lx, mid);
		build(a, 2 * x + 2, mid, rx);
		sums[x] = merge(sums[2 * x + 1], sums[2 * x + 2]);
	}
	void build(vector<int> &a)
	{
		build(a, 0, 0, size);
	}
	item merge(item a, item b)
	{
		item ans;
		int prev[40];prev[0] = b.num[0];
		ans.inv = a.inv + b.inv;
		for (int i = 0; i < 40; i++)
		{
			ans.num[i] = a.num[i] + b.num[i];
			if (i != 0)
			{
				ans.inv += a.num[i] * prev[i - 1];
				prev[i] = prev[i - 1] + b.num[i];
			}
		}
		return ans;
	}
	void set(int i, int pv, int v, int x, int lx, int rx)
	{
		if (rx - lx == 1)
		{
			sums[x].num[pv]--;
			sums[x].num[v]++;
			return ;
		}
		int mid = (lx + rx) / 2;
		if (i < mid) set(i, pv, v, 2 * x + 1, lx, mid);
		else if (i >= mid) set(i, pv, v, 2 * x + 2, mid, rx);
		sums[x] = merge(sums[2 * x + 1], sums[2 * x + 2]);
	}
	void set(int i, int pv, int v)
	{
		set(i, pv, v, 0, 0, size);	
	}
	item sum(int l, int r, int x, int lx, int rx)
	{
		if (lx >= r || rx <= l) return NEUTRAL_ELEMENT;
		if (lx >= l && rx <= r) return sums[x];
		int mid = (lx + rx) / 2;
		item s1 = sum(l, r, 2 * x + 1, lx, mid);
		item s2 = sum(l, r, 2 * x + 2, mid, rx);
		item s3 = merge(s1, s2);
		return s3;
	}
	item sum(int l, int r)
	{
		return sum(l, r, 0, 0, size);
	}
};
int main()
{
	ios::sync_with_stdio(false);
	int n,m;
	cin >> n >> m;
	segtree st;
	st.init(n);
	vector<int> a(n);
	for (int i = 0; i < n; i++)
	{
		cin>>a[i];
		a[i]--;
	}
	st.build(a);
	while (m--)
	{
		int op;
		cin >> op;
		if (op == 2)
		{
			int i, v;
			cin >> i >> v;
			st.set(i - 1, a[i - 1], v - 1);
			a[i - 1] = v - 1;
		}
		else if (op == 1)
		{
			int l,r;
			cin >> l >> r;
			cout << st.sum(l - 1, r).inv << endl;
		}
	}
}

