#include<bits/stdc++.h>
using namespace std;
string work(int n)
{
	if (n % 2 == 1) return "Bob";
	int pow = 0;
	while (n % 2 == 0)
	{
		n /= 2;
		pow += 1;
	}
	if (n != 1) return "Alice";
	if (pow % 2 == 0) return "Alice";
	else return "Bob";
}
int main()
{
	int T;
	cin >> T;
	while (T--)
	{
		int n;
		cin >> n;
		cout << work(n) << endl;
	}
	return 0;
}
