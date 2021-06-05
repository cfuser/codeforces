#include<bits/stdc++.h>
using namespace std;
const int N = (1 << 20) + 5;
int num[N];
char node[N];
int get_Index(int K, int n, int p)
{
	int index = 0;
	int num = 1 << (K - 1);
	while (p > num)
	{
		K -= 1;
		p -= num;
		num /= 2;
	}
	return num - 1 + p;
}
void update(int index)
{
	if (node[index] == '0')
	{
		num[index] = num[index * 2];
	}
	else if (node[index] == '1')
	{
		num[index] = num[index * 2 + 1];
	}
	else if (node[index] == '?')
	{
		num[index] = num[index * 2] + num[index * 2 + 1];
	}
}
int main()
{
	int K;
	cin >> K;
	string str;
	cin >> str;
	int n = (1 << K) - 1;
	for (int i = n + 1; i <= 2 * n + 1; i++)
	{
		num[i] = 1;
	}
	for (int i = 1; i <= n; i++)
	{
		int index = get_Index(K, n, i);
		node[index] = str[i - 1];
		update(index);
	}
	int q;
	cin >> q;
	while (q--)
	{
		int p;
		char c;
		cin >> p >> c;
		int index = get_Index(K, n, p);
		node[index] = c;		
		while (index)
		{
			update(index);
			index /= 2;
		}
		cout << num[1] << endl;
	}
	return 0;
}
