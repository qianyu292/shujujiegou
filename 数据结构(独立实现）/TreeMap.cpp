#include <iostream>
#include <functional>
#include <memory>
#include <vector>
#include <list>
#include <stdexcept>
#include <iterator>
template<typename K,typename V>
class MyTreeMap
{
private:
	struct Treenode
	{
		K key;
		V val;
		std::shared_ptr<Treenode>left;
		std::shared_ptr<Treenode>right;
		int size;
		Treenode(K key, V val) :key(key), val(val), left(nullptr), right(nullptr), size(1) {}

	};
	std::shared_ptr<Treenode>root;
public:
	MyTreeMap() :root(nullptr) {}
	// **** 增/改 ****
   // 添加 key -> val 键值对，如果键 key 已存在，则将值修改为 val
	V put(const K& key, const V& val)
	{
		if (!root)
		{
			root = std::make_shared<Treenode>(key,val);
			return V();
		}
		V oldval = get(key);
		root = put(root, key, val);
		return oldval;
	}
	// **** 删 ****
	// 删除 key 并返回对应的 val
	V remove(const K& key)
	{
		if (!containsKey(key))
		{
			return V();
		}
		V oldval = get(key);
		root = remove(root, key);
		return oldval;
	}
	// 删除并返回 BST 中最小的那个 key
	void removeMin()
	{
		if (isEmpty())
		{
			throw std::out_of_range("Tree is empty");
		}
		root = removeMin(root);
	}
	// 删除并返回 BST 中最大的那个 key
	void removeMax() 
	{
		if (isEmpty()) {
			throw std::out_of_range("Tree is empty");
		}
		root = removeMax(root);
	}
	V get(const K& key)const
	{
		auto node = get(root, key);
		if (!node)
		{
			return V();
		}
		return node->val;
	}
	// 返回小于等于 key 的最大的键
	K floorKey(const K& key)const
	{
		if (isEmpty()) {
			throw std::out_of_range("Tree is empty");
		}
		auto node = floorkey(root, key);
		if (!node) {
			throw std::out_of_range("No floor key found");
		}
		return node->key;
	}
	// 返回大于等于 key 的最小的键
	K ceilingKey(const K& key) const
	{
		if (isEmpty()) {
			throw std::out_of_range("Tree is empty");
		}

		auto node = ceilingKey(root, key);
		if (!node) {
			throw std::out_of_range("No ceiling key found");
		}
		return node->key;
	}
	int rank(const K& key) const {
		return rank(root, key);
	}
	K select(int i)const
	{
		if (i < 0 || i >= size())
		{
			throw std::out_of_range("Index out of range");
		}
		auto node = select(root, i);
		return node->key;
	}
	// 返回 BST 中最大的键
	K maxKey() const
	{
		if (isEmpty()) {
			throw std::out_of_range("Tree is empty");
		}
		return maxNode(root)->key;
	}
	// 返回 BST 中最小的键
	K minKey() const
	{
		if (isEmpty()) {
			throw std::out_of_range("Tree is empty");
		}
		return minNode(root)->key;
	}
	// 判断 key 是否存在 Map 中
	bool containsKey(const K& key) const
	{
		return get(root, key) != nullptr;
	}
	// 从小到大返回闭区间 [min, max] 中的键
	std::vector<K> keys(const K& min, const K& max) const
	{
		std::vector<K> result;
		traverse(root, result,min,max);
		return result;
	}
	int size() const
	{
		return size(root);
	}
	bool isEmpty() const
	{
		return size() == 0;
	}
private:
	std::shared_ptr<Treenode>put(std::shared_ptr<Treenode>node, const K& key, const V& val)
	{
		if (node == nullptr)
		{
			return std::make_shared<Treenode>(key, val);
		}
		if (node->key > key)
		{
			node->left = put(node->left, key, val);
		}
		else if (node->key < key)
		{
			node->right = put(node->right, key, val);
		}
		else
		{
			node->val = val;
		}
		node->size = size(node->left) + size(node->right) + 1;

		return node;
	}
	std::shared_ptr<Treenode>remove(std::shared_ptr<Treenode>node, const K& key)
	{
		if (node == nullptr)
		{
			return nullptr;
		}
		if (node->key > key)
		{
			node->left = remove(node->left, key);
		}
		else if (node->key < key)
		{
			node->right = remove(node->right, key);
		}
		else
		{
			if (!node->left)return node->right;
			if (!node->right)return node->left;

			auto leftmax = maxNode(node->left);
			node->left = removeMax(node->left);
			leftmax->left = node->left;
			leftmax->right = node->right;
			node = leftmax;
		}
		node->size = size(node->left) + size(node->right) + 1;

		return node;
	}
	std::shared_ptr<Treenode> removeMin(std::shared_ptr<Treenode> node)
	{
		if (!node->left)return node->right;

		node->left = removeMin(node->left);

		node->size = size(node->left) + size(node->right) + 1;

		return node;
	}
	std::shared_ptr<Treenode> removeMax(std::shared_ptr<Treenode> node)
	{
		if (!node->right)return node->left;

		node->right = removeMax(node->right);

		node->size= size(node->left) + size(node->right) + 1;

		return node;
	}
	std::shared_ptr<Treenode>get(std::shared_ptr<Treenode> node, const K& key)const
	{
		if (node == nullptr)
		{
			return nullptr;
		}
		if (node->key < key)
		{
			return get(node->right, key);
		}
		else if (node->key > key)
		{
			return get(node->left, key);
		}
		else
		{
			return node;
		}
	}
	std::shared_ptr<Treenode> floorKey(std::shared_ptr<Treenode> node, const K& key)
	{
		if (!node)
		{
			return nullptr;
		}
		if (node->key > key)
		{
			return floorKey(node->left, key);
		}
		if (node->key < key)
		{
			auto x = floorKey(node->right, key);
			if (x == nullptr)
			{
				return node;
			}
			return x;
		}
		return node;
	}
	std::shared_ptr<Treenode> ceilingKey(std::shared_ptr<Treenode> node, const K& key) const
	{
		if (!node)
		{
			return nullptr;
		}
		if (node->key < key)
		{
			return ceilingKey(node->right, key);
		}
		if (node->key > key)
		{
			auto x = ceilingKey(node->left, key);
			if (x == nullptr)
			{
				return node;
			}
			return x;
		}
		return node;
	}
	int rank(std::shared_ptr<Treenode> node, const K& key) const
	{
		if (!node)
		{
			return 0;
		}
		if (key < node->key)
		{
			return rank(node->left, key);
		}
		else if (key > node->key)
		{
			return size(node->left) + 1 + rank(node->right, key);
		}
		else
		{
			return size(node->left);
		}
	}
	std::shared_ptr<Treenode> select(std::shared_ptr<Treenode> node, int i) const
	{
		int n = size(node->left);
		if (n < i)
		{
			return select(node->right, i-n-1);
		}
		else if (n > i)
		{
			return select(node->left, i);
		}
		else
		{
			return node;
		}
	}
	std::shared_ptr<Treenode> maxNode(std::shared_ptr<Treenode> node) const
	{
		while (node->right != nullptr)
		{
			node = node->right;
		}
		return node;
	}
	std::shared_ptr<Treenode> minNode(std::shared_ptr<Treenode> node) const
	{
		while (node->left != nullptr)
		{
			node = node->left;
		}
		return node;
	}
	void traverse(std::shared_ptr<Treenode> node, std::vector<K>& result) const
	{
		if (!node)return;
		traverse(node->left,result);
		result.push_back(node->key);
		traverse(node->right,result);
	}
	void traverse(std::shared_ptr<Treenode> node, std::vector<K>& result,
		const K& min, const K& max) const
	{
		if (node == nullptr) {
			return;
		}

		if (min < node->key) {
			// min < node.key
			traverse(node->left, result, min, max);
		}

		// 中序遍历 min <= node.key <= max
		if (min <= node->key && max >= node->key) {
			result.push_back(node->key);
		}

		if (max > node->key) {
			// max > node.key
			traverse(node->right, result, min, max);
		}
	}
	int size(std::shared_ptr<Treenode> node) const
	{
		if (node == nullptr)
		{
			return 0;
		}
		return node->size;
	}
};