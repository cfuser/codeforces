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
	void build(vector<int> &a, int x, int lx, int rx)
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
	void build(vector<int> &a)
	{
		build(a, 0, 0, size);
	}
	void set(int i, int v, int x, int lx, int rx)
	{
		if (rx - lx == 1)
		{
			sums[ x ] = v;
			return ;
		}
		int mid = (lx + rx) / 2;
		if (i < mid) set(i, v, 2 * x + 1, lx, mid);
		else if (i >= mid) set(i, v, 2 * x + 2, mid, rx);
		sums[x] = sums[2 * x + 1] + sums[2 * x + 2];
	}
	void set(int i, int v)
	{
		set(i, v, 0, 0, size);	
	}
	long long sum(int l, int r, int x, int lx, int rx)
	{
		if (lx >= r || rx <= l) return 0;
		if (lx >= l && rx <= r) return sums[x];
		int mid = (lx + rx) / 2;
		long long s1 = sum(l, r, 2 * x + 1, lx, mid);
		long long s2 = sum(l, r, 2 * x + 2, mid, rx);
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
	cin >> n;
	n*=2;
	segtree st;
	st.init(n);
	vector<int> a(n),b(n),pos(n/2),ans(n/2);
	a.assign(n,0);b=a;
	pos.assign(n/2,-1);
	ans.assign(n/2,0);
	st.build(a);
	for (int i = 0; i < n; i++) {cin>>a[i];a[i]--;}
	for (int i = 0; i < n; i++)
	{
		if (pos[a[i]] == -1)
		{
			pos[a[i]] = i;
			st.set(pos[a[i]], 1);
		}
		else
		{
			st.set(pos[a[i]], 0);
			ans[a[i]] += st.sum(pos[a[i]], i);
		}
	}
	pos.assign(n / 2, -1);
	st.build(b);
	for (int i = n - 1; i >= 0; i--)
	{
		if (pos[a[i]] == -1)
		{
			pos[a[i]] = i;
			st.set(pos[a[i]], 1);
		}
		else
		{
			st.set(pos[a[i]], 0);
			ans[a[i]] += st.sum(i, pos[a[i]]);
		}
	}
	for (int i = 0; i < n/2; i++) cout << ans[i] << " ";cout << endl;
}

