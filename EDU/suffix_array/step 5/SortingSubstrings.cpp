#include<bits/stdc++.h>
using namespace std;
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
int main()
{
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
	string s;
	cin >> s;
	s += ' ';
	int n = s.size();
	vector<int> p(n), c(n);
	{ 
		vector<pair<char, int> > a(n);
		for (int i = 0; i < n; i++) a[i] = {s[i], i};
		sort(a.begin(), a.end());
		for (int i = 0; i < n; i++) p[i] = a[i].second;
		c[p[0]] = 0;
		for (int i = 1; i < n; i++)
			if (a[i].first == a[i-1].first) c[p[i]] = c[p[i - 1]];
			else c[p[i]] = c[p[i - 1]] + 1;
	}
	int k = 0;
	while ((1 << k) < n)
	{
		for (int i = 0; i < n; i++) p[i] = (p[i] - (1 << k) + n) % n;
		radix_sort(p,c);
		vector<int> c_new(n);
		c_new[p[0]] = 0;
		for (int i = 1; i < n; i++)
		{
			pair<int, int> now = {c[p[i]], c[(p[i] + (1 << k)) % n]};
			pair<int, int> prev = {c[p[i - 1]], c[(p[i - 1] + (1 << k)) % n]};
			if (now == prev) c_new[p[i]] = c_new[p[i - 1]];
			else c_new[p[i]] = c_new[p[i - 1]] + 1;
		}
		c = c_new;
		k++;
	}
	//for (int i = 0; i < n; i++) cout<<p[i]<<" ";cout<<endl;
	//for (int i = 0; i < n; i++) cout<<c[i]<<" ";cout<<endl;
	//int reverse_pos[n],lcp[n];
	vector<int> lcp(n);
	k = 0;
	for (int i = 0; i < n - 1; i++)
	{
		int pi = c[i],j = p[pi - 1];
		while (s[i + k] == s[j + k]) k++;
		lcp[pi] = k;
		k = max(k - 1, 0);
	}
	//for (int i = 1; i < n; i++) cout<<lcp[i]<<" ";cout<<endl;
	int m;
	cin >> m;
	vector<pair<pair<int, int>, pair<int, int>>> lr(m);
	for (int i = 0; i < m; i++)
	{
		cin >> lr[i].second.first >> lr[i].second.second;
		lr[i].first.first = lr[i].second.first - 1;
		lr[i].first.second = lr[i].second.second - 1;
	}
	sort(lr.begin(), lr.end()); 
	vector<int> pos(n + 5), cnt(n + 5);
	for (int i = 0; i < m; i++) cnt[lr[i].first.first]++;
	pos[0] = 0;
	for (int i = 1; i < n; i++) pos[i] = pos[i-1] + cnt[i-1];
	vector<pair<int, int>> f(n+5);
	//f[1]={p[1],lcp[1]};int h=1;
	int h = 0;
	f[0]={0,0};
	for (int i = 1; i < n; i++)
	{
		int hh = h;
		while (h > 0 && f[h].second > lcp[i]) h--;
		if (lcp[i] != 0) {h++;f[h] = {hh==(h-1)?p[i]:f[h].first, lcp[i]};}
		//for (int j=1;j<=h;j++) cout<<f[j].second<<" ";cout<<endl;
		int k = pos[p[i]];
		while (lr[k].first.first == p[i])
		if (lr[k].first.second - lr[k].first.first + 1 <= f[h].second)
		{
			/*int r = h, delta = lr[k].first.second - lr[k].first.first + 1;
			while (r > 0 && f[r].second >= delta) r--;r++;*/
			
			int l = 1, r = h, mid = (l + r)/2, delta = lr[k].first.second - lr[k].first.first + 1;
			while (l <= r)
			{
				if (f[mid].second >= delta) r = mid - 1;
				else l = mid + 1;
				mid = (l + r) / 2;
			}
			r++;
			if (r <= h)
			{
				lr[k].first.second -= (lr[k].first.first - p[c[f[r].first] - 1]);
				lr[k].first.first -= (lr[k].first.first - p[c[f[r].first] - 1]);
			}
			k++;
		}
		else break;
	}
	//for (int i = 0;i<m;i++) cout<<lr[i].first.first<<" "<<lr[i].first.second<<" "<<lr[i].second.first<<" "<<lr[i].second.second<<endl;
	sort(lr.begin(), lr.end());
	//for (int i = 0;i<m;i++) cout<<lr[i].first.first<<" "<<lr[i].first.second<<" "<<lr[i].second.first<<" "<<lr[i].second.second<<endl;
	pos.assign(n, 0);cnt.assign(n, 0);//pos.clear();cnt.clear();
	for (int i = 0; i < m; i++) cnt[lr[i].first.first]++;
	pos[0] = 0;
	for (int i = 1; i < n; i++) pos[i] = pos[i - 1] + cnt[i - 1];
	for (int i = 1; i < n; i++)
	{
		int j = pos[p[i]];
		while (j<m && lr[j].first.first == p[i])
		{
			cout << lr[j].second.first << " " << lr[j].second.second << endl;
			j++;
		}
	}
	//for (int i = 0; i < m; i++) cout<<lr[i].first.first<<" "<<lr[i].first.second<<endl;
	fclose(stdin);fclose(stdout);
	return 0;
}

