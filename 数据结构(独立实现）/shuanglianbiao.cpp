#include<iostream>
#include<stdexcept>
#include<string>
template<typename E>
class Mylinkedlist
{
	struct Node
	{
		E val;
		Node* next;
		Node* prev;
		Node(E value) :val(value), next(nullptr), prev(nullptr) {}
	};
	Node* head;
	Node* tail;
	int size;
public:
	Mylinkedlist()
	{
		head = new Node();
		tail = new Node();
		head->next = tail;
		tail->prev = head;
		size = 0;
	}
	~Mylinkedlist()
	{
		while (size > 0)
		{
			removeFirst();
		}
		delete head;
		delete tail;
	}
	void addLast(E e)
	{
		Node* L = new Node(e);
		Node* temp = tail->prev;
		temp->next = L;
		L->prev = temp;

		L->next = tail;
		tail->prev = L;
		size++;
	}
	void addFirst(E e)
	{
		Node* x = new Node(e);
		Node* temp = head->next;
		
		temp->prev = x;
		x->next = temp;

		x->prev = head;
		head->next = x;

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
		Node* p = getNode(index);
		Node* temp = p->prev;
		Node* x = new Node(element);

		temp->next = x;
		x->prev = temp;

		x->next = p;
		p->prev = x;

		size++;
	}
	E removeFirst()
	{
		if (size < 1)
		{
			throw std::out_of_range("No elements to remove");
		}
		Node* temp = head->next;
		Node* newnode = temp->next;

		head->next = newnode;
		newnode->prev = head;

		E val = temp->val;
		delete temp;
		size--;
		return val;
	}
	E removeLast()
	{
		if (size < 1)
		{
			throw std::out_of_range("No elements to remove");
		}
		Node* x = tail->prev;
		Node* temp = x->prev;
		temp->next = tail;
		tail->prev = temp;

		E oldval = x->val;
		delete x;
		size--;
		return oldval;
	}
	E remove(int index)
	{
		checkElementIndex(index);
		Node* x = getNode(index);
		Node* temp1 = x->prev;
		Node* temp2 = x->next;

		temp1->next = temp2;
		temp2->prev = temp1;

		E oldval = x->val;
		size--;
		delete x;
		return oldval;
	}
	E get(int index)
	{
		checkElementIndex(index);

		Node* p = getNode(index);
		return p->val;
	}
	E getFirst()
	{
		if (size < 1)
		{
			throw std::out_of_range("No elements in the list");
		}
		return head->next->val;
	}
	E getLast()
	{
		if (size < 1)
		{
			throw std::out_of_range("No elements in the list");
		}
		return tail->prev->val;
	}
	E set(int index, E val)
	{
		checkElementIndex(index);
		Node* p = getNode(index);
		E oldval = p->val;
		p->val = val;
		return oldval;
	}
	int getsize()const
	{
		return size;
	}
	bool isempty()const
	{
		return size == 0;
	}
	void display()
	{
		std::cout << "size=" << size << std::endl;
		for (Node* p = head->next; p != tail; p = p->next)
		{
			std::cout << p->val << "<->";
		}
		std::cout << "nullptr" << std::endl;
		std::cout << std::endl;
	}
	void swap(ListNode* a, ListNode* b)
	{
		ListNode* temp1 = a->prev;
		ListNode* temp2 = b->next;

		temp1->next = b;
		b->prev = a;

		temp2->prev = a;
		a->next = temp2;
	}
private:
	Node* getNode(int index)
	{
		Node* p = head->next;
		for (int i = 0; i < index; ++i)
		{
			p = p->next;
		}
		return p;
	}
	bool isElementIndex(int index) const {
		return index >= 0 && index < size;
	}

	bool isPositionIndex(int index) const {
		return index >= 0 && index <= size;
	}
	void checkElementIndex(int index) const {
		if (!isElementIndex(index))
			throw std::out_of_range("Index: " + std::to_string(index) + ", Size: " + std::to_string(size));
	}

	// 检查 index 索引位置是否可以添加元素
	void checkPositionIndex(int index) const {
		if (!isPositionIndex(index))
			throw std::out_of_range("Index: " + std::to_string(index) + ", Size: " + std::to_string(size));
	}
};