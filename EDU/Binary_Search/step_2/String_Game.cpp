#include<bits/stdc++.h>
using namespace std;
string str_t, str_p;
int len, len_p;
vector<int> a;
bool good(int x)
{
	string str = str_t;
	for (int i = 0; i < x; i++) str[a[i] - 1] = ' ';
	int match_len = 0;
	for (int i = 0; i < len; i++)
	{
		if (str[i] == str_p[match_len])
		{
			match_len++;
			if (match_len == len_p) return true;
		}
	}
	return false;
}
int main()
{
	ios_base::sync_with_stdio(false);
	cin >> str_t;
	cin >> str_p;
	len = str_t.size();
	len_p = str_p.size();
	a.resize(len);
	for (int i = 0; i < len; i++) cin >> a[i];
	int l = 0, r = len;
	//while (good(r)) r *= 2;
	while (r > l + 1)
	{
		int m = (l + r) / 2;
		if (good(m)) l = m;
		else r = m;
	}
	cout << l << endl;
	return 0;
}



