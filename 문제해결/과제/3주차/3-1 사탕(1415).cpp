#include<iostream>
using namespace std;
#include<algorithm>
#include<memory.h>
int n, m, sm, a[60], cost[60], mx[60], offset[60], isNotPrime[500010] = { 1,1 };
long long d[10020][110], out;
int main()
{
	int i, j, k, prv = 0;
	for (i = 4; i <= 500000; i = i + 2)isNotPrime[i] = 1;
	for (i = 3; i <= 707; i = i + 2)if (!isNotPrime[i])for (j = 3; i*j <= 500000; j = j + 2)isNotPrime[i*j] = 1;
	cin >> n;
	for (i = 1; i <= n; ++i)cin >> a[i];
	sort(&a[1], &a[n + 1]);
	for (i = 1; i <= n; ++i)
	{
		if (a[i] != a[i + 1])
		{
			cost[++m] = a[i];
			mx[m] = i - prv;
			offset[m] = prv + m;
			prv = i;
		}
		sm = sm + a[i];
	}
	offset[m + 1] = n + m + 1;
	d[0][0] = 1;
	for (i = 0; i <= sm; ++i)
	{
		if (i)memset(d[i % 10010], 0, sizeof(d[i % 10010]));
		for (j = 1; j <= m; ++j)
		{
			for (k = offset[j - 1]; k<offset[j]; ++k)d[i % 10010][offset[j]] = d[i % 10010][offset[j]] + d[i % 10010][k];
			for (k = offset[j] + 1; k<offset[j + 1]; ++k)if (i - cost[j] >= 0)d[i % 10010][k] = d[(i - cost[j]) % 10010][k - 1];
		}
		if (!isNotPrime[i])for (j = offset[m]; j<offset[m + 1]; ++j)out = out + d[i % 10010][j];
	}
	cout << out;
	return 0;
}