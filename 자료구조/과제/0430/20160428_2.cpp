#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>
using namespace std;

template<typename T>
inline T Mymin(T x, T y) { return x > y ? y : x; }

template <typename T>
class Bag
{
private:
	T *array;
	int capacity;
	int top;

public:
	Bag(int bagCapacity = 3);
	~Bag();
	int Size() const;
	bool IsEmpty() const;
	T& Element() const;
	void Push(const T&);
	void Pop();
};

template <typename T>
Bag<T>::Bag(int bagCapacity) : capacity(bagCapacity){
	if (capacity < 1) 
		throw "Capacity must be > 0";						// Bag�� �뷮�� 1���� ������� ����ó��
	array = new T[capacity];								// �Ű������κ��� ���޹��� ũ��(�⺻ : 3)�� bag������ ����
	top = -1;												// Bag�� ������ �����͸� ����Ű�� top�� -1�� �ʱ�ȭ
}

template <typename T>
Bag<T>::~Bag() { delete[] array; }							// �������� �Ҵ��� array�� �Ҹ��ڿ��� ����

template <typename T>
inline int Bag<T>::Size() const { return top + 1; }			// �ֻ�� �������� ��ġ�� �̿��Ͽ� Bag ũ�� ���

template <typename T>
inline bool Bag<T>::IsEmpty() const { return Size() == 0; }	// Size�Լ��� �̿��Ͽ� Bag�� ���� ���� �Ǵ�

template <typename T>
T& Bag<T>::Element() const
{
	if (Size() == 0) 
		throw "Bag is empty, bag has not any element";		// Bag�� ����� 0�ΰ�� ���Ұ� �����Ƿ� ����ó��
	return (!top ? *array : *(array + (rand() % top)));		// �������ҹ�ȯ(top�� 0���� ���Ұ� 1���ΰ�� �ش���� ��ȯ)
}




template <typename T>
void Bag<T>::Push(const T& x)
{
	if (capacity == top + 1)								// Bag�� ���Ұ� �������� ������ ��� ����� 2�� Ȯ��
	{
		ChangeSize1D(array, capacity, 2 * capacity);		
		capacity *= 2;
	}
	array[++top] = x;										// �Ű������� ���޹��� ���� (������������ ��ġ+1)�� �߰�
}

template <class T>											// �����������ڸ� �̿��Ͽ� �迭�� ũ�⸦ Ȯ��
void ChangeSize1D(T*& a, const int oldSize, const int newSize)
{
	T* temp = new T[newSize];
	int number = Mymin(oldSize, newSize);
	copy(a, a + number, temp);
	delete[] a;
	a = temp;
	cout << "Bag Size is changed : " << oldSize << " to " << newSize << endl;
}

template <typename T>
void Bag<T>::Pop()											// �迭�� ���� ����
{
	if (IsEmpty()) throw "Bag is empty, cannot delete";		// ������ �����Ͱ� ���� ��� ����ó��
	int deletePos = top / 2;
	copy(array + deletePos + 1, array + top + 1, array + deletePos);
	top--;
}

class Bizcard
{
private:
	char *name;
	char *phone;
public:
	Bizcard() : name(NULL),phone(NULL) {};					// �Ű������� ���°�� NULL�� �ʱ�ȭ�ϴ� ������
	Bizcard(char* myname, char* myphone)					// �̸��� ��ȭ��ȣ�� �Է¹޾� �����޸� ������ �ϴ� ������
	{
		name = new char[strlen(myname) + 1];
		phone = new char[strlen(myphone) + 1];
		strcpy(name, myname);
		strcpy(phone, myphone);
	}
	Bizcard(const Bizcard& data)							// ���� ������
	{
		name = new char[strlen(data.name) + 1];
		phone = new char[strlen(data.phone) + 1];
		strcpy(name, data.name);
		strcpy(phone, data.phone);
	}
	Bizcard& operator=(const Bizcard& data)					// ���� ������ �����ε�
	{
		name = new char[strlen(data.name) + 1];
		phone = new char[strlen(data.phone) + 1];
		strcpy(name, data.name);
		strcpy(phone, data.phone);
		return *this;
	}
	~Bizcard()												// �Ҹ���
	{
		if(name) delete[] name;
		if(phone) delete[] phone;
	}
	void Showinfo()											// �̸��� ��ȭ��ȣ�� ����ϴ� �Լ�
	{
		cout << "�̸� : " << name;
		cout << " ��ȭ��ȣ : " << phone << endl;
	}
};


int main()
{
	Bag<Bizcard> a;
	srand(time(NULL));

	cout << "--------����ִ� Bag---------" << endl;
	try {
		cout << "Size : " << a.Size() << endl;
		cout << ((a.IsEmpty() == 1) ? "Bag is Empty" : "Bag is not Empty") << endl;
		a.Element().Showinfo();
	}
	catch (const char *s) { cout << s << endl; }


	cout << endl << "--------Push 3ȸ-----------" << endl;
	try {
		a.Push(*new Bizcard("Kim", "010-9745-7296"));
		a.Push(*new Bizcard("Lee", "011-1234-5678"));
		a.Push(*new Bizcard("Park", "010-9876-5431"));

		cout << "Size : " << a.Size() << endl;
		cout << ((a.IsEmpty() == 1) ? "Bag is Empty" : "Bag is not Empty") << endl;
		a.Element().Showinfo();
	}
	catch (const char *s) { cout << s << endl; }


	cout << endl << "--------Push 4ȸ-----------" << endl;
	try {
		a.Push(*new Bizcard("Mun", "001-0001-0001"));
		a.Push(*new Bizcard("Hong", "002-0002-0002"));
		a.Push(*new Bizcard("Ahn", "003-0003-0003"));
		a.Push(*new Bizcard("Yu", "004-0004-0004"));
		cout << "Size : " << a.Size() << endl;
		cout << ((a.IsEmpty() == 1) ? "Bag is Empty" : "Bag is not Empty") << endl;
		a.Element().Showinfo();
	}
	catch (const char *s) { cout << s << endl; }
	

	cout << endl << "--------Pop 2ȸ-----------" << endl;
	try {
		a.Pop();
		a.Pop();
		cout << "Size : " << a.Size() << endl;
		cout << ((a.IsEmpty() == 1) ? "Bag is Empty" : "Bag is not Empty") << endl;
		a.Element().Showinfo();
	}
	catch (char *s) { cout << s << endl; }

	return 0;
}