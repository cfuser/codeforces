#include<bits/stdc++.h>
using namespace std;
int work(int sum)
{
	if (sum < 0) return 1;
	else if (sum == 0) return 0;
	else if (sum > 0) return sum;
}
int main()
{
	int T;
	cin >> T;
	while (T--)
	{
		int n;
		cin >> n;
		int sum = 0;
		for (int i = 0; i < n; i++)
		{
			int x;
			cin >> x;
			sum += x;
		}
		cout << work(sum - n) << endl;
	}
	return 0;
}
