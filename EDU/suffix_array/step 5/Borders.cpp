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
		pos[i] ++;
	}
	p = p_new;
	return ;
}
int main()
{
	string s;
	cin >> s;
	s += '$';
	int n = s.size();
	vector<int> p(n),c(n);
	{ 
		vector<pair<char, int> > a(n);
		for (int i = 0; i < n; i++) a[i] = {s[i],i};
		sort(a.begin(),a.end());
		for (int i = 0; i < n; i++) p[i] = a[i].second;
		c[p[0]] = 0;
		for (int i = 1; i < n; i++)
			if (a[i].first == a[i-1].first) c[p[i]] = c[p[i-1]];
			else c[p[i]] = c[p[i-1]]+1;
	}
	int k = 0;
	while ((1 << k) < n)
	{
		for (int i = 0; i < n; i++) p[i] = (p[i] - (1<<k) + n) % n;
		radix_sort(p,c);
		vector<int> c_new(n);
		c_new[p[0]] = 0;
		for (int i = 1; i < n; i++)
		{
			pair<int, int> now={c[p[i]], c[(p[i] + (1 << k)) % n]};
			pair<int, int> prev={c[p[i-1]], c[(p[i-1] + (1 << k)) % n]};
			if (now==prev) c_new[p[i]] = c_new[p[i-1]];
			else c_new[p[i]] = c_new[p[i-1]]+1;
		}
		c = c_new;
		k++;
	}
	//for (int i = 0; i < n; i++) cout<< p[i] <<" ";cout << endl;
	//for (int i = 0; i < n; i++) cout<< c[i] <<" ";cout << endl;
	//int reverse_pos[n], lcp[n];
	vector<int> lcp(n);
	k = 0;
	for (int i = 0; i < n - 1; i++)
	{
		int pi = c[i],j = p[pi - 1];
		while (s[i + k] == s[j + k]) k++;
		lcp[pi] = k;
		k = max(k - 1, 0);
	}
	//for (int i = 1; i < n; i++) cout << lcp[i] << " ";cout << endl;
	long long sum = (long long)n * (n - 1) / 2;
	vector<pair<pair<long long, long long>, long long>> seq;
	for (int i = 1; i < n; i++)
	{
		int pos = lcp[i];
		int h = seq.size();
		pair<pair<long long, long long>, long long> max_pos = (h > 0)?seq[h - 1]:(pair<pair<long long, long long>, long long>){{0, 0}, 0};
		while (h > 0 && seq[h - 1].first.first >= pos)
		{
			seq.pop_back();
			h--;
		}
		pair<pair<long long, long long>, long long> pre_pos = (h > 0)?seq[h - 1]:(pair<pair<long long, long long>, long long>){{0, 0}, 0};
		seq.push_back({{pos, max_pos.first.second+1}, pre_pos.second + (max_pos.first.second - pre_pos.first.second + 1) * pos});
		h++;sum += seq[h-1].second;
	}
	cout << sum << endl;
	return 0;
}

