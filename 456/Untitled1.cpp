#include<iostream>
#include<string.h>

using namespace std;

class ArrayStack
{
private:
	int maxSize;
	int top=-1;
	char *Array;
public:
	ArrayStack(int size);
	void clear();
	bool IsEmpty();
	bool IsFull();
	void Push(char n);
	char Pop();
	char Top();
	int getTop();
	void InToPost(char * str);
	bool match(char *);
};
ArrayStack::ArrayStack(int size)
{
	this->maxSize = size;
	Array = new char[size];
}
void ArrayStack::clear()
{
	top = -1;
}
bool ArrayStack::IsEmpty()
{
	if (top == -1)
		return true;
	return false;
}
bool ArrayStack::IsFull()
{
	if (top == maxSize - 1)
		return true;
	return false;
}
void ArrayStack::Push(char n)
{
	if (IsFull())
		cout << "FULL" << endl;
	else
	{
		Array[++top] = n;
	}
}
char ArrayStack::Pop()
{
	char temp;
	if (IsEmpty() == 0)
	{
		temp = Array[top];
		top--;
		return temp;
	}
}
char ArrayStack::Top()
{
	if (IsEmpty() == 0)
		return Array[top];
}
int ArrayStack::getTop()
{
	return top;
}
bool ArrayStack::match(char * str)
{
	int len = strlen(str);
	for (int i = 0; i < len; i++)
	{
		switch (str[i])
		{
		case '{':
		case '[':
		case '(':
			Push(str[i]);
			break;
		case ')':
			if (Pop() == '(')
				break;
			else
				return false;
		case ']':
			if (Pop() == '[')
				break;
			else
				return false;
		case '}':
			if (Pop() == '{')
				break;
			else
				return false;
		default:
			break;
		}
	}
	return true;
}
void ArrayStack::InToPost(char * str)
{
	int i = 0;
	int j = 0;
	char PostfixExp[20] = { 0 };
	int len = strlen(str);
	for (i = 0; i < len; i++)
	{
		switch (str[i])
		{
		case '0': case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':
			PostfixExp[j] = str[i];
			j++;
			break;
		case '{': case '[':	case '(':
			Push(str[i]);
			break;
		case '*':	case '/':
			while ( Top() == '*' || Top() == '/')
			{
				PostfixExp[j] = Pop();
				j++;
			}
			Push(str[i]);
			break;
		case ')':
			while (Top() != '(')
			{
				PostfixExp[j] = Pop();
				j++;
			}
			Pop();
			break;
		case ']':
			while (Top() != '[')
			{
				PostfixExp[j] = Pop();
				j++;
			}
			Pop();
			break;
		case '}':
			while (Top() != '{')
			{
				PostfixExp[j] = Pop();
				j++;
			}
			Pop();
			break;
		case '+': case '-':
			while (Top() == '+' || Top() == '-' || Top() == '*' || Top() == '/' || Top() == '%')
			{
				PostfixExp[j] = Pop();
				j++;
			}
			Push(str[i]);
			break;
		default:
			break;
		}
	}
	while (IsEmpty() == 0)
	{
		PostfixExp[j] = Pop();
		j++;
	}
	clear();
	cout << "后缀表达式为：" << endl;
	for (i = 0; i < len; i++)
		cout << PostfixExp[i];
	cout << endl;
	clear();
	len = strlen(PostfixExp);
	int result = 0;
	int left = 0;
	int right = 0;
	for (i = 0; i < len; i++)
	{
		switch (PostfixExp[i])
		{
		case '0': case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':
			Push(PostfixExp[i]);
			break;
		case '+':
			right = Pop() - 48;
			left = Pop() - 48;
			result = left + right;
			Push(result + 48);
			break;
		case '-':
			right = Pop() - 48;
			left = Pop() - 48;
			result = left - right;
			Push(result + 48);
			break;
		case '*':
			right = Pop() - 48;
			left = Pop() - 48;
			result = left * right;
			Push(result + 48);
			break;
		case '/':
			right = Pop() - 48;
			left = Pop() - 48;
			if (right == 0)
				cout << "表达式错误" << endl;
			else
				result = left / right;
			Push(result + 48);
			break;
		default:
			break;
		}
	}
	cout <<"表达式结果为： "<< result << endl;
	clear();
}

int main()
{
	char str[100] = { 0 };
	ArrayStack A(15);
	while (1)
	{
		cout << "请输入表达式：" << endl;
		cin >> str;
		if (A.match(str) && A.getTop() == -1)
			A.InToPost(str);
		else
			cout << "括号匹配错误" << endl;
		A.clear();
	}
	return 0;
}
