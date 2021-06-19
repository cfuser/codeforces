#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
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
		sort(a, a + n);
		int index = 1;
		for (int i = 2; i < n; i++)
		if (a[i] - a[i - 1] < a[index] - a[index - 1]) index = i;
		cout << a[index - 1] << " ";
		for (int i = index + 1; i < n; i++) cout << a[i] << " ";
		for (int i = 0; i < index - 1; i++) cout << a[i] << " ";
		cout << a[index] << " ";
		cout << endl;
	}
	return 0;
}
