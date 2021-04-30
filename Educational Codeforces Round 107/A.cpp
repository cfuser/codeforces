#include<bits/stdc++.h>
using namespace std;
int main()
{
	int T;
	cin >> T;
	while (T--)
	{
		int n, num = 0;
		cin >> n;
		for (int i = 0; i < n; i++)
		{
			int x;
			cin >> x;
			if (x != 2) num += 1;
		}
		cout << num << endl;
	}
	return 0;
}
