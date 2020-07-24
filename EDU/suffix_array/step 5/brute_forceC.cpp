#include<bits/stdc++.h>
using namespace std;
int main()
{
	freopen("in.txt","r",stdin);
	freopen("brute.txt","w",stdout);
	string s;
	int m;
	cin >> s;
	cin >> m;
	vector<pair<string, pair<int,int>>> sub(m);
	sub.assign(m,{"",{0,0}});
	for (int i = 0; i < m; i++)
	{
		int l, r;
		cin >> l >> r;
		sub[i].first=s.substr(l - 1, r - l + 1);
		sub[i].second.first = l;
		sub[i].second.second = r;
	}
	sort(sub.begin(),sub.end());
	for (int i = 0; i < m; i++) cout << sub[i].second.first << " " << sub[i].second.second << endl;
	fclose(stdin);fclose(stdout);
	return 0;
}
