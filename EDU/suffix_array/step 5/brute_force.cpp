#include<bits/stdc++.h>
using namespace std;
int main()
{
	freopen("in.txt","r",stdin);
	freopen("brute.txt","w",stdout);
	int n, m;
	cin >> n >> m;
	string s = "";
	for (int i = 0; i < n; i++)
	{
		int x;
		cin >> x;
		s += (char)(x + 47);
	}
	vector<string> sub;
	int num = 0;
	for (int i = 0; i < n; i++)
		for (int j = i; j < n; j++)
			{
				sub.push_back(s.substr(i, j - i + 1));
				num++;
			}	
	sort(sub.begin(), sub.end());
	//for (int i = 0; i < num; i++) cout<<sub[i]<<endl;
	long long ans = 0;
	for (int i = 0; i < num; i++)
	{
		int j = i + 1;
		while (j < num && sub[i] == sub[j]) j++;
		j--;
		ans = max(ans, (long long)sub[i].size() * (j - i + 1));
		//cout << ans << endl;
		i = j;
	}	
	cout << ans << endl;
	fclose(stdin);fclose(stdout);
	return 0;
}
