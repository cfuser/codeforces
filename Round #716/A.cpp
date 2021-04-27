#include<bits/stdc++.h>
using namespace std;
int main()
{
	int T;
	cin >> T;
	while (T--)
	{
		int n, work = 1;
		cin >> n;
		for (int i = 0; i < n; i++)
		{
			int x;
			cin >> x;
			int y = sqrt(x);
			if (y * y != x) work = 0;
		}
		if (!work) cout << "YES" << endl;
		else cout << "NO" << endl;
	}
	return 0;
}
