#include <iostream>
#include <utility>
#include <algorithm>
using namespace std;
int n;
struct _data {
	int d;
	int sum = 0;
}tree[555][555];
struct _sort {
	int x, y;
	int d;
}s[555 * 555];
int Max;
bool cmp(struct _sort &tmp1, struct _sort &tmp2) { return tmp1.d < tmp2.d; }
inline int big(int x, int y)
{
	return x > y ? x : y;
}
int main()
{
	int i, j, cnt = 0;
	cin >> n;
	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= n; j++)
		{
			scanf("%d", &tree[i][j].d);
			s[++cnt].d = tree[i][j].d;
			s[cnt].x = i;
			s[cnt].y = j;
		}
	}
	sort(&s[1], &s[cnt + 1], cmp);
	for (cnt =1;cnt <= n*n;cnt++)
	{
		if (tree[s[cnt].x - 1][s[cnt].y].d > tree[s[cnt].x][s[cnt].y].d)
		{
			tree[s[cnt].x - 1][s[cnt].y].sum = big(tree[s[cnt].x][s[cnt].y].sum + 1, tree[s[cnt].x - 1][s[cnt].y].sum);
			Max = Max < tree[s[cnt].x - 1][s[cnt].y].sum ? tree[s[cnt].x - 1][s[cnt].y].sum : Max;
		}
		if (tree[s[cnt].x + 1][s[cnt].y].d > tree[s[cnt].x][s[cnt].y].d)
		{
			tree[s[cnt].x + 1][s[cnt].y].sum = big(tree[s[cnt].x][s[cnt].y].sum + 1, tree[s[cnt].x + 1][s[cnt].y].sum);
			Max = Max < tree[s[cnt].x + 1][s[cnt].y].sum ? tree[s[cnt].x + 1][s[cnt].y].sum : Max;
		}
		if (tree[s[cnt].x][s[cnt].y - 1].d > tree[s[cnt].x][s[cnt].y].d)
		{
			tree[s[cnt].x][s[cnt].y - 1].sum = big(tree[s[cnt].x][s[cnt].y].sum + 1, tree[s[cnt].x][s[cnt].y - 1].sum);
			Max = Max < tree[s[cnt].x][s[cnt].y - 1].sum ? tree[s[cnt].x][s[cnt].y - 1].sum : Max;
		}
		if (tree[s[cnt].x][s[cnt].y + 1].d > tree[s[cnt].x][s[cnt].y].d)
		{
			tree[s[cnt].x][s[cnt].y + 1].sum = big(tree[s[cnt].x][s[cnt].y].sum + 1, tree[s[cnt].x][s[cnt].y + 1].sum);
			Max = Max < tree[s[cnt].x][s[cnt].y + 1].sum ? tree[s[cnt].x][s[cnt].y + 1].sum : Max;
		}
	}
	cout << Max + 1;
	return 0;
}