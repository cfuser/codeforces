#include<bits/stdc++.h>
using namespace std;
const int N = 2e3 + 5;
int a[N];
int main()
{
	int T;
	cin >> T;
	while (T--)
	{
		int n;
		cin >> n;
		for (int i = 0; i < n; i++) cin >> a[i];
		int sum = 0, temp = 0, num = 0;
		for (int i = 0; i < n; i++) sum = sum ^ a[i];
		for (int i = 0; i < n; i++)
		{
			temp = temp ^ a[i];
			if (temp == sum)
			{
				temp = 0;
				num += 1;
			}
		}
		if (num >= 2 || sum == 0)
		{
			cout << "YES" << endl;
		}
		else
		{
			cout << "NO" << endl;
		}
	}
	return 0;
}
