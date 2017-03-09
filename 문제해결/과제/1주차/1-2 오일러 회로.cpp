#include <iostream>
using namespace std;
int G[1010][1010];
int n;
int ch;
void back(int x)
{
	for (int i = 1; i <= n; i++)
	{
		while (G[x][i])
		{
			G[x][i]--;
			G[i][x]--;
			back(i);
		}
	}
    cout << x << ' ';
	return;
}
int main()
{
	int i, j;
	cin >> n;
	for (i = 1; i <= n; i++)
	{
		int s = 0;
		for (j = 1; j <= n; j++)
		{
			cin >> G[i][j];
			s += G[i][j];
		}
		if (s % 2)
		{
			cout << "-1";
			return 0;
		}
	}
	back(1);
	return 0;
}