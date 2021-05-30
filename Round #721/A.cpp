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
		int pow = 1;
		while (n != 1)
		{
			n = n / 2;
			pow *= 2;
		}
		cout << pow - 1 << endl;
	}
	return 0;
}
