#include<bits/stdc++.h>
using namespace std;
string str[3];
int l[3];
int main()
{
	int T;
	cin >> T;
	for (int t = 0; t < T; t++)
	{
		int n;
		cin >> n;
		for (int i = 0; i < 3; i++) cin >> str[i];
		for (int i = 0; i < 3; i++) l[i] = 0;
		//if (T == 285 && t == 17) cout << str[0] << endl << str[1] << endl << str[2] << endl; 
		int step = 0;
		while (true)
		{
			int seq[2] = {0, 0};
			if (str[0][l[0]] == str[1][l[1]]) seq[0] = 0, seq[1] = 1;
			else if (str[0][l[0]] == str[2][l[2]]) seq[0] = 0, seq[1] = 2;
			else seq[0] = 1, seq[1] = 2;
			cout << str[seq[0]][l[seq[0]]];
			l[seq[0]] += 1; l[seq[1]] += 1; step += 1;
			if (l[seq[0]] == 2 * n || l[seq[1]] == 2 * n) break;
		}
		int index = 0;
		for (int i = 0; i < 3; i++)
		if (l[i] != 2 * n && l[i] >= step - n) index = i;
		/*for (int i = 0; i < 3; i++)
		if (l[i] == 2 * n)
		{
			int j = (i + 1) % 3, k = (i + 2) % 3;
			if (l[j] > l[k]) index = j;
			else index = k;
		}*/
		//cout << " " << l[0] << " " << l[1] << " " << l[2] << " " << index << " " << step << endl;
		while (l[index] < 2 * n && step < 3 * n)
		{
			cout << str[index][l[index]];
			l[index] += 1;
			step += 1;
		}
		/*while (step < 3 * n)
		{
			cout << 0;
			step += 1;
		}*/
		cout << endl; 
	}
	return 0;
}
