#include<bits/stdc++.h>
using namespace std;
const int N = 3e5 + 5;
long long fa[N][20], a[N], c[N], depth[N];
int get_max_pow(int v)
{
	int l = 0;
	while (a[fa[v][l + 1]] != 0)
	{
		l += 1;
	}
	return l;
}
int get_top_index(int v)
{
	if (a[0] != 0) return 0; // root[v] is fixed to 0
	int pow = get_max_pow(v);
	while (pow > 0 && a[fa[v][0]] != 0)
	{
		v = fa[v][pow];
		while (a[fa[v][pow]] == 0) pow -= 1;
	}
	return v;
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0); 
	int q;
	cin >> q >> a[0] >> c[0];
	depth[0] = 0;
	for (int i = 1; i <= q; i++)
	{
		int op;
		cin >> op;
		if (op == 1)
		{
			int p;
			cin >> p >> a[i] >> c[i];
			fa[i][0] = i; fa[i][1] = p;
			depth[i] = depth[p] + 1;
			for (int j = 2, d = 2; d <= depth[i]; j++, d *= 2)
			{
				fa[i][j] = fa[fa[i][j - 1]][j - 1];
			}
		}
		else if (op == 2)
		{
			long long v, w;
			cin >> v >> w;
			long long value = 0, num = 0;
			if (a[v] != 0)
			while (w)
			{
				int index = get_top_index(v);
				if (a[index] == 0) break;
				if (w <= a[index])
				{
					num += w;
					value += w * c[index];
					a[index] -= w;
					w = 0;
				}
				else
				{
					num += a[index];
					value += a[index] * c[index];
					w -= a[index];
					a[index] = 0;
					//vis[index] = 1;
				}
			}
			cout << num << " " << value << endl;
			fflush(stdout);
		}
	}
	return 0;
}
