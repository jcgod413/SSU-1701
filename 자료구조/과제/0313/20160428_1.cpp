#include <iostream>
using namespace std;

typedef struct div {
	int quot;
	int rem;
} D;

D divide(int num1, int num2);

int main()
{
	int num1=0, num2=0;
	D result;
	while (1)
	{
		cout << "나눗셈을 진행할 두 정수를 입력해 주세요 : ";
		cin >> num1 >> num2;
		try
		{
			result = divide(num1, num2);
			cout << num1 << " / " << num2 << " = " << result.quot << ", " << num1 << " % " << num2 << " = " << result.rem << endl;
			break;
		}
		catch (int tmp1)
		{
			cout << tmp1 << "으로 나눌 수 없습니다." << endl;
			cout << "재입력을 진행합니다" << endl << endl;
		}
	}
	return 0;
}

D divide(const int num1, const int num2)
{
	D calc;
	if (num2 == 0) throw 0;
	calc.quot = num1 / num2;
	calc.rem = num1 % num2;
	return calc;
}