#include <iostream>
#include <cstdio>
using namespace std;
int a[51][51];
int d[51][51][51][51];
int answer[51];
int main() {
	int i, j, l, k;
	int n, m, c;
	scanf("%d %d %d", &n, &m, &c);
	for (i = 0; i <= 50; i++) for (j = 0; j <= 50; j++) a[i][j] = -1;
	for (int t1,t2,i = 0; i<c; i++) 
	{ 
		scanf("%d %d", &t1, &t2);
		a[t1][t2] = i;
	}
	d[1][0][0][0] = 1;
	for (i = 1; i <= n; i++) 
	{
		for (j = 1; j <= m; j++) 
		{
			if (a[i][j] == -1) 
			{
				d[i][j][0][0] += d[i - 1][j][0][0] + d[i][j - 1][0][0];
				d[i][j][0][0] %= 1000007;
			}
			for (k = 1; k <= c; k++) 
			{ 
				if (a[i][j] == -1) 
				{
					for (l = 0; l<c; l++) 
					{
						d[i][j][l][k] += d[i - 1][j][l][k] + d[i][j - 1][l][k];
						d[i][j][l][k] %= 1000007;
					}
				}
				else 
				{  
					if (k==1) 
					{ 
						d[i][j][a[i][j]][k] += d[i - 1][j][0][0] + d[i][j - 1][0][0];
						d[i][j][a[i][j]][k] %= 1000007;
					}
					else 
					{
						for (l = 0; l<a[i][j]; l++)
						{
							d[i][j][a[i][j]][k] += d[i - 1][j][l][k - 1] + d[i][j - 1][l][k - 1];
							d[i][j][a[i][j]][k] %= 1000007;
						}
					}
				}
			}
		}
	}
	for (i = 0; i <= c; i++) 
	{
		for (int j = 0,tmp=(c>1?c:1); j<tmp; j++) 
		{
			answer[i] += d[n][m][j][i];
			answer[i] %= 1000007;
		}
		printf("%d ", answer[i]);
	}
	return 0;
}