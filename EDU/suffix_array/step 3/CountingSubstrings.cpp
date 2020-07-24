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
int SearchLeft(string &s, vector<int> &p, string &str,int pos)
{
	int n = s.size() - 1, l = 1, r = pos, mid = (l + r) / 2, len=str.size();
	//cout<<n<<endl;
	while (l < r)
	{
		string cutString=s.substr(p[mid],min(n-p[mid]+1,(int)str.size()));
		if (str>cutString) l=mid+1; else r=mid;
		
		/*int i;
		for (i = 0; i < len; i++)
		if (str[i] != s[i + p[mid]]) break;
		if (i == len) return true;
		else if (str[i] > s[i + p[mid]]) l = mid + 1;
		else if (str[i] < s[i + p[mid]]) r = mid - 1;*/ 
		mid = (l + r) / 2;
		//cout<<l<<" "<<mid<<" "<<r<<" "<<p[mid]<<" "<<endl;
	}
	return mid;
}
int SearchRight(string &s, vector<int> &p, string &str,int pos)
{
	int n = s.size() - 1, l = pos, r = n, mid = (l + r + 1) / 2, len=str.size();
	//cout<<n<<endl;
	while (l < r)
	{
		string cutString=s.substr(p[mid],min(n-p[mid]+1,(int)str.size()));
		if (str<cutString) r=mid-1; else l=mid;
		
		/*int i;
		for (i = 0; i < len; i++)
		if (str[i] != s[i + p[mid]]) break;
		if (i == len) return true;
		else if (str[i] > s[i + p[mid]]) l = mid + 1;
		else if (str[i] < s[i + p[mid]]) r = mid - 1;*/ 
		mid = (l + r + 1) / 2;
		//cout<<l<<" "<<mid<<" "<<r<<" "<<p[mid]<<" "<<endl;
	}
	return mid;
}
int SearchString(string &s, vector<int> &p, string &str)
{
	int n = s.size() - 1, l = 1, r = n, mid = (l + r) / 2, len=str.size();
	//cout<<n<<endl;
	while (l <= r)
	{
		string cutString=s.substr(p[mid],min(n-p[mid]+1,(int)str.size()));
		if (str==cutString) return mid;
		else if (str>cutString) l=mid+1;
		else r=mid-1;
		
		/*int i;
		for (i = 0; i < len; i++)
		if (str[i] != s[i + p[mid]]) break;
		if (i == len) return true;
		else if (str[i] > s[i + p[mid]]) l = mid + 1;
		else if (str[i] < s[i + p[mid]]) r = mid - 1;*/ 
		mid = (l + r) / 2;
		//cout<<l<<" "<<mid<<" "<<r<<" "<<p[mid]<<" "<<endl;
	}
	return 0;
}
int main()
{
	string s;
	cin >> s;
	s += '$';
	int n = s.size();
	vector<int> p(n),c(n);
	{ 
		vector<pair<char, int>> a(n);
		for (int i = 0; i < n; i++) a[i] = {s[i],i};
		sort(a.begin(), a.end());
		for (int i = 0; i < n; i++) p[i] = a[i].second;
		c[p[0]] = 0;
		for (int i = 1; i < n; i++)
			if (a[i].first == a[i-1].first) c[p[i]] = c[p[i-1]];
			else c[p[i]] = c[p[i-1]]+1;
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
			pair<int, int> prev = {c[p[i-1]], c[(p[i-1] + (1 << k)) % n]};
			if (now == prev) c_new[p[i]] = c_new[p[i-1]];
			else c_new[p[i]] = c_new[p[i-1]]+1;
		}
		c = c_new;
		k++;
	}
	//for (int i = 0; i < n; i++) cout<<p[i]<<" ";cout<<endl;
	int query;
	cin>>query;
	string str;
	while (query--)
	{
		cin>>str;
		int pos=SearchString(s,p,str);
		if (pos == 0) cout<<0<<endl;
		else
		{
			int l=SearchLeft(s,p,str,pos);
			int r=SearchRight(s,p,str,pos);
			cout<<r-l+1<<endl;
		}
	}
	return 0;
}
