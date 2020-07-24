#include<bits/stdc++.h>
using namespace std;
const int M = 25;
void radix_sort(vector<int> &p,vector<int> &c)
{
	int n = p.size();
	vector<int> cnt(n);
	for (auto x: c) cnt[x]++;
	vector<int> p_new(n); 
	vector<int> pos(n);
	pos[0] = 0;
	for (int i = 1; i < n; i++) pos[i] = pos[i - 1] + cnt[i - 1];
	for (auto x: p)
	{
		int i = c[x];
		p_new[pos[i]] = x;
		pos[i]++;
	}
	p = p_new;
}
int query(vector<int> &c, int height[][M],int i,int j)
{
	int l = min(c[i], c[j]), r = c[i] + c[j] - l;
	int cnt = log2(r - l), len = 1 << cnt;
	return min(height[l + 1][cnt], height[r - len + 1][cnt]);
}
int main()
{
	string s;
	cin >> s;
	s += '$';
	int n = s.size();
	int height[n+5][M];
	vector<int> p(n),c(n);
	{ 
		vector<pair<char, int> > a(n);
		for (int i = 0; i < n; i++) a[i] = {s[i], i};
		sort(a.begin(),a.end());
		for (int i = 0; i < n; i++) p[i] = a[i].second;
		c[p[0]] = 0;
		for (int i = 1; i < n; i++)
			if (a[i].first == a[i - 1].first) c[p[i]] = c[p[i - 1]];
			else c[p[i]] = c[p[i - 1]]+1;
	}
	int k = 0;
	while ((1 << k) < n)
	{
		for (int i = 0; i < n; i++) p[i] = (p[i] - (1 << k) + n) % n;
		radix_sort(p, c);
		vector<int> c_new(n);
		c_new[p[0]] = 0;
		for (int i = 1; i < n; i++)
		{
			pair<int, int> now = {c[p[i]], c[(p[i] + (1 << k)) % n]};
			pair<int, int> prev = {c[p[i - 1]], c[(p[i - 1] + (1 << k)) % n]};
			if (now == prev) c_new[p[i]] = c_new[p[i-1]];
			else c_new[p[i]] = c_new[p[i - 1]]+1;
		}
		c = c_new;
		k++;
	}
	//for (int i = 0; i < n; i++) cout<<p[i]<<" ";cout<<endl;
	//for (int i = 0; i < n; i++) cout<<c[i]<<" ";cout<<endl;
	//int reverse_pos[n],lcp[n];
	vector<int> lcp(n);
	k = 0;lcp[0] = 0;
	for (int i = 0; i < n - 1; i++)
	{
		int pi = c[i],j = p[pi - 1];
		while (s[i + k] == s[j + k]) k++;
		lcp[pi] = k;
		k = max(k - 1, 0);
	}
	//for (int i = 1; i < n; i++) cout<<lcp[i]<<" ";cout<<endl;
	for (int i = 0; i < n; i++) height[i][0] = lcp[i];
	for (int j = 1, len = 2; len < n; j++, len <<= 1)
	{
		for (int i = 0; i < n - len + 1; i++)
		height[i][j] = min(height[i][j - 1], height[i + len / 2][j - 1]);
	}
	int ans = 0;
	for (int i = 1; i < n; i++)
	{
		for (int j = 0; j + i < n; j += i)
		{
			int len_K = query(c, height, j, j + i);
			int k = j - (i - len_K % i);
			int num = len_K / i + 1;
			if (k >= 0 && query(c, height, k, k + i) >= i) num++;
			ans = max(num, ans);
		}
	}
	cout << ans << endl;
	return 0;
}

