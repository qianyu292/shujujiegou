#include<list>
#include <stdexcept>
using std::list;
template<typename E>
class myqueue
{
private:
	list<E>queue;
public:
	void push_back(const E& e)
	{
		queue.push_back(e);
	}
	void push_front(const E& e)
	{
		queue.push_front(e);
	}
	E pop_front()
	{
		E front = queue.front();
		queue.pop_front();
		return front;
	}
	E pop_back()
	{
		E back = queue.back();
		queue.pop_back();
		return back;
	}
	E peek_front()
	{
		return queue.front();
 	}
	E peek_back()
	{
		return queue.back();
	}
};