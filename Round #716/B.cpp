#include<bits/stdc++.h>
using namespace std;
const int MO = 1e9 + 7;
int main()
{
	int T;
	cin >> T;
	while (T--)
	{
		int n, k;
		cin >> n >> k;
		int ans = 1;
		for (int i = 0; i < k; i++)
		ans = (long long)ans * n % MO;
		cout << ans << endl;
	}
	return 0;
}
