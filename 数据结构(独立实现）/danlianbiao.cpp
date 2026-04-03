#include<iostream>
#include<stdexcept>
#include<string>
using namespace std;
template<typename E>
class Danlianbiao
{
private:
	struct ListNode
	{
		E val;
		ListNode* next;
		ListNode(E value) :val(value), next(nullptr) {};
	};
	ListNode* head;
	ListNode* tail;
	int size;
public:
	Danlianbiao()
	{
		head = new ListNode(E());
		tail = head;
		size = 0;
	}
	~Danlianbiao()
	{
		ListNode* current = head;
		while (current != nullptr) 
		{
			ListNode* next = current->next;
			delete current;
			current = next;
		}
	}
	void addFirst(E e)
	{
		ListNode* newnode = new ListNode(e);
		ListNode* temp = head->next;
		newnode->next = temp;
		head->next = newnode;
		if (size == 0)
		{
			tail = newnode;
		}
		size++;
	}
	void addLast(E e)
	{
		ListNode* newnode = new ListNode(e);
		tail->next = newnode;
		tail = newnode;
		size++;
	}
	void add(int index, E element)
	{
		checkPositionIndex(index);
		if (index == size)
		{
			addLast(element);
			return;
		}
		ListNode* prev = head;
		for (int i = 0; i < index; ++i)
		{
			prev = prev->next;
		}
		ListNode* newnode = new ListNode(element);
		ListNode* temp = prev->next;
		prev->next = newnode;
		newnode->next = temp;
		size++;
	}
	E removeFirst()
	{
		if (isEmpty())
		{
			throw std::out_of_range("No elements to remove");
		}
		ListNode* temp = head->next;
		head->next = head->next->next;
		if (size == 1)
		{
			tail = head;
		}
		size--;
		E val = temp->val;
		delete temp;
		return val;
	}
	E removeLast()
	{
		if (isEmpty())
		{
			throw std::out_of_range("No elements to remove");
		}
		ListNode* prev = head;
		while (prev->next!= tail)
		{
			prev = prev->next;
		}
		E val = tail->val;
		delete tail;
		prev->next = nullptr;
		tail = prev;
		size--;
		return val;
	}
	E remove(int index)
	{
		checkElementIndex(index);
		ListNode* p = head;
		for (int i = 0; i < index; ++i)
		{
			p = p->next;
		}
		ListNode* l = p->next;
		p->next = l->next;
		if (index == size - 1)
		{
			tail = p;
		}
		size--;
		E val = l->val;
		delete l;
		return val;
	}
	E getFirst()
	{
		if (isEmpty()) 
		{
			throw std::out_of_range("No elements in the list");
		}
		return head->next->val;
	}
	E getLast()
	{
		if (isEmpty()) 
		{
			throw std::out_of_range("No elements in the list");
		}
		return tail->val;
	}
	E get(int index)
	{
		checkElementIndex(index);
		ListNode* p = getNode(index);
		return p->val;
	}
	E set(int index, E element)
	{
		checkElementIndex(index);
		ListNode* p = getNode(index);
		E oldval = p->val;
		p->val = element;
		return oldval;
	}
	
	int size_() 
	{
		return size;
	}
	vector<int> display()
	{
		vector<int>res;
		if (head != nullptr)
		{
			res.push_back(head->val);
			head = head->next;
		}
		return res;
	}
	bool isEmpty() 
	{
		return size == 0;
	}
	bool isElementIndex(int index) {
		return index >= 0 && index < size;
	}

	bool isPositionIndex(int index) {
		return index >= 0 && index <= size;
	}

	// 检查 index 索引位置是否可以存在元素
	void checkElementIndex(int index) {
		if (!isElementIndex(index)) {
			throw std::out_of_range("Index: " + std::to_string(index) + ", size_: " + std::to_string(size));
		}
	}

	// 检查 index 索引位置是否可以添加元素
	void checkPositionIndex(int index) 
	{
		if (!isPositionIndex(index)) 
		{
			throw std::out_of_range("Index: " + std::to_string(index) + ", size_: " + std::to_string(size));
		}
	}

	// 返回 index 对应的 Node
	// 注意：请保证传入的 index 是合法的
	ListNode* getNode(int index) {
		ListNode* p = head->next;
		for (int i = 0; i < index; ++i)
		{
			p = p->next;
		}
		return p;
	}
};