#include <iostream>
#include <algorithm>
using namespace std;
typedef struct _G {
	int data;
	int index;
}G;
bool cmp(struct _G &x, struct _G &y)
{
	if (x.data == y.data) return x.index < y.index;
	return x.data < y.data;
}
int main()
{
	int i, n, max = -2147483647;
	cin >> n;
	G *A = (G *)malloc(sizeof(G)*(n + 1));
	for (i = 1; i <= n; i++)
	{
		cin >> A[i].data;
		A[i].index = i;
	}
	sort(&A[1], &A[n + 1], cmp);
	for (i = 1; i <= n; i++) if (A[i].index - i > max) max = A[i].index - i;
	cout << max + 1;
	free(A);
	return 0;
}
