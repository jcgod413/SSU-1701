#include <iostream>
#include <vector>
using namespace std;

vector <int> v;
vector <int> sum;
char answer;

void back(int k, int n)
{
	
	if (sum[k] + 1 == n)
	{
		answer = 'm';
		return;
	}
	else if (sum[k] + 1 < n && sum[k] + 1 + k + 2 >= n)
	{
		answer = 'o';
		return;
	}
	else if (n - (sum[k] + k + 3) > 0) back(k - 1, n - (sum[k] + k + 3));
	else back(k-1, n);
}
int main()
{
	int n;
	int i = 0;
	cin >> n;
	sum.push_back(0);
	while (sum[i++] < n) sum.push_back(sum[i - 1] * 2 + i + 2);
	back(i-2, n);
	cout << answer;
	return 0;
}

