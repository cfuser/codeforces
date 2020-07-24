#include<bits/stdc++.h>
using namespace std;
int main()
{
	freopen("in.txt","w",stdout);
	srand((unsigned)time(0));
	int n = 200;
	int m = 4;
	string s = "";
	cout << n << " " << m << endl;
	for (int i = 0; i < n; i++)
	{
		int x;
		x = rand() % m + 1;
		cout << x << " ";
	}
	cout <<endl;
	fclose(stdout);
	return 0;
}
