#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
struct item
{
	long long num11, num12, num21, num22;
};
item values[4*N];
item a[N];
struct segtree
{
	int size;
	item NEUTRAL_ELEMENT = {1,0,0,1};
	item merge(item &a, item &b, int module)
	{
		long long x1 = (a.num11 + a.num22) % module * ((b.num11 + b.num22) % module) % module,
		x2 = (a.num21 + a.num22) % module * b.num11 % module,
		x3 = a.num11 * ((b.num12 - b.num22) % module) % module,
		x4 = a.num22 * ((b.num21 - b.num11) % module) % module,
		x5 = (a.num11 + a.num12) % module * b.num22 % module,
		x6 = (a.num21 - a.num11) % module * ((b.num11 + b.num12) % module) % module,
		x7 = (a.num12 - a.num22) % module * ((b.num21 + b.num22) % module	) % module;
		return {((x1 + x4 - x5 + x7) %module + module) % module,
				((x3 + x5) % module + module) % module,
				((x2 + x4) % module + module) % module,
				((x1 + x3 - x2 + x6) % module + module) % module};
		/*
		return {(a.num11 * b.num11 % module + a.num12 * b.num21 % module) % module,
		(a.num11 * b.num12 % module + a.num12 * b.num22 % module) % module,
		(a.num21 * b.num11 % module + a.num22 * b.num21 % module) % module,
		(a.num21 * b.num12 % module + a.num22 * b.num22 % module) % module
		};
		*/
	}
	item single(item &v)
	{
		return {v.num11,v.num12,v.num21,v.num22};
	}
	void init(int n)
	{
		size = 1;
		while (size < n) size *= 2;
		//values.resize(2 * size);
	}
	void build(int n, int x, int lx, int rx, int module)
	{
		if (rx - lx == 1)
		{
			if (lx < n) values[x] = single(a[lx]);
			else values[x] = NEUTRAL_ELEMENT;
			return ;
		}
		int mid = (lx + rx) / 2;
		build(n, 2 * x + 1, lx, mid, module);
		build(n, 2 * x + 2, mid, rx, module);
		values[x] = merge(values[2 * x + 1], values[2 * x + 2], module);
	}
	void build(int n, int module)
	{
		build(n, 0, 0, size, module);
	}
	void set(int i, item v, int x, int lx, int rx, int module)
	{
		if (rx - lx == 1)
		{
			values[x] = single(v);
			return ;
		}
		int mid = (lx + rx) / 2;
		if (i < mid) set(i, v, 2 * x + 1, lx, mid, module);
		else if (i >= mid) set(i, v, 2 * x + 2, mid, rx, module);
		values[x] = merge(values[2 * x + 1], values[2 * x + 2], module);
	}
	void set(int i, item v,int module)
	{
		set(i, v, 0, 0, size, module);
	}
	item calc(int l, int r, int x, int lx, int rx, int module)
	{
		if (lx >= r || rx <= l) return NEUTRAL_ELEMENT;
		if (lx >= l && rx <= r) return values[x];
		int mid = (lx + rx) / 2;
		item s1 = calc(l, r, 2 * x + 1, lx, mid, module);
		item s2 = calc(l, r, 2 * x + 2, mid, rx, module);
		return merge(s1, s2, module);
	}
	item calc(int l, int r, int module)
	{
		return calc(l, r, 0, 0, size, module);
	}
};
void read(int &x)
{
	x=0;char c=getchar();
	while(c<'0' || c>'9') c=getchar();
	while(c>='0' && c<='9'){
		x=x*10+c-'0';
		c=getchar();
	}
}
int main()
{
	//ios::sync_with_stdio(false);
	int module, n, m;
	read(module);read(n);read(m);
	//scanf("%d%d%d", &module, &n, &m);
	//cin >> module >> n >> m;
	segtree st;
	st.init(n);

	for (int i = 0; i < n; i++)
	{
		//scanf("%d%d%d%d",&a[i].num11,&a[i].num12,&a[i].num21,&a[i].num22);
		//cin >> a[i].num11 >> a[i].num12 >> a[i].num21 >> a[i].num22;
		int x;
		read(x);a[i].num11 = x;
		read(x);a[i].num12 = x;
		read(x);a[i].num21 = x;
		read(x);a[i].num22 = x;
		a[i].num11 = (a[i].num11 % module + module) % module;
		a[i].num12 = (a[i].num12 % module + module) % module;
		a[i].num21 = (a[i].num21 % module + module) % module;
		a[i].num22 = (a[i].num22 % module + module) % module;
	}
	st.build(n, module);
	while (m--)
	{
		int l, r;
		read(l);read(r);
		//scanf("%d%d",&l,&r);
		//cin >> l >> r;
		item ans = st.calc(l - 1, r, module);
		cout << ans.num11 << " " << ans.num12 << endl << ans.num21 << " " << ans.num22 << endl << endl;
	}
}

