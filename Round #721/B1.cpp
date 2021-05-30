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
		string str;
		cin >> str;
		int num = 0, unpair = 0, mid = 0;
		if (n % 2) mid = (str[n / 2] - '0') ^ 1;
		for (int i = 0; i < n; i++) num += (str[i] - '0') ^ 1;
		for (int i = 0; i < (n + 1) / 2; i++) unpair += (str[i] != str[n - 1 - i]);
		if (num == 0) cout << "DRAW" << endl;
		else if (mid)
		{
			if (num - mid) cout << "ALICE" << endl;
			else cout << "BOB" << endl;
		}
		else
		{
			if (num) cout << "BOB" << endl;
			else cout << "ALICE" << endl;
		}
	}
	return 0;
}
