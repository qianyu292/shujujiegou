//动态数组
#include<iostream>
#include<stdexcept>
#include<vector>
template<typename E>
class Myarraylist
{
private:
	E* data;//真正记录数据的底层数组

	int size;//当前元素个数

	int cap;//最大容量

	static const int INIT_CAP = 1;
public:
	Myarraylist()//初始化
	{
		this->data = new E[INIT_CAP];
		this->size = 0;
		this->cap = INIT_CAP;
	}
	Myarraylist(int initcapacity)//分配内存
	{
		this->data = new E[initcapacity];
		this->size = 0;
		this->cap = initcapacity;
	}
	~Myarraylist()
	{
		delete[]data;
	}
	//增
	void addlast(E e)
	{
		if (size == cap)
		{
			resize(cap * 2);
		}
		data[size] = e;
		size++;
	}
	void addfirst(E e)
	{
		if (size == cap) {
			resize(cap * 2);
		}
		for (int i = size; i > 0; --i)
		{
			data[i] = data[i-1];
		}
		data[0] = e;
		size++;
	}
	void add(int index, E e)//指定位置插入
	{
		checkPositionIndex(index);
		if (size == cap)
		{
			resize(cap * 2);
		}
		for (int i = size - 1; i >= index; --i)
		{
			data[i + 1] = data[i];
		}
		data[index] = e;

		size++;
	}
	//删
	E removelast()
	{
		if (size == 0) {
			throw std::out_of_range("NoSuchElementException");
		}
		if (size == cap / 4)
		{
			resize(cap / 2);
		}
		E deleteval = data[size - 1];

		data[size - 1] = E();
		size--;

		return deleteval;
	}
	E removefirst()
	{
		if (size == 0) {
			throw std::out_of_range("NoSuchElementException");
		}
		if (size == cap / 4)
		{
			resize(cap / 2);
		}
		E firstval = data[0];
		for (int i = 0; i <size-1;++i)
		{
			data[i] = data[i+1];
		}
		size--;
		return firstval;
	}
	E remove(int index)
	{
		if (size == 0) {
			throw std::out_of_range("NoSuchElementException");
		}
		if (size == cap / 4)
		{
			resize(cap / 2);
		}
		E dataval = data[index];
		for (int i = index; i < size-1;++i)
		{
			data[i] = data[i + 1];
		}
		data[size - 1] = E();
		size--;
		return dataval;
	}
	//查
	E get(int index)
	{
		checkPositionIndex(index);

		return data[index];
	}
	//改
	E set(int index, E element)
	{
		checkPositionIndex(index);

		E temp = data[index];

		data[index] = element;
		
		return temp;
	}
private:
	//工具方法
	int getsize()
	{
		return size;
	}
	bool isEmpty()
	{
		return this->size == 0;
	}
	void resize(int newcap)//重新分配内存
	{
		E* temp = new E[newcap];

		for (int i = 0; i < size; ++i)
		{
			temp[i] = data[i];
		}
		delete[]data;
		data = temp;
		cap = newcap;
	}
	bool isElementIndex(int index)
	{
		return index >= 0 && index < size;
	}
	bool isPositionIndex(int index)
	{
		return index >= 0 && index <= size;
	}
	void checkElementIndex(int index)
	{
		if (!isElementIndex(index))
		{
			throw std::out_of_range("Index out of bounds");
		}
	}
	void checkPositionIndex(int index)
	{
		if (!isPositionIndex(index))
		{
			throw std::out_of_range("Index out of bounds");
		}
	}
public:
	void display()
	{
		std::cout << "size:" << size << "cap" << cap << std::endl;
		for (int i = 0; i < size; ++i)
		{
			std::cout << data[i] << " ";
		}
		std::cout << std::endl;

	}
};