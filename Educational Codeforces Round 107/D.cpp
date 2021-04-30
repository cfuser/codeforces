#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n, k;
	cin >> n >> k;
	if (k == 1)
	{
		for (int i = 0; i < n; i++) cout << "a";
		cout << endl;
		return 0;
	}
	string str = "";
	for (int i = 0; i < k; i++)
		for (int j = i; j < k; j++)
		{
			str += (char)(j + 97);
			if (j != k - 1) str += (char)(i + 97);
		}
	for (int i = 0; i < n / str.size(); i++) cout << str;
	cout << str.substr(0, n % str.size()) << endl;
	return 0;
}
