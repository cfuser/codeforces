#include<bits/stdc++.h>
using namespace std;

const int N = 2e5+5;

struct item
{
	long long num11, num12, num21, num22;
};
item st[N][20];

void read(int &x)
{
	x=0;char c=getchar();
	while(c<'0' || c>'9') c=getchar();
	while(c>='0' && c<='9'){
		x=x*10+c-'0';
		c=getchar();
	}
}
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
int main()
{
	int module, n, m;
	read(module);read(n);read(m);
	//scanf("%d%d%d",&module, &n, &m);
	//memset(st,0,sizeof(item)); 
	for (int i = 0; i < n; i++)
	{
		int x;
		read(x);st[i][0].num11 = (x % module + module) % module;
		read(x);st[i][0].num12 = (x % module + module) % module;
		read(x);st[i][0].num21 = (x % module + module) % module;
		read(x);st[i][0].num22 = (x % module + module) % module;
	}
	int len = 2, k = 1;
	while (len <= n)
	{
		for (int i = 0; i < n - len + 1; i++)
		st[i][k] = merge(st[i][k - 1], st[i + len / 2][k - 1], module);
		len <<= 1;
		k++;
	}
	/*
	for (int k = 0;(1<<k)<=n;k++)
	{
		for (int i = 0; i < n-(1<<k)+1; i++) cout<<st[i][0].num11<<" "<<st[i][0].num12<<" "<<st[i][0].num21<<" "<<st[i][0].num22<<endl;
		cout<<endl;
	}
	*/
	for (int i = 0; i < m; i++)
	{
		int l,r;
		read(l);read(r);
		l--;r--;
		int delta = r - l + 1, k = 0, len = 1;
		item ans = {1,0,0,1};
		while (delta)
		{
			if (delta % 2 == 1)
			{
				ans = merge(ans, st[l][k], module);
				l += len;
			}
			k++;
			len <<= 1;
			delta >>= 1; 
			//cout << ans.num11 << " " << ans.num12 << " " << ans.num21 << " " << ans.num22 <<endl;
		}
		//cout << ans.num11 << " " << ans.num12 << endl << ans.num21 << " " << ans.num22 << endl << endl;
		printf("%lld %lld\n%lld %lld\n\n", ans.num11, ans.num12, ans.num21, ans.num22);
	}
	return 0;
	
} 
