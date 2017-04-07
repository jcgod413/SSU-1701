#include <iostream>
#include <cstring>
using namespace std;

typedef struct _detect {
	int prev = 0;
	int now = 0;
}det;

det dp[17005];
unsigned char detect[17005][4255];
char answer[2][17005];
char text[17005], cmp[17005];
unsigned char compress[12] = { 0x40, 0x80, 0xc0, 0x10, 0x20, 0x30, 0x04, 0x08, 0x0c, 0x01,0x02, 0x03 };
//								01	  10    11	  01	10	  11	01	  10	11	  01   10	 11
unsigned char decompress[4] = { 0xc0, 0x30, 0x0c, 0x03 };
int cnt;
int main()
{
	int n, m;
	int i, j;
	int x, y, z;
	cin >> text + 1 >> cmp + 1;
	n = strlen(text + 1);
	m = strlen(cmp + 1);
	for (i = 0; i <= n; i++)
	{
		for (j = 0; j <= m; j++)
		{
			if (i == 0 && j == 0) continue;
			x = (i - 1 >= 0) ? dp[j].prev + 1 : 1e9;
			y = (j - 1 >= 0) ? dp[j - 1].now + 1 : 1e9;
			z = (i - 1 >= 0 && j - 1 >= 0) ? dp[j - 1].prev + (text[i] != cmp[j]) : 1e9;
			if (x <= y && x <= z)
			{
				detect[i][j / 4] |= compress[3 * (j % 4)];
				dp[j].now = x;
			}
			else if (y <= x && y <= z)
			{
				detect[i][j / 4] |= compress[3 * (j % 4) + 1];
				dp[j].now = y;
			}
			else
			{
				detect[i][j / 4] |= compress[3 * (j % 4) + 2];
				dp[j].now = z;
			}
			if (j != 0) dp[j - 1].prev = dp[j - 1].now;
		}
		dp[m].prev = dp[m].now;
	}
	int cnt = 0;
	unsigned char now = detect[n][m / 4] & decompress[(m % 4)];
	unsigned char data;
	for(cnt=1;n||m;cnt++)
	{
		now = detect[n][m / 4] & decompress[(m % 4)];
		for (i = 0; i <= 11; i++)
		{
			if (now == compress[i])	data = i % 3 + 1;
		}
		if (data == 1)
		{
			answer[0][cnt] = 'd';
			answer[1][cnt] = text[n];
			n -= 1;
		}
		else if (data == 2)
		{
			answer[0][cnt] = 'a';
			answer[1][cnt] = cmp[m];
			m -= 1;
		}
		else
		{
			if (text[n] == cmp[m])
			{
				answer[0][cnt] = 'c';
				answer[1][cnt] = text[n];
			}
			else
			{
				answer[0][cnt] = 'm';
				answer[1][cnt] = cmp[m];
			}
			n--;
			m--;
		}
	}
	for (i = cnt-1; i >= 1; i--)
	{
		cout << answer[0][i] << ' ' << answer[1][i] << endl;
	}
	return 0;
}