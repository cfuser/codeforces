#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
vector< vector<long long> > a;
bool cmp(vector<long long> a, vector<long long> b)
{
	return a[0] > b[0];
}
int main()
{
	int T;
	cin >> T;
	while (T--)
	{
		int n;
		cin >> n;
		a.resize(n, vector<long long>(2) );
		for (int i = 0; i < n; i++)
		{
			cin >> a[i][0];
			a[i][1] = i + 1;
		}
		sort(a.begin(), a.end(), cmp);
		long long num = 0;
		for (int i = 0; i < n; i++)
			for (int j = n - 1; j > i && a[i][0] * a[j][0] <= 4 * n; j--)
			{
				if (a[i][0] * a[j][0] == a[i][1] + a[j][1]) num += 1;
			}
		cout << num << endl;
		a.clear();
	}
	return 0;
}
