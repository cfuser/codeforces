#include<bits/stdc++.h>
using namespace std;
int main()
{
	int T;
	cin >> T;
	while (T--)
	{
		int prev[2] = {0, 0}; 
		string str;
		cin >> str;
		int n;
		n = str.size();
		if (str[0] == '0')
		{
			prev[0] = 0;
			prev[1] = 1;
		}
		else if (str[0] == '1')
		{
			prev[0] = 1;
			prev[1] = 0;
		}
		else if (str[0] == '?')
		{
			prev[0] = 0;
			prev[1] = 0;
		}
		long long ans = 1;
		//cout << prev[0] << " " << prev[1] << endl;
		for (int i = 1; i < n; i++)
		{
			int update[2];
			if (str[i] == '0')
			{
				update[0] = prev[1];
				update[1] = i + 1;
			}
			else if (str[i] == '1')
			{
				update[0] = i + 1;
				update[1] = prev[0];
			}
			else if (str[i] == '?')
			{
				update[0] = prev[1];
				update[1] = prev[0];
			}
			ans += (i - min(update[0], update[1]) + 1);
			prev[0] = update[0];
			prev[1] = update[1];
			//cout << prev[0] << " " << prev[1] << endl;
		}
		cout << ans << endl;
	}
	return 0;
}
