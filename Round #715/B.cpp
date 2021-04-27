#include<bits/stdc++.h>
using namespace std;
int main()
{
	int T;
	cin >> T;
	while (T--)
	{
		int n, num_T = 0, num_M = 0, work = 1;
		cin >> n;
		string str;
		cin >> str;
		for (int i = 0; i < n; i++)
		{
			if (str[i] == 'T') num_T++;
			else num_M++;
			if (num_T < num_M)
			{
				work = 0;
				break;
			}
		}
		num_T = num_M = 0;
		for (int i = n - 1; i >= 0; i--)
		{
			if (str[i] == 'T') num_T++;
			else num_M++;
			if (num_T < num_M)
			{
				work = 0;
				break;
			}
		}
		if (num_T == num_M * 2 && work) cout << "YES" << endl;
		else cout << "NO" << endl;
	}
	return 0;
}
