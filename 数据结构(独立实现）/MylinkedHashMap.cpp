#include<list>
#include<iostream>
#include<unordered_map>
#include<vector>
using namespace std;
template<typename K,typename V>
struct Node
{
	Node* prev;
	Node* next;
	K key;
	V val;
	Node(K key, V val) :key(key), val(val), prev(nullptr), next(nullptr) {}
};
template<typename K, typename V>
class MylinkedHashMap
{
public:
	MylinkedHashMap()
	{
		head = new Node<K, V>(K(), V());
		tail = new Node<K, V>(K(), V());
		head->next = tail;
		tail->prev = head;
	}
	~MylinkedHashMap()
	{
		Node<K, V>* current = head->next;
		while (current != tail) {
			Node<K, V>* next = current->next;
			delete current;
			current = next;
		}
		// 释放头尾节点
		delete head;
		delete tail;
	}
	MylinkedHashMap(const MylinkedHashMap&) = delete;
	MylinkedHashMap& operator=(const MylinkedHashMap&) = delete;
	V get(K key)
	{
		if (map.find(key) == map.end())
		{
			return V();
		}
		return map[key]->val;
	}
	void put(K key,V val)
	{
		if (map.find(key) == map.end())
		{
			Node<K, V>* node = new Node<K, V>(key, val);
			addlastNode(node);
			map[key] = node;
			return;
		}
		map[key]->val=val;
	}
	void remove(K key)
	{
		// 若 key 本不存在，直接返回
		if (map.find(key) == map.end())
		{
			return;
		}
		// 若 key 存在，则需要同时在哈希表和链表中删除
		Node<K, V>* node = map[key];
		map.erase(key);
		removeNode(node);
		// 释放节点内存
		delete node;
	}
	bool containsKey(K key)
	{
		return map.find(key) != map.end();
	}
	vector<K> keys()
	{
		vector<K> keyList;
		for (Node<K, V>* p = head->next; p != tail; p = p->next) {
			keyList.push_back(p->key);
		}
		return keyList;
	}
	size_t size()
	{
		return map.size();
	}
	bool empty()
	{
		return map.empty();
	}
private:
	Node<K, V>* head;
	Node<K, V>* tail;
	unordered_map<K, Node<K, V>*>map;
	void addlastNode(Node<K, V>* x)
	{
		Node* temp = tail->prev;
		x->next = tail;
		x->prev = temp;

		temp->next = x;
		tail->prev = x;
	}
	void removeNode(Node<K, V>* x)
	{
		Node<K, V>* prev = x->prev;
		Node<K, V>* next = x->next;

		prev->next = next;
		next->prev = prev;

		x->next = x->prev = nullptr;
	}
};
