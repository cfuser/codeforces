#include<bits/stdc++.h>
using namespace std;
int main()
{
	int T;
	cin >> T;
	while (T--)
	{
		vector<int> num[2];
		int n;
		cin >> n;
		for (int i = 0; i < n; i++)
		{
			int x;
			cin >> x;
			num[x % 2].push_back(x);
		}
		for (int j = 0; j < 2; j++)
			for (int i = 0; i < num[j].size(); i++)
			cout << num[j][i] << " ";
		cout << endl;
	}
	return 0;
}
