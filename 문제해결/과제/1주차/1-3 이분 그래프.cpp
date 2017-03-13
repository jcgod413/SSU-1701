#include <iostream>
#include <vector>
#include <queue>
using namespace std;

vector < int > vec[20010];
int chk[20010];
queue <int> q;
int main()
{
	int i, j;
	int n, v, e;
	int state;
	int answer = 0;
	cin >> n;
	while (n--)
	{
		cin >> v >> e;
		while (!q.empty()) q.pop();
		for (i = 1; i <= v; i++)
		{
			vec[i].clear();
			chk[i] = 0;
		}
		for (i = 0; i < e; i++)
		{		
			int tmp1, tmp2;
			cin >> tmp1 >> tmp2;
			vec[tmp1].push_back(tmp2);
			vec[tmp2].push_back(tmp1);
		}
		int f;
		state = 1;
		answer = 0;
		while (answer!=-1)
		{
			int cchk = 0;
			for (i = 1; i <= v; i++)
			{
				if (!chk[i])
				{
					q.push(i);
					chk[i] = 1;
					cchk = 1;
					break;
				}
			}
			if (!cchk) break;
			while (!q.empty() && answer!=-1)
			{
				f = q.front();
				for (i = 0; i < vec[f].size(); i++)
				{
					if (!chk[vec[f][i]])
					{
						chk[vec[f][i]] = chk[f] % 2 + 1;
						q.push(vec[f][i]);
					}
					else if (chk[f] == chk[vec[f][i]] && f != vec[f][i])
					{
						answer = -1;
						break;
					}
				}
				q.pop();
			}

		}
		if (answer == -1) cout << "NO" << endl;
		else cout << "YES" << endl;


	}
}