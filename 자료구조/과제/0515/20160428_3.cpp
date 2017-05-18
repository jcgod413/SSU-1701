#include <cstdio>
#include <iostream>
using namespace std;

template <typename T> class Chain;
template <typename T>
class ChainNode {
public:
	ChainNode(T element = 0, ChainNode* next = NULL)
	{
		data = element;
		link = next;
	}
private:
	friend class Chain<T>;
	friend class Chain<T>::iter;
	T data;
	ChainNode<T> *link;
};

template <typename T>
class Chain {
private:
	ChainNode<T> *first;
	ChainNode<T> *last;
public:
	Chain<T>() : first(0), last(0) {} // 1) ����ü�� ������

	~Chain<T>() // 2) ���� ���� �Ҹ���
	{
		ChainNode<T> *del;
		while (first != last)
		{
			del = first;
			first = first->link;
			delete del;
		}
		delete last;
	}
	
	void InsertFront(T x) // 3) �Ǿտ� �����ϴ� �Լ�
	{
		if (first)
		{
			ChainNode<T> *temp = new ChainNode<T>(first->data, first->link);
			first->data = x;
			first->link = temp;
		}
		else {
			ChainNode<T> *temp = new ChainNode<T>(x, 0);
			first = last = temp;
		}
	}

	void InsertBack(T x) // 4) �ǵڿ� �����ϴ� �Լ�
	{
		if (!last)
		{
			ChainNode<T> *temp = new ChainNode<T>(x, 0);
			first = last = temp;
			return;
		}
		ChainNode<T> *NewData = new ChainNode<T>(x, 0);
		while (last->link != 0) last = last->link;
		last->link = NewData;
		last = NewData;
	}
	T Front() { return first->data; } // 5) ù��° ���� ��ȯ �Լ�

	T Back() // 6) ������ ���� ��ȯ �Լ�
	{
		while (last->link != 0) last = last->link;
		return last->data;
	}

	T Get(int i) // 7) i��° ���� ��ȯ �Լ�
	{
		ChainNode<T> *find = first;
		while (i--)
		{
			if (find->link == NULL) break;
			find = find->link;
		}
		return find->data;
	}

	int DeleteFront() // 8) �� �� ���� ���� �Լ�
	{
		ChainNode<T> *tmp = first;
		if (first->link == 0) return -1;
		first = first->link;
		delete tmp;
		return 0;
	}

	int DeleteBack() // 9) �� �� ���� ���� �Լ�
	{
		last = first;
		while (last->link->link != 0) last = last->link;
		if (last == first) return -1;
		delete last->link->link;
		last->link = NULL;
		return 0;
	}

	void InsertNext(int i, T x) // 10) i��° ���� �� ���� �Լ�
	{
		ChainNode<T> *pt = first;
		ChainNode<T> *tmp = new ChainNode<T>(x, NULL);
		while (--i) pt = pt->link;
		tmp->link = pt->link;
		pt->link = tmp;
	}

	int DeleteNext(int i) // 11) i��° ���� ���� �Լ�
	{
		ChainNode<T> *pt = first;
		ChainNode<T> *tmp;
		while (i--)
		{
			if (pt->link == NULL) return -1;
			tmp = pt;
			pt = pt->link;
		}
		if (pt == last) last = tmp;
		tmp->link = pt->link;
		delete pt;
		return 0;
	}

	class iter // 12) �ݺ���
	{
	private:
		ChainNode<T> *it;
	public:// '=', '++', '!=', '*' ������ �����ε�
		iter() : it(NULL) {}
		iter& operator++(int)
		{
			it = it->link;
			return *this;
		}
		T& operator*() { return it->data; }
		bool operator=(ChainNode<T>* diff) { return (it = diff); }
		bool operator!=(ChainNode<T>* diff) { return (it != diff); }
	};

	void PrintAll() // �ݺ��ڸ� �̿��� ��ü����Լ�
	{
		iter i;
		cout << "��ü ���� : ";
		for (i = first; i != last->link; i++ )
		{
			cout << '[' << *i << "] ";
		}
		cout << endl;
	}
	
};


int main()
{
	Chain<int> a;
	
	for(int i=1;i<=9;i++) a.InsertBack(i); // TEST1
	a.PrintAll(); // TEST2
	a.InsertFront(0); // TEST3
	a.PrintAll(); // TEST4	
	a.InsertBack(10); // TEST5
	a.PrintAll(); // TEST6
	cout << "Front ���� : " << a.Front() << endl; // TEST7
	cout << "Back ���� : " << a.Back() << endl; // TEST8
	cout << "2��° ���� : " << a.Get(2) << endl; // TEST9
	a.DeleteFront(); // TEST10
	a.PrintAll(); // TEST11
	a.DeleteBack(); // TEST12
	a.PrintAll(); // TEST13
	a.InsertNext(3, 100); // TEST14
	a.PrintAll(); // TEST15
	a.DeleteNext(6); // TEST16
	a.PrintAll(); // TEST17

	return 0;
}