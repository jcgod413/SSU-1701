# 자료구조 과제3
자료구조(공통 1) 20160428 김동현
### 컴파일 및 실행 방법
소스파일은 20160428_3.cpp로 구성되어 있으며 Cygwin환경에서 g++컴파일러를 이용하여 컴파일 하였습니다.

사용명령어
```
$ g++ 20160428_3.cpp -o 20160428_3.exe
```

### 실행 결과

<img src = "1.png"/>

과제의 테스트 방법 1~17 문항에 따라

* 1~9까지의 정수를 갖는 노드 생성 뒤 출력
* 0을 맨 앞에 삽입 후 전체 노드 출력
* 10을 맨 뒤에 삽입 후 전체 노드 출력
* Front를 호출해서 나온 값 출력
* Back를 호출해서 나온 값 출력
* Get(2)를 호출하여 나온 값 출력
* 맨 앞의 원소 삭제 후 전체 노드 출력
* 2번째 원소 뒤에 100 삽입 후 전체 노드 출력
* 6번째 원소 삭제 후 전체 노드 출력

결과를 출력하였습니다.



### 구현 / 미구현
과제에서 주어진 모든 지시사항을 구현하였습니다.

전체 노드를 출력하는 빈도가 높아 `Chain`클래스의 멤버함수로 `PrintAll`함수를 생성하고 반복자를 이용해 전체 원소를 출력하였습니다.

1) 초기에 공백 체인을 생성하는 생성자
`Chain<T>()`
2) 체인의 모든 원소를 삭제하는 파괴자
`~Chain<T>()`
3) 체인의 맨 앞에 삽입하는 함수
`InsertFront(T x)`
4) 체인의 맨 뒤에 삽입하는 함수
`InsertBack(T x)`
5) 리스트의 첫 번째 원소를 반환하는 Front 함수
`Front()`
6) 리스트의 마지막 원소를 반환하는 Back 함수
`Back()`
7) 리스트의 i번째 원소를 반환하는 함수 Get(i)
`Get()`
8) 체인의 맨 앞에서 삭제하는 함수
`DeleteFront()`
9) 체인의 맨 뒤에서 삭제하는 함수
`DeleteBack()`
10) i번째 원소 뒤에 삽입하는 함수
`InsertNext(int i, T x)`
11) i번째 원소를 삭제하는 함수
`DeleteNext(int i)`
12) 반복자
`Chain<T>::iter`


## 소스코드
```
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
	Chain<T>() : first(0), last(0) {} // 1) 공백체인 생성자

	~Chain<T>() // 2) 원소 삭제 소멸자
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

	void InsertFront(T x) // 3) 맨앞에 삽입하는 함수
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

	void InsertBack(T x) // 4) 맨뒤에 삽입하는 함수
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
	T Front() { return first->data; } // 5) 첫번째 원소 반환 함수

	T Back() // 6) 마지막 원소 반환 함수
	{
		while (last->link != 0) last = last->link;
		return last->data;
	}

	T Get(int i) // 7) i번째 원소 반환 함수
	{
		ChainNode<T> *find = first;
		while (i--)
		{
			if (find->link == NULL) break;
			find = find->link;
		}
		return find->data;
	}

	int DeleteFront() // 8) 맨 앞 원소 삭제 함수
	{
		ChainNode<T> *tmp = first;
		if (first->link == 0) return -1;
		first = first->link;
		delete tmp;
		return 0;
	}

	int DeleteBack() // 9) 맨 뒤 원소 삭제 함수
	{
		last = first;
		while (last->link->link != 0) last = last->link;
		if (last == first) return -1;
		delete last->link->link;
		last->link = NULL;
		return 0;
	}

	void InsertNext(int i, T x) // 10) i번째 원소 뒤 삽입 함수
	{
		ChainNode<T> *pt = first;
		ChainNode<T> *tmp = new ChainNode<T>(x, NULL);
		while (--i) pt = pt->link;
		tmp->link = pt->link;
		pt->link = tmp;
	}

	int DeleteNext(int i) // 11) i번째 원소 삭제 함수
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

	class iter // 12) 반복자
	{
	private:
		ChainNode<T> *it;
	public:// '=', '++', '!=', '*' 연산자 오버로딩
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

	void PrintAll() // 반복자를 이용한 전체출력함수
	{
		iter i;
		cout << "전체 원소 : ";
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

	for(int i=1;i<=9;i++) a.InsertBack(i);        // TEST1
	a.PrintAll();                                 // TEST2
	a.InsertFront(0);                             // TEST3
	a.PrintAll();                                 // TEST4
	a.InsertBack(10);                             // TEST5
	a.PrintAll();                                 // TEST6
	cout << "Front 원소 : " << a.Front() << endl; // TEST7
	cout << "Back 원소 : " << a.Back() << endl;   // TEST8
	cout << "2번째 원소 : " << a.Get(2) << endl;  // TEST9
	a.DeleteFront();                             // TEST10
	a.PrintAll();                                // TEST11
	a.DeleteBack();                              // TEST12
	a.PrintAll();                                // TEST13
	a.InsertNext(3, 100);                        // TEST14
	a.PrintAll();                                // TEST15
	a.DeleteNext(6);                             // TEST16
	a.PrintAll();                                // TEST17

	return 0;
}
```
