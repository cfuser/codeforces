#include<bits/stdc++.h>
using namespace std;
const int N = 35e3+ 5;
int a[N], pre[N], dp[N];
struct SegmentTree
{
	int size;
	vector<int> minn, add;
	void apply(int u, int v)
	{
		add[v] += add[u];
	}
	void push_down(int x, int lx, int rx)
	{
		if (rx - lx != 1)
		{
			apply(x, 2 * x + 1);
			apply(x, 2 * x + 2);
		}
		minn[x] += add[x];
		add[x] = 0;
	}
	void modify(int l, int r, int Add, int x, int lx, int rx)
	{
		if (l >= rx || r <= lx) return ;
		push_down(x, lx, rx);
		if (lx >= l && rx <= r)
		{
			add[x] += Add;
			return ;
		}
		int mid = (lx + rx) / 2;
		modify(l, r, Add, 2 * x + 1, lx, mid);
		modify(l, r, Add, 2 * x + 2, mid, rx);
		minn[x] = min(minn[2 * x + 1] + add[2 * x + 1], minn[2 * x + 2] + add[2 * x + 2]);
	}
	void modify(int l, int r, int Add)
	{
		modify(l, r, Add, 0, 0, size);
	}
	int get_Min(int l, int r, int x, int lx, int rx)
	{
		if (l >= rx || r <= lx) return INT_MAX / 2;
		push_down(x, lx, rx);
		if (lx >= l && rx <= r) return minn[x];
		int mid = (lx + rx) / 2;
		int min_l = get_Min(l, r, 2 * x + 1, lx, mid);
		int min_r = get_Min(l, r, 2 * x + 2, mid, rx);
		return min(min_l, min_r);
	}
	int get_Min(int l, int r)
	{
		return get_Min(l, r, 0, 0, size);
	}
	void build(int x, int lx, int rx, int n, int *a)
	{
		if (rx - lx == 1)
		{
			//add[x] = 0;
			minn[x] = a[lx];
			return ;
		}
		int mid = (lx + rx) / 2;
		build(2 * x + 1, lx, mid, n, a);
		build(2 * x + 2, mid, rx, n, a);
		minn[x] = min(minn[2 * x + 1], minn[2 * x + 2]);
		return ;
	}
	void build(int n, int *a)
	{
		build(0, 0, size, n, a);
	}
	void init(int n)
	{
		size = n;
		minn.assign(4 * size, 0);
		add.assign(4 * size, 0);
	}
};
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, K;
	cin >> n >> K;
	SegmentTree st;
	for (int i = 0; i < n; i++) cin >> a[i];
	st.init(n);
	memset(dp, 0, sizeof(dp));
	for (int i = 1; i <= n; i++) pre[i] = -1;
	pre[a[0]] = 0;
	for (int i = 1; i < n; i++)
	{
		if (pre[a[i]] != -1) dp[i] = dp[i - 1] + i - pre[a[i]];
		else dp[i] = dp[i - 1];
		pre[a[i]] = i;
	}
	st.build(n, dp);
	for (int k = 1; k < K; k++)
	{
		for (int i = 1; i <= n; i++) pre[i] = -1; 
		memset(dp, 0, sizeof(dp));
		for (int i = 0; i < n; i++)
		{
			if (pre[a[i]] != -1)
			st.modify(0, pre[a[i]], i - pre[a[i]]);
			dp[i] = i <= k ? 0 : st.get_Min(0, i);
			pre[a[i]] = i;
		}
		st.init(n);
		st.build(n, dp);
	}
	cout << dp[n - 1] << endl;
	return 0;
}
