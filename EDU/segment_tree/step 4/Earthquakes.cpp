#include<bits/stdc++.h>
using namespace std;
struct item
{
	int min, number;
};
struct segtree
{
	int size;
	vector<int> values;
	int NEUTRAL_ELEMENT = INT_MAX;
	void init(int n)
	{
		size = 1;
		while (size < n) size *= 2;
		values.assign(2 * size, 0LL);
	}
	void build(vector<int> &a, int x, int lx, int rx)
	{
		if (rx - lx == 1)
		{
			if (lx < (int)a.size()) values[x] = a[lx];
			else values[x] = INT_MAX;
			return ;
		}
		int mid = (lx + rx) / 2;
		build(a, 2 * x + 1, lx, mid);
		build(a, 2 * x + 2, mid, rx);
		values[x] = min(values[2 * x + 1], values[2 * x + 2]);
	}
	void build(vector<int> &a)
	{
		build(a, 0, 0, size);
	}
	void set(int i, int v, int x, int lx, int rx)
	{
		if (rx - lx == 1)
		{
			values[ x ] = v;
			return ;
		}
		int mid = (lx + rx) / 2;
		if (i < mid) set(i, v, 2 * x + 1, lx, mid);
		else if (i >= mid) set(i, v, 2 * x + 2, mid, rx);
		values[x] = min(values[2 * x + 1], values[2 * x + 2]);
	}
	void set(int i, int v)
	{
		set(i, v, 0, 0, size);	
	}
	int destroy(int l, int r, int power, int x, int lx, int rx)
	{
		if (lx >= r || rx <= l) return 0;
		if (rx - lx == 1)
		{
			if (values[x] <= power)
			{
				set(lx, INT_MAX);
				return 1; 
			}
		}
		int mid=(lx + rx)/2;
		if (values[x] <= power)
		{
			int s1 = (values[2 * x + 1] <= power)?destroy(l, r, power, 2 * x + 1, lx, mid):0;
			int s2 = (values[2 * x + 2] <= power)?destroy(l, r, power, 2 * x + 2, mid, rx):0;
			return s1 + s2;
		}
		return 0;
	}
	int destroy(int l, int r, int power)
	{
		return destroy(l, r, power, 0, 0, size);
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
	a.assign(n,INT_MAX);
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
			int l, r, power;
			cin >> l >> r >> power;
			cout << st.destroy(l, r, power) << endl;
		}
	}
}
