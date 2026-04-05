#include<vector>
#include<string>
using namespace std;
template<typename V>
class Triemap
{
private:
    static const int R = 26;

    int _size = 0;

    struct TrieNode
    {
        V* val;
        TrieNode* children[R]=nullptr;
        ~TrieNode() { delete val; }
    };
    TrieNode* root=nullptr;

    TrieNode* getNode(TrieNode* node, const string& key)
    {
        TrieNode* p = node;
        for (int i = 0; i < key.length(); ++i)
        {
            if (p == nullptr)
            {
                return nullptr;
            }
            char c = key[i];
            p = p->children[c-'a'];
        }
        return p;
    }
public:
    // 在 Map 中添加 key
    void put(string key, V val)
    {
        if (!containsKey(key))
        {
            _size++;
       }
        root = put2(root, key, val, 0);
    }
    // 定义：向以 node 为根的 Trie 树中插入 key[i..]，返回插入完成后的根节点
    TrieNode* put2(TrieNode* node, string key, V val, int i)
    {
        if (node == nullptr)
        {
            node = new TrieNode();
        }
        if (i == key.length())
        {
            if (node->val == nullptr) {
                node->val = new V(val);
            }
            else {
                *(node->val) = val;
            }
            return node;
        }
        char c = key[i];
        node->children[c-'a'] = put2(node->children[c-'a'], key, val, i + 1);
        return node;
    }
    // 删除键 key 以及对应的值
    void remove(string key)
    {
        if (!containsKey(key)) {
            return;
        }
        // 递归修改数据结构要接收函数的返回值
        root = remove2(root, key, 0);
        _size--;
    }
    // 定义：在以 node 为根的 Trie 树中删除 key[i..]，返回删除后的根节点
    TrieNode* remove2(TrieNode* node,const string&key, int i)
    {
        if (node == nullptr)
        {
            return nullptr;
        }
        if (i == key.length())
        {
            delete node->val;
            node->val = nullptr;
        }
        else
        {
            char c = key[i];
            
            node->children[c-'a'] = remove2(node->children[c-'a'], key, i + 1);
        }
        if (node->val != nullptr)
        {
            return node;
        }
        for (int c = 0; c < R; ++c)
        {
            if (node->children[(char)c] != nullptr)
            {
                return node;
            }
        }
        delete node;
        return nullptr;
    }
    // 搜索 key 对应的值，不存在则返回 null
    // get("the") -> 4
    // get("tha") -> null
    V* get(string key)
    {
        TrieNode* x = getNode(root, key);
        if (x == nullptr || x->val == nullptr)
        {
            return nullptr;
        }
        return x->val;
    }

    // 判断 key 是否存在在 Map 中
    // containsKey("tea") -> false
    // containsKey("team") -> true
    bool containsKey(string key)
    {
        return get(key) != nullptr;
    }

    // 在 Map 的所有键中搜索 query 的最短前缀
    // shortestPrefixOf("themxyz") -> "the"
    string shortestPrefixOf(const string& query)
    {
        TrieNode* p = root;
        for (int i = 0; i < query.length(); ++i)
        {
            if (p == nullptr)
            {
                return "";
            }
            if (p->val != nullptr)
            {
                return query.substr(0, i);
            }
            char c = query[i];
            p = p->children[c-'a'];
        }
        if (p != nullptr && p->val != nullptr)
        {
            return query;
        }
        return "";
    }

    // 在 Map 的所有键中搜索 query 的最长前缀
    // longestPrefixOf("themxyz") -> "them"
    string longestPrefixOf(string query)
    {
        TrieNode* p = root;
        int maxlen = 0;
        for (int i = 0; i < query.length(); ++i)
        {
            if (p == nullptr)
            {
                break;
            }
            if (p->val != nullptr)
            {
                maxlen = i;
            }
            char c = query[i];
            p = p->children[c-'a'];
        }
        if (p != nullptr && p->val != nullptr)
        {
            return query;
        }
        return query.substr(0, maxlen);
    }

    // 搜索所有前缀为 prefix 的键
    // keysWithPrefix("th") -> ["that", "the", "them"]
    vector<string> keysWithPrefix(string prefix)
    {
        vector<string>res;
        TrieNode* x = getNode(root, prefix);
        if (x == nullptr)
        {
            return res;
        }
        string path = prefix;
        traverse(x, path, res);
        return res;
    }
    void traverse(TrieNode* node, string&path, vector<string>&res)
    {
        if (node == nullptr)
        {
            return;
        }
        if (node->val != nullptr)
        {
            res.push_back(path);
        }
        for (int c = 0; c < R; ++c)
        {
            path.push_back(char(c+'a'));

            traverse(node->children[c], path, res);

            path.pop_back();
        }
    }

    // 判断是和否存在前缀为 prefix 的键
    // hasKeyWithPrefix("tha") -> true
    // hasKeyWithPrefix("apple") -> false
    bool hasKeyWithPrefix(string prefix)
    {
        return getNode(root, prefix) != nullptr;
    }

    // 通配符 . 匹配任意字符，搜索所有匹配的键
    // keysWithPattern("t.a.") -> ["team", "that"]
    vector<string> keysWithPattern(string pattern)
    {
        vector<string>res;
        string path;
        traversepattern(root, path, pattern, 0, res);
        return res;
    }
    void traversepattern(TrieNode* node, string path, const string& pattern, int i, vector<string>& res)
    {
        if (node == nullptr)
        {
            return;
        }
        if (i == pattern.length())
        {
            if (node->val != nullptr)
            {
                res.push_back(path);
            }
            return;
        }
        char c = pattern[i];
        if (c == '.')
        {
            for (int j = 0; j < R; ++j)
            {
                path.push_back(j+'a');
                traversepattern(node->children[j], path, pattern, i + 1, res);
                path.pop_back();
            }
        }
        else
        {
            path.push_back(c);
            traversepattern(node->children[c-'a'], path, pattern, i + 1, res);
            path.pop_back();
        }
    }
    // 通配符 . 匹配任意字符，判断是否存在匹配的键
    // hasKeyWithPattern(".ip") -> true
    // hasKeyWithPattern(".i") -> false
    bool hasKeyWithPattern(string pattern)
    {
        return !keysWithPattern(pattern).empty();
    }

    // 返回 Map 中键值对的数量
    int size()
    {
        return _size;
    }
};