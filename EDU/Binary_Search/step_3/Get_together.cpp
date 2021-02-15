#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
int n;
double x[N], v[N];
vector<double> intersect(vector<double> boundary, vector<double> bound_i)
{
	return vector<double> {max(boundary[0], bound_i[0]), min(boundary[1], bound_i[1])};
}
bool good(double t)
{
	double left = - DBL_MAX, right = DBL_MAX;
	for (int i = 0; i < n; i++)
	{
		double i_left = x[i] - v[i] * t, i_right = x[i] + v[i] * t;
		if (i_left > right || i_right < left) return false;
		left = max(left, i_left);
		right = min(right, i_right); 
	}
	return true;
}
int main()
{ 
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		scanf("%lf %lf", &x[i], &v[i]);
	}
	double l = 0, r = 1;
	while (!good(r)) r *= 2;
	while (r - l > 1e-6)
	{
		double m = (l + r) / 2;
		if (!good(m)) l = m;
		else r = m;
	}
	cout << setprecision(20) << r << endl;
	return 0;
}

