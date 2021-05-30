#include<bits/stdc++.h>
using namespace std;
int main()
{
	int T;
	cin >> T;
	while (T--)
	{
		map<int, long long> value;
		long long ans = 0, f = 0;
		int n;
		cin >> n;
		for (int i = 0; i < n; i++)
		{
			int x;
			cin >> x;
			if (value.find(x) != value.end())
			{
				f += value[x];
				value[x] += i + 1; 
			}
			else value[x] = i + 1;
			ans += f;
		}
		cout << ans << endl;
	}
	return 0;
}
