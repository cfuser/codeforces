#include<bits/stdc++.h>
using namespace std;
const int N = 2e3 + 5;
int a[N];
long long min_value[N][N];
int main()
{
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) cin >> a[i];
	sort(a, a + n);
	for (int i = 0; i < n; i++) min_value[i][0] = 0;
	for (int len = 1; len < n; len++)
		for (int i = 0; i < n - len; i++)
		min_value[i][len] = min(min_value[i][len - 1] , min_value[i + 1][len - 1]) + a[i + len] - a[i];
	cout << min_value[0][n - 1] << endl; 
	return 0;
}
