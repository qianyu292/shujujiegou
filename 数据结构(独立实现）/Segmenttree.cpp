#include <functional>
#include <iostream>
#include <stdexcept>
#include <vector>
#include<string>
//链式segmentTree
// 线段树节点
class SegmentNode
{
public:
	int l, r;
	int mergeVal;
	SegmentNode* left;
	SegmentNode* right;
	SegmentNode(int mergeVal, int l, int r)
		: mergeVal(mergeVal), l(l), r(r), left(nullptr), right(nullptr) {
	}
};
class SegmentTree
{
private:
	SegmentNode* root;
	std::function<int(int, int)> merger;
	SegmentNode* build(const std::vector<int>& nums, int l, int r)
	{
		if (l == r)
		{
			return new SegmentNode(nums[l], l, r);
		}
		int mid = l + (r - l) / 2;
		SegmentNode* left = build(nums, l, mid);
		SegmentNode* right = build(nums, mid + 1, r);
		SegmentNode* node = new SegmentNode(merger(left->mergeVal, right->mergeVal), l, r);
		node->left = left;
		node->right = right;
		return node;
	}
	void update(SegmentNode* node, int index, int value)
	{
		if (node->l == node->r)
		{
			node->mergeVal = value;
			return;
		}
		int mid = node->l + (node->r - node->l) / 2;
		if (index <= mid)
		{
			update(node->left, index, value);
		}
		else
		{
			update(node->right, index, value);
		}
		node->mergeVal = merger(node->left->mergeVal, node->right->mergeVal);
	}
	int query(SegmentNode* node, int qL, int qR)
	{
		if (qL > qR) {
			throw std::invalid_argument("Invalid query range");
		}
		if (node->l == qL && node->r == qR)
		{
			return node->mergeVal;
		}
		int mid = node->l + (node->r - node->l) / 2;
		if (qR <= mid)
		{
			return query(node->left, qL, qR);
		}
		else if (qL > mid)
		{
			return query(node->right, qL, qR);
		}
		else
		{
			return merger(query(node->left, qL, mid),
				query(node->right, mid + 1, qR));
		}
	}
public:
	SegmentTree(const std::vector<int>& nums, std::function<int(int, int)> merger)
		: merger(merger) {
		root = build(nums, 0, nums.size() - 1);
	}

	void update(int index, int value) {
		update(root, index, value);
	}

	int query(int qL, int qR) {
		return query(root, qL, qR);
	}
};