#include<deque>
#include<cassert>
template <typename E>
class MonotonicQueue
{
private:
	// 常规队列，存储所有元素
	std::deque<E>q;
	// 元素降序排列的单调队列，头部是最大值
	std::deque<E>maxq;
	// 元素升序排列的单调队列，头部是最小值
	std::deque<E>minq;
public:
	void push(const E& elem)
	{
		q.push_back(elem);
		while (!maxq.empty() && maxq.back() < elem)
		{
			maxq.pop_back();
		}
		maxq.push_back(elem);
		while (!maxq.empty() && minq.back() > elem)
		{
			minq.pop_back();
		}
		minq.push_back(elem);
	}
	E max() const
	{
		assert(!maxq.empty());
		return maxq.front();
	}
	E min() const
	{
		assert(!minq.empty());
		return minq.front();
	}
	E pop()
	{
		E front = q.front();
		q.pop_front();
		if (front == maxq.front())
		{
			maxq.pop_front();
		}
		if (front == minq.front())
		{
			minq.pop_front();
		}
	}
	int size() const
	{
		return q.size();
	}
	bool isEmpty() const
	{
		return q.empty();
	}
};