#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
int flag[N];
int main()
{
	int T;
	cin >> T;
	while (T--)
	{
		int n;
		long long k;
		cin >> n >> k;
		if (n <= 62 && ((long long)1 << (n - 1) < k))
		{
			cout << -1 << endl;
			continue;
		}
		memset(flag, 0, sizeof(int) * n);
		long long K = k - 1;
		for (int i = n - 2; i >= 0; i--)
		{
			flag[i] = K % 2;
			K /= 2;
			if (K == 0) break;
		}
		int num = 1;
		for (int i = 0; i < n; i++)
		{
			int j = i;
			while (flag[j] == 1 && j < n) j += 1;
			for (int t = i; t <= j; t++) cout << num + (j - t) << " ";
			num += (j - i + 1);
			i = j;
		}
		cout << endl;
	}
	return 0;
}
