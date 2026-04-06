#include<iostream>
#include<functional>
#include<vector>
#include<stdexcept>
template<typename T>
class mypriorityqueue
{
private:
	std::vector<T>heap;

	int size;

	std::function<bool(const T&, const T&)>comparator;

	int parent(int node)
	{
		return (node - 1) / 2;
	}
	int left(int node)
	{
		return node * 2 + 1;
	}
	int right(int node)
	{
		return node * 2 + 2;
	}
	void swap(int i, int j)
	{
		std::swap(heap[i], heap[j]);
	}
	void resize(int capacity)
	{
		if (capacity > size)
		{
			heap.resize(capacity);
		}
	}
	void swim(int node)
	{
		while (node > 0 && comparator(heap[parent(node)], heap[node]))
		{
			swap(parent(node), node);
			node = parent(node);
		}
	}
	void sink(int node)
	{
		while (left(node) < size || right(node) < size) {
			// 比较自己和左右子节点，看看谁最小
			int min = node;
			if (left(node) < size && comparator(heap[min], heap[left(node)])) {
				min = left(node);
			}
			if (right(node) < size && comparator(heap[min], heap[right(node)])) {
				min = right(node);
			}
			if (min == node) {
				break;
			}
			swap(node, min);
			node = min;
		}
	}
public:
	mypriorityqueue(int capacity, std::function<bool(const T&, const T&)> comparator)
		: heap(capacity), size(0), comparator(std::move(comparator)) {
	}

	int getsize()const
	{
		return size;
	}
	bool isempty()const
	{
		return size == 0;
	}
	const T& peek()const
	{
		if (isempty())
		{
			throw std::underflow_error("Priority queue underflow");
		}
		return heap[0];
	}
	void push(const T& x)
	{
		if (size == heap.size())
		{
			resize(2 * heap.size());
		}
		heap[size] = x;
		swim(size);
		size++;
	}
	T pop()
	{
		if (isempty())
		{
			throw std::underflow_error("Priority queue underflow");
		}
		T res = heap[0];
		swap(0, size - 1);
		size--;
		sink(0);
		if (size > 0 && size == heap.size() / 4)
		{
			resize(heap.size() / 2);
		}
		return res;
	}
};