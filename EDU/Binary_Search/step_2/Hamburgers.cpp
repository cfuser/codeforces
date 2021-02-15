#include<bits/stdc++.h>
using namespace std;
int each_b, each_c, each_s;
int n_b, n_c, n_s, p_b, p_c, p_s;
long long rubles;
bool good(long long x)
{
	long long cost = 0;
	cost += (long long)max(each_b * x - n_b, (long long)0) * p_b;
	cost += (long long)max(each_c * x - n_c, (long long)0) * p_c;
	cost += (long long)max(each_s * x - n_s, (long long)0) * p_s;
	return cost <= rubles;
}
int main()
{
	ios_base::sync_with_stdio(false);
	string str;
	cin >> str;
	int len = str.size();
	for (int i = 0; i < len; i++)
	{
		if (str[i] == 'B') each_b++;
		else if (str[i] == 'C') each_c++;
		else if (str[i] == 'S') each_s++;
	}
	cin >> n_b >> n_s >> n_c;
	cin >> p_b >> p_s >> p_c;
	cin >> rubles;
	long long l = 0, r = 1;
	while (good(r)) r *= 2;
	while (r > l + 1)
	{
		long long m = (l + r) / 2;
		if (good(m)) l = m;
		else r = m;
	}
	cout << l << endl;
	return 0;
}


