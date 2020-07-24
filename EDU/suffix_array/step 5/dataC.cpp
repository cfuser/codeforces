#include<bits/stdc++.h>
using namespace std;
int main()
{
	freopen("in.txt","w",stdout);
	srand((unsigned)time(0));
	int n = 100;
	int m = rand() % 1000;
	string s = "";
	for (int i = 0; i < n; i++)
	{
		int x;
		x = rand() % 26 + 97;
		s=s+(char)x;
	}
	cout << s << endl;
	cout << m << endl;
	for (int i = 0; i < m; i++)
	{
		int x,y;
		x = rand() % n + 1;
		y = rand() % (n - x + 1) + x;
		cout << x << " " << y << endl;
	}
	fclose(stdout);
	return 0;
}
