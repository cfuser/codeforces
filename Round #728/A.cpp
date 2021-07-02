#include<bits/stdc++.h>
using namespace std;
int main()
{
	int T;
	cin >> T;
	while (T--)
	{
		int n;
		cin >> n;
		int l = 1;
		if (n % 2)
		{
			cout << "3 1 2 ";
			l = 4;
		}
		while (l < n)
		{
			cout << l + 1 << " " << l << " ";
			l += 2;
		}
		cout << endl;
	}
	return 0;
}
