#include <iostream>
#include <string.h>
using namespace std;
int main()
{
	char a[55][55];
	int n, len;
	int i, j;
	scanf("%d", &n);
	for (i = 1; i <= n; i++)
	{
		cin >> &a[i][1];
	}
	len = strlen(&a[1][1]);
	for (i = 1; i <= len; i++)
	{
		for (j = 1; j < n; j++)
		{
			if (a[j][i] != a[j + 1][i]) break;
		}
		cout << ((j == n) ? a[1][i] : '?');
	}
	return 0;
}