#include<iostream>
#include<list>
#include<vector>
using namespace std;
template<typename E>
class stack1
{
	list<E>stack;
public:
	stack1(){}
	bool isempty()
	{
		return stack.size()==0;
	}
	void push(const E& val)
	{
		stack.push_back(val);
	}
	void pop()
	{
		if (isempty())return;
		stack.pop_back();
	}
	E peek()
	{
		if (isempty())return E();
		return stack.back();
	}
	int size()const
	{
		return stack.size();
	}
};
class stack2
{
	vector<int>arr;
	stack2() {};
	bool isempty()
	{
		return arr.size() == 0;
	}
	void push(const int& val)
	{
		arr.push_back(val);
	}
	void pop()
	{
		if (isempty())return;
		arr.pop_back();
	}
	int top()
	{
		if (isempty())return -1;
		return arr.back();
	}
	int size()const
	{
		return arr.size();
	}
};