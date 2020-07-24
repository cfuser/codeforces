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
	string s1,s2,s;
	cin >> s1 >> s2;
	s = s1 + '$' + s2 + '#';
	int len1 = s1.size(), len2 = s2.size(), len = len1 + 1 + len2+1;
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
	//for (int i = 0; i < n; i++) cout<<p[i]<<" ";cout<<endl;
	//for (int i = 0; i < n; i++) cout<<c[i]<<" ";cout<<endl;
	//int reverse_pos[n],lcp[n];
	vector<int> lcp(n);
	k = 0;
	for (int i = 0; i < n - 1; i++)
	{
		int pi = c[i],j = p[pi - 1];
		while (i+k<n && j+k<n && s[i + k] == s[j + k]) k++;
		lcp[pi] = k;
		k = max(k - 1, 0);
	}
	int maxlen_pos = -1,length=0;
	for (int i = 1; i < n; i++)
	{
		if (maxlen_pos==-1 || lcp[i]>length)
			if (p[i-1]<len1 && p[i]>=len1+1) maxlen_pos=p[i-1],length=lcp[i];
			else if (p[i-1]>=len1+1 && p[i]<len1) maxlen_pos=p[i-1],length=lcp[i];
	}
	//cout<<maxlen_pos<<" ";
	if (maxlen_pos<=len1) cout<<s1.substr(maxlen_pos,length)<<endl;
	else cout<<s2.substr(maxlen_pos-len1-1,length)<<endl;
	//for (int i = 1; i < n; i++) cout<<lcp[i]<<" ";cout<<endl;
	return 0;
}


