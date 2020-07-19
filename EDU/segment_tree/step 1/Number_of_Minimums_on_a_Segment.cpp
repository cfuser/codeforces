#include<bits/stdc++.h>
using namespace std;
struct item
{
	int m, c;
};
struct segtree
{
	int size;
	vector<item> values;
	item NEUTRAL_ELEMENT = {INT_MAX, 0};
	item merge(item a,item b)
	{
		if (a.m < b.m) return a;
		else if (a.m > b.m) return b;
		else return (item){a.m,a.c+b.c};
	}
	item single(int v)
	{
		return (item){v, 1};
	}
	void init(int n)
	{
		size = 1;
		while (size < n) size *= 2;
		values.resize(2 * size);
	}
	void build(vector<int> &a, int x, int lx, int rx)
	{
		if (rx - lx == 1)
		{
			if (lx < (int)a.size()) values[x] = single(a[lx]);
			return ;
		}
		int mid = (lx + rx) / 2;
		build(a, 2 * x + 1, lx, mid);
		build(a, 2 * x + 2, mid, rx);
		values[x]=merge(values[2*x+1],values[2*x+2]);
	}
	void build(vector<int> &a)
	{
		build(a, 0, 0, size);
	}
	void set(int i, int v, int x, int lx, int rx)
	{
		if (rx - lx == 1)
		{
			values[x] = single(v);
			return ;
		}
		int mid = (lx + rx) / 2;
		if (i < mid) set(i, v, 2 * x + 1, lx, mid);
		else if (i >= mid) set(i, v, 2 * x + 2, mid, rx);
		values[x]=merge(values[2*x+1],values[2*x+2]);
	}
	void set(int i, int v)
	{
		set(i, v, 0, 0, size);	
	}
	item calc(int l, int r, int x, int lx, int rx)
	{
		if (lx >= r || rx <= l) return NEUTRAL_ELEMENT;
		if (lx >= l && rx <= r) return values[x];
		int mid = (lx + rx) / 2;
		item s1 = calc(l, r, 2 * x + 1, lx, mid);
		item s2 = calc(l, r, 2 * x + 2, mid, rx);
		return merge(s1,s2);
	}
	item calc(int l, int r)
	{
		return calc(l, r, 0, 0, size);
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
	for (int i = 0; i < n; i++) cin>>a[i];
	st.build(a);
	while (m--)
	{
		int op;
		cin >> op;
		if (op == 1)
		{
			int i, v;
			cin >> i >> v;
			st.set(i, v);
		}
		else if (op == 2)
		{
			int l,r;
			cin >> l >> r;
			item res=st.calc(l,r);
			cout << res.m << " " << res.c << endl;
		}
	}
}

