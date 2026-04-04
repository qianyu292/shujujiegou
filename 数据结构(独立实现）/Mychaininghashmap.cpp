#include<list>
#include<vector>
#include<string>
#include<functional>
#include<algorithm>
template<typename K,typename V>
class Mychaininghashmap
{
private:
	struct KVnode
	{
		K key;
		V value;
		KVnode(K key, V val):key(key), value(std::move(val)){}
	};
	std::vector<std::list<KVnode>>table;

	int size;

	static constexpr int INIT_CAP = 4;

	int hash(K key)const
	{
		return (std::hash<K>{}(key) & 0x7fffffff) % table.size();
	}
	void resize(int newcap)
	{
		newcap = std::max(newcap, 1);
		Mychaininghashmap<K, V>newMap(newcap);
		for (auto& list : table) {
			for (auto& node : list) {
				// 将键值对转移到新的 HashMap 中
				newMap.put(node.key, node.value);
			}
		}
		// 将当前 HashMap 的底层 table 换掉
		this->table = newMap.table;
	}
public:
	Mychaininghashmap() : Mychaininghashmap(INIT_CAP) {
	}
	explicit Mychaininghashmap(int capacity)
	{
		size = 0;
		capacity = std::max(capacity, 1);
		table.resize(capacity);
	}
	//增
	void put(K key, V val)
	{
		auto& list = table[hash(key)];
		for (auto& node : list)
		{
			if (node.key == key)
			{
				node.value = val;
				return;
			}
		}
		list.emplace(key, val);
		size++;
		if (size >= table.size() * 0.75)
		{
			resize(table.size() * 2);
		}
	}
	//删
	void remove(K key)
	{
		auto& list = table[hash(key)];
		for (auto it = list.begin(); it != list.end(); ++it)
		{
			if (it->key == key)
			{
				list.erase(it);
				size--;
				if (size < table.size() / 8)
				{
					resize(table.size() / 4);
				}
				return;
			}
		}
	}
	//查
	V get(K key)const
	{
		int index = (std::hash<K>{}(key) & 0x7fffffff) % table.size();
		const auto& list = table[index];
		for (const auto& node : list)
		{
			if (node.key == key)
			{
				return node.value;
			}
		}
		return V();
	}
	//返回所有key
	std::list<K>keys()const
	{
		std::list<K>keys;
		for (const auto& list : table)
		{
			for (const auto& node : list)
			{
				keys.push_back(node.key);
			}
		}
		return keys;
	}
	int size_()const
	{
		return size;
	}
};