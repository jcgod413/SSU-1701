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
		throw "Capacity must be > 0";						// Bag의 용량이 1보다 작은경우 예외처리
	array = new T[capacity];								// 매개변수로부터 전달받은 크기(기본 : 3)로 bag사이즈 변경
	top = -1;												// Bag의 마지막 데이터를 가르키는 top을 -1로 초기화
}

template <typename T>
Bag<T>::~Bag() { delete[] array; }							// 동적으로 할당한 array를 소멸자에서 삭제

template <typename T>
inline int Bag<T>::Size() const { return top + 1; }			// 최상단 데이터의 위치를 이용하여 Bag 크기 출력

template <typename T>
inline bool Bag<T>::IsEmpty() const { return Size() == 0; }	// Size함수를 이용하여 Bag의 공백 여부 판단

template <typename T>
T& Bag<T>::Element() const
{
	if (Size() == 0) 
		throw "Bag is empty, bag has not any element";		// Bag의 사이즈가 0인경우 원소가 없으므로 예외처리
	return (!top ? *array : *(array + (rand() % top)));		// 랜덤원소반환(top이 0으로 원소가 1개인경우 해당원소 반환)
}




template <typename T>
void Bag<T>::Push(const T& x)
{
	if (capacity == top + 1)								// Bag의 원소가 마지막에 도달한 경우 사이즈를 2배 확장
	{
		ChangeSize1D(array, capacity, 2 * capacity);		
		capacity *= 2;
	}
	array[++top] = x;										// 매개변수로 전달받은 값을 (마지막데이터 위치+1)에 추가
}

template <class T>											// 포인터참조자를 이용하여 배열의 크기를 확장
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
void Bag<T>::Pop()											// 배열의 원소 제거
{
	if (IsEmpty()) throw "Bag is empty, cannot delete";		// 제거할 데이터가 없는 경우 예외처리
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
	Bizcard() : name(NULL),phone(NULL) {};					// 매개변수가 없는경우 NULL로 초기화하는 생성자
	Bizcard(char* myname, char* myphone)					// 이름과 전화번호를 입력받아 동적메모리 접근을 하는 생성자
	{
		name = new char[strlen(myname) + 1];
		phone = new char[strlen(myphone) + 1];
		strcpy(name, myname);
		strcpy(phone, myphone);
	}
	Bizcard(const Bizcard& data)							// 복사 생성자
	{
		name = new char[strlen(data.name) + 1];
		phone = new char[strlen(data.phone) + 1];
		strcpy(name, data.name);
		strcpy(phone, data.phone);
	}
	Bizcard& operator=(const Bizcard& data)					// 대입 연산자 오버로딩
	{
		name = new char[strlen(data.name) + 1];
		phone = new char[strlen(data.phone) + 1];
		strcpy(name, data.name);
		strcpy(phone, data.phone);
		return *this;
	}
	~Bizcard()												// 소멸자
	{
		if(name) delete[] name;
		if(phone) delete[] phone;
	}
	void Showinfo()											// 이름과 전화번호를 출력하는 함수
	{
		cout << "이름 : " << name;
		cout << " 전화번호 : " << phone << endl;
	}
};


int main()
{
	Bag<Bizcard> a;
	srand(time(NULL));

	cout << "--------비어있는 Bag---------" << endl;
	try {
		cout << "Size : " << a.Size() << endl;
		cout << ((a.IsEmpty() == 1) ? "Bag is Empty" : "Bag is not Empty") << endl;
		a.Element().Showinfo();
	}
	catch (const char *s) { cout << s << endl; }


	cout << endl << "--------Push 3회-----------" << endl;
	try {
		a.Push(*new Bizcard("Kim", "010-9745-7296"));
		a.Push(*new Bizcard("Lee", "011-1234-5678"));
		a.Push(*new Bizcard("Park", "010-9876-5431"));

		cout << "Size : " << a.Size() << endl;
		cout << ((a.IsEmpty() == 1) ? "Bag is Empty" : "Bag is not Empty") << endl;
		a.Element().Showinfo();
	}
	catch (const char *s) { cout << s << endl; }


	cout << endl << "--------Push 4회-----------" << endl;
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
	

	cout << endl << "--------Pop 2회-----------" << endl;
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