#include<bits/stdc++.h>
using namespace std;
const int N = 5e1 + 5;
int main()
{
	int n, q;
	int a[N];
	memset(a, 0x3f3f, sizeof(a));
	cin >> n >> q;
	for (int i = 0; i < n; i++)
	{
		int x;
		cin >> x;
		a[x] = min(a[x], i);
	}
	for (int i = 0; i < q; i++)
	{
		int x;
		cin >> x;
		cout << a[x] + 1 << " ";
		for (int j = 0; j < N; j++)
		if (a[j] < a[x]) a[j] += 1;
		a[x] = 0;
	}
	cout << endl;
	return 0;
}
