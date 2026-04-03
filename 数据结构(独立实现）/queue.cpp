#include<list>
using namespace std;
template<typename E>
class queue
{
private:
	list<E>q;
public:
	queue() {};
	bool isempty()
	{
		return q.size() == 0;
	}
	void push(const E& val)
	{
		q.push_back(val);
	}
	void pop()
	{
		if (isempty())return;
		q.pop_front();
	}
	E peek()
	{
		if (isempty())return E();
		return q.front();
	}
	int size()const
	{
		return q.size();
	}
};