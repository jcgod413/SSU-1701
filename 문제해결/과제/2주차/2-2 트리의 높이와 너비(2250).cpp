#include <iostream>
using namespace std;

int max_degree, node_cnt;

typedef struct _save {
	int first = 0;
	int last = 0;
}save;

typedef struct _node {
	int data;
	int depth;
	struct _node *next;
	struct _node *prev;
}node;

node *head, *tail;

node *find_node(int data)
{
	node *sf = (node *)malloc(sizeof(node));
	node *sb = (node *)malloc(sizeof(node));
	sf = head->next;
	sb = tail->prev;
	while ((sf->data != data && sf != tail) && (sb->data != data && sb != head))
	{
		sf = sf->next;
		sb = sb->prev;
	}
	if (sf->data == data || sf == tail) return sf;
	else return sb;

}


node *p_insert_front(int data, node *back)
{
	++node_cnt;
	node *tmp = (node *)malloc(sizeof(node));
	if (back == head) return NULL;
	tmp->data = data;
	back->prev->next = tmp;
	tmp->prev = back->prev;
	back->prev = tmp;
	tmp->next = back;
	tmp->depth = max_degree = back->depth + 1;
	return tmp;
}

node *p_insert_back(int data, node *front)
{
	++node_cnt;
	node *tmp = (node *)malloc(sizeof(node));
	if (front == tail) return NULL;
	tmp->data = data;
	front->next->prev = tmp;
	tmp->next = front->next;
	front->next = tmp;
	tmp->prev = front;
	tmp->depth = max_degree = front->depth + 1;
	return tmp;
}

void init()
{
	head = (node *)malloc(sizeof(node));
	tail = (node *)malloc(sizeof(node));
	head->next = tail;
	head->prev = head;
	tail->prev = head;
	tail->next = tail;
	head->depth = tail->depth = 0;
}
int main()
{

	int n;
	int search_cnt = 0;
	int max_pt, max = -1;
	node *tree = (node *)malloc(sizeof(node));
	init();
	cin >> n;
	save *s = (save *)calloc(n + 2, sizeof(save));
	for (int i = 1; i <= n; i++)
	{
		int parent, left_child, right_child;
		cin >> parent >> left_child >> right_child;
		tree = find_node(parent);
		if (tree == tail)
		{
			p_insert_front(parent, tail);
			tree = tail->prev;
		}
		if (tree == head)
		{
			p_insert_back(parent, head);
			tree = head->next;
		}
		if (left_child != -1) p_insert_front(left_child, tree);
		if (right_child != -1) p_insert_back(right_child, tree);
	}
	tree = head->next;
	while (search_cnt<node_cnt)
	{
		++search_cnt;
		if (s[tree->depth].first == 0) s[tree->depth].first = search_cnt;
		s[tree->depth].last = search_cnt;
		if (max < s[tree->depth].last - s[tree->depth].first + 1)
		{
			max = s[tree->depth].last - s[tree->depth].first + 1;
			max_pt = tree->depth;
		}
		else if (max == s[tree->depth].last - s[tree->depth].first + 1) max_pt = (tree->depth > max_pt) ? max_pt : tree->depth;
		tree = tree->next;

	}

	cout << max_pt << ' ' << max;
	return 0;
}
