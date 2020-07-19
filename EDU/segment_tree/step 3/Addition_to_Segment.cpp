#include<bits/stdc++.h>
using namespace std;
struct segtree
{
	int size;
	vector<long long> sums;
	void init(int n)
	{
		size = 1;
		while (size < n) size *= 2;
		sums.assign(2 * size, 0LL);
	}
	void build(vector<long long> &a, int x, int lx, int rx)
	{
		if (rx - lx == 1)
		{
			if (lx < (int)a.size()) sums[x] = a[lx];
			return ;
		}
		int mid = (lx + rx) / 2;
		build(a, 2 * x + 1, lx, mid);
		build(a, 2 * x + 2, mid, rx);
		sums[x] = sums[2 * x + 1] + sums[2 * x + 2];
	}
	void build(vector<long long> &a)
	{
		build(a, 0, 0, size);
	}
	void set(int i, long long v, int x, int lx, int rx)
	{
		if (rx - lx == 1)
		{
			sums[x] = (long long)v;
			return ;
		}
		int mid = (lx + rx) / 2;
		if (i < mid) set(i, v, 2 * x + 1, lx, mid);
		else if (i >= mid) set(i, v, 2 * x + 2, mid, rx);
		sums[x] = sums[2 * x + 1] + sums[2 * x + 2];
	}
	void set(int i, long long v)
	{
		set(i, v, 0, 0, size);	
	}
	long long sum(int l, int r, int x, int lx, int rx)
	{
		if (lx >= r || rx <= l) return 0;
		if (lx >= l && rx <= r) return sums[x];
		int mid = (lx + rx) / 2;
		//cout<<x<<" "<<lx<<" "<<rx<<endl;
		long long s1 = (long long)sum(l, r, 2 * x + 1, lx, mid);
		long long s2 = (long long)sum(l, r, 2 * x + 2, mid, rx);
		return s1 + s2;
	}
	long long sum(int l, int r)
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
	n++;
	st.init(n);
	vector<long long> a(n);
	a.assign(n, 0LL);
	st.build(a);
	while (m--)
	{
		int op;
		cin >> op;
		if (op == 1)
		{
			int l, r;
			long long v;
			cin >> l >> r >> v;
			a[l] += v;st.set(l, a[l]);
			a[r] -= v;st.set(r, a[r]);
		}
		else if (op == 2)
		{
			int i;
			cin >> i;
			cout << st.sum(0, i + 1) << endl;
		}
	}
}

