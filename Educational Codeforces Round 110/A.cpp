#include<bits/stdc++.h>
using namespace std;
int main()
{
	int T;
	cin >> T;
	while (T--)
	{
		int s[4];
		for (int i = 0; i < 4; i++) cin >> s[i];
		int minn[2] = {min(s[0], s[1]), min(s[2], s[3])};
		int maxm[2] = {max(s[0], s[1]), max(s[2], s[3])};
		if (minn[0] > maxm[1] || minn[1] > maxm[0]) cout << "NO" << endl;
		else cout << "YES" << endl;
	}
	return 0;
}
