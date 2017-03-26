#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

char word[55];
char bag[55][55];

int word_cmp(int start, int chk)
{
	int i;
	char cmp1[30] = { 0 }, cmp2[30] = {0};
	int cost=0;
	for (i = 1; i <= bag[chk][0]; i++)
	{
		if (bag[chk][i] != word[start + i - 1]) ++cost;
		++cmp1[bag[chk][i]-'a'+1];
		++cmp2[word[start + i - 1]-'a'+1];
	}
	for (i = 1; i <= 26; i++) if (cmp1[i] != cmp2[i]) break;
	if (i != 27) return -1;
	else return cost;
}

int main()
{
	int i, j;
	int n, m;
	int dp[550];
	for (i = 1; i <= 110; i++) dp[i] = -1;
	cin >> &word[1];
	n = strlen(word + 1);
	cin >> m;
	for (i = 1; i <= m; i++)
	{
		cin >> &bag[i][1];
		bag[i][0] = strlen(&bag[i][1]);
	}
	dp[0] = 0;
	int now = 0;
	int tmp;
	for (i = 1; i <= n; i++)
	{
		for (int cp = 1; cp <= m; cp++)
		{
			if (i - bag[cp][0] >= 0 && dp[i - bag[cp][0]] != -1)
			{
				tmp = word_cmp(i - bag[cp][0] + 1, cp);
				if (tmp != -1 && (dp[i] == -1 || dp[i] > tmp + dp[i - bag[cp][0]])) dp[i] = dp[i - bag[cp][0]] + tmp;
			}
		}
	}
	cout << dp[n];
	return 0;
}