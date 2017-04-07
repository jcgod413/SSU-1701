#include <iostream>
#include <utility>
#include <cstdlib>
using namespace std;

pair <char,int> d[1515][1515];

typedef struct _gnd {
	int banana=0;
	int apple=0;
}Gnd;

int n, m;
int dp[1515][1515];
Gnd gnd[1515][1515];

inline int MAX(int x, int y, int z)
{
	if (x >= y && x >= z) return x;
	else if (y >= x && y >= z) return y;
	else return z;
}

int main()
{
	int i, j;
	char tmp[20];
	scanf("%d %d\n", &n, &m);
	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= m; j++)
		{
			scanf("%s", &tmp);
			if (tmp[0] == 'B') d[i][j].first = 1;
			else d[i][j].first = 2;
			d[i][j].second = atoi(&tmp[1]);
		}
	}
	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= m; j++)
		{
			if (d[i][j].first == 1) gnd[i][j].banana += gnd[i - 1][j].banana + d[i][j].second;
			else gnd[i][j].banana = gnd[i - 1][j].banana;

			if(d[n-i+1][j].first == 2) gnd[n - i + 1][j].apple += gnd[n - i + 2][j].apple + d[n - i + 1][j].second;
			else gnd[n - i + 1][j].apple = gnd[n - i + 2][j].apple;
		}
	}
	int x, y, z;
	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= m; j++)
		{
			x = (i>1 && j>1 || (i == 1 && j == 1)) ? dp[i - 1][j - 1] + gnd[i-1][j].banana + gnd[i+1][j].apple : 0;
			y = (j==1) ? 0 : dp[i][j - 1] + gnd[i-1][j].banana + gnd[i+1][j].apple; 
			z = (i == 1) ? 0 : dp[i - 1][j] - gnd[i][j].apple + gnd[i + 1][j].apple;
			dp[i][j] = MAX(x, y, z);
		}
	}
	cout << dp[n][m];
	return 0;
}