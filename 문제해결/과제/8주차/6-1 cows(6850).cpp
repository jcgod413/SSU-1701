#include <iostream>
#include <deque>
#include <algorithm>
#include <cmath>
using namespace std;

class location {
public:
	int x, y;
	double angle;
};

deque<location> stack;

location fence[10010];
location temp;

bool cmp(location t1, location t2) {
	if (t1.angle == t2.angle) if(pow(temp.x - t1.x, 2) + pow(temp.y - t1.y, 2) > pow(temp.x - t2.x, 2) + pow(temp.y - t2.y, 2)) return 1;
	else return 0;
	return t1.angle > t2.angle;
}

inline int ccw(const location p1, const location p2, const location p3)
{
	return (p2.x - p1.x)*(p3.y - p1.y) - (p2.y - p1.y)*(p3.x - p1.x);
}

int main()
{
	//freopen("input.txt", "r", stdin);
	int n;
	int i, j, start = 1;
	scanf("%d", &n);
	for (i = 1; i <= n; i++)
	{
		scanf("%d %d", &fence[i].x, &fence[i].y);
		if (fence[start].y >= fence[i].y)
		{
			if (fence[start].y == fence[i].y && fence[start].x < fence[i].x) continue;
			start = i;
		}
	}
	temp = fence[start];
	fence[start] = fence[1];
	fence[1] = temp;
	for (i = 1; i <= n; i++) fence[i].angle = abs(atan2(temp.y - fence[i].y, temp.x - fence[i].x));
	sort(&fence[2], &fence[n + 1], cmp);
	stack.push_back(fence[1]);
	stack.push_back(fence[2]);
	deque<location>::iterator iter1;
	deque<location>::iterator iter2;
	for (i = 3; i <= n; i++)
	{
		iter1 = iter2 = stack.end();
		iter1 -= 1;
		iter2 -= 2;
		while (stack.size() >= 3 && ccw(*iter2, *iter1, fence[i]) <= 0)
		{
			iter1--;
			iter2--;
			stack.pop_back();
		}
		stack.push_back(fence[i]);
	}
	stack.push_back(fence[1]);
	double sum = 0;
	for (iter1 = stack.begin(); iter1 < stack.end() -1; iter1++)
	{
		sum += (*iter1).x*(*(iter1 + 1)).y;
		sum -= (*iter1).y*(*(iter1 + 1)).x;
	}
	cout << (int)(abs(sum) / 100);
	return 0;
}