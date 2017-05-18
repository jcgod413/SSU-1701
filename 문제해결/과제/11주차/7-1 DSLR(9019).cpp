#include <cstdio>
#include <queue>
#include <cstdlib>
#include <algorithm>
using namespace std;

pair<char, int> chk[11101];
queue<int> q;
char answer[11111];

inline int D(int x) { return (x * 2) % 10000; }
inline int L(int x)
{
	x *= 10;
	x += x / 10000;
	return x % 10000;
}
inline int R(int x)
{
	int tmp = x % 10;
	x /= 10;
	x += tmp * 1000;
	return x%10000;
}
inline int S(int x) { return (x == 0 ? 9999 : x - 1); }
int main()
{
	int N;
	int i, j;
	scanf("%d", &N);
	while (N--)
	{
		int n, m;	
		while (!q.empty()) q.pop();
		for (j = 0; j <= 10000; j++) 
		{ 
			chk[j].first = '\0';  
			chk[j].second = -1; 
			answer[j] = '\0'; 
		}
		
		scanf("%d %d", &n, &m);
		
		q.push(n);
		chk[q.front()].second = 0;
		chk[q.front()].first = '\0';
		
		while (!q.empty())
		{
			if (q.front() == m) break;

			int push = L(q.front());
			if (chk[push].second==-1)
			{
				chk[push].first = 'L';
				chk[push].second = q.front();
				q.push(push);
				if (push == m) break;
			}

			push = R(q.front());
			if (chk[push].second==-1)
			{
				chk[push].first = 'R';
				chk[push].second = q.front();
				q.push(push);
				if (push == m) break;
			}

			push = S(q.front());
			if (chk[push].second==-1)
			{
				chk[push].first = 'S';
				chk[push].second = q.front();
				q.push(push);
				if (push == m) break;
			}

			push = D(q.front());
			if (chk[push].second==-1)
			{
				chk[push].first = 'D';
				chk[push].second = q.front();
				q.push(push);
				if (push == m) break;
			}
			q.pop();
		}
		for (j = 0; chk[m].first != '\0'; j++)
		{
			answer[j] = chk[m].first;
			m = chk[m].second;
		}
		reverse(&answer[0], &answer[j]);
		printf("%s\n", answer);
	}
	return 0;
}
