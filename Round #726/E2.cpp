#include<bits/stdc++.h>
using namespace std;
string str;
int main()
{
	int n, k;
	cin >> n >> k;
	cin >> str;
	int len = 1;
	for (int i = 1; i < n; i++)
	{
		if (str[i] > str[i % len]) break;
		if (str[i] < str[i % len]) len = i + 1;
	}
	for (int i = 0; i < k; i++) cout << str[i % len];
	cout << endl;
	return 0;
}
