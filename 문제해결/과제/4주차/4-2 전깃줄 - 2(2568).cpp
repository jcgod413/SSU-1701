#include <iostream>
#include <algorithm>

using namespace std; 
typedef struct _pole
{
	int x, y;
	int chk;
}pole;

bool cmp(const pole xx, const pole yy)
{
	return xx.x < yy.x;
}
int p[500050], result[500050];
int dp[500050];
pole d[500050];
int main()
{
	int i, j, max=0, t1, t2, maxp=0, answer=0;
	int n;
	scanf("%d", &n);
	for (i = 1; i <= n; i++)
	{
		scanf("%d %d",&d[i].x,&d[i].y);
		dp[i] = 1e9;
	}
	sort(&d[1], &d[n + 1], cmp);
	int *tmp;
	for (i = 1; i <= n; i++)
	{
		tmp = lower_bound(&dp[1], &dp[dp[0]+1], d[i].y);
		if (*tmp == 1e9) ++dp[0];
		*tmp = d[i].y;
		p[i] = tmp-&dp[1]+1;
		maxp = maxp < p[i] ? p[i] : maxp;
	}
	cout << n - maxp << endl;
	for (i = n; i >= 1; i--)
	{
		if (p[i] == maxp)
		{
			--maxp;
			d[i].chk = 1;
		}
	}
	for (i = 1; i <= n; i++) if (!d[i].chk) printf("%d\n",d[i].x);
}