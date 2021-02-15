#include<bits/stdc++.h>
using namespace std;
double c;
bool good(double x)
{
	return x * x + sqrt(x) >= c;
}
int main()
{
	ios_base::sync_with_stdio(false);
	cin >> c;
	double l = 0, r = 1;
	while (!good(r)) r *= 2;
	for (int i = 0; i < 100; i++)
	{
		double m = (l + r) / 2;
		if (good(m)) r = m;
			else l = m;
	}
	cout << setprecision(20) << r << endl;
	return 0;
}


