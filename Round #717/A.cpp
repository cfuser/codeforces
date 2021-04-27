#include<bits/stdc++.h>
using namespace std;
const int N = 1e2 + 5;
int a[N];
int main()
{
	int T;
	cin >> T;
	while (T--)
	{
		int n, k;
		cin >> n >> k;
		int K = k;
		for (int i =  0; i < n; i++)
		{
			cin >> a[i];
			if (a[i] >= k)
			{
				a[i] -= k;
				k = 0;
			}
			else
			{
				k -= a[i];
				a[i] = 0;
			}
		}
		a[n - 1] += (K - k);
		for (int i = 0; i < n; i++) cout << a[i] << " ";
		cout << endl;
	}
	return 0;
}
