#include <iostream>
#include <vector>
using namespace std;

vector <int> v;
vector <int> sum;
int main()
{
	int n;
	int i = 0;
	int s = 3;
	int end;
	int center = 3;
	int v_size;
	int sp;
	cin >> n;
	sum.push_back(0);
	while (sum[i] < n)
	{
		++i;
		sum.push_back(sum[i - 1] * 2 + i + 2);
	}
	sum.pop_back();

	if (sum[sum.size() - 1] + 1 == n)
	{
		cout << 'm';
		return 0;
	}
	end = sum[sum.size() - 1] + sum.size() + 3 ;
	v.push_back(center);
	while (end + s < n)
	{
		v_size = v.size();
		if (s + end > n) break;
		v.push_back(++center);
		s += center;
		for (i = 0; i < v_size; i++)
		{
			if (s + end > n) goto out;
			v.push_back(v[i]);
			s += v[i];
		}
	}
out:
	if (end + s == n || end==n) cout << 'm';
	else cout << 'o';
	return 0;
}

