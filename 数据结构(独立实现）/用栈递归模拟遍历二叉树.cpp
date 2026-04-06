#include<vector>
#include<stack>
using namespace std;
struct Node
{
	Node* left;
	Node* right;
	int val;
	Node(int val) :val(val), left(nullptr), right(nullptr) {};
};
class Solution
{
private:
	stack<Node*>stk;
public:
	//×ó²àÊ÷Ö¦µ½µ×
	void pushlefttree(Node* p)
	{
		//Ç°Ðò±éÀúÎ»ÖÃ
		while (p != nullptr)
		{
			stk.push(p);
			p = p->left;
		}
	}
	vector<int>traverse(Node* root)
	{
		Node* visited = new Node(-1);

		pushlefttree(root);

		while (!stk.empty())
		{
			Node* p = stk.top();
			stk.pop();
			if ((p->left==nullptr||p->left==visited)&&p->right!=nullptr)
			{
				//ÖÐÐò±éÀúÎ»ÖÃ
				stk.push(p->right);
			}
			if (p->right == nullptr || p->right == visited)
			{
				visited = p;
				stk.pop();
			}
		}
    }
};