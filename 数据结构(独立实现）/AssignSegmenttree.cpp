#include <iostream>
#include <stdexcept>

using namespace std;

class SegmentNode {
public:
    int l, r;
    int sum;
    SegmentNode* left;
    SegmentNode* right;

    // 表示当前节点是否存在赋值懒标记
    bool hasLazyAssign; // [!code highlight]
    // 懒更新中赋值的值
    int lazyAssign; // [!code highlight]

    SegmentNode(int l, int r, int value)
        : l(l), r(r), sum(value), left(nullptr), right(nullptr), hasLazyAssign(false) {
    }

    ~SegmentNode() {
        delete left;
        delete right;
    }
};
class AssignSegmentTree
{
private:
    SegmentNode* root;
    int defaultvalue;
    void initChildrenIfNeeded(SegmentNode* node)
    {
        if (node->l == node->r)
        {
            return;
        }
        if (node->left == nullptr || node->right == nullptr)
        {
            int mid = node->l + (node->r - node->l) / 2;
            if (node->left == nullptr) {
                node->left = new SegmentNode(node->l, mid, defaultvalue);
            }
            if (node->right == nullptr) {
                node->right = new SegmentNode(mid + 1, node->r, defaultvalue);
            }
        }
    }
    void pushDown(SegmentNode* node)
    {
        if (!node->hasLazyAssign)
        {
            return;
        }
        if (node->left)
        {
            node->left->lazyAssign = node->lazyAssign;
            node->left->hasLazyAssign = true;
            node->left->sum = (node->left->r - node->left->l + 1) * node->lazyAssign;
        }
        if (node->right)
        {
            node->right->lazyAssign = node->lazyAssign;
            node->right->hasLazyAssign = true;
            node->right->sum = (node->right->r - node->right->l + 1) * node->lazyAssign;
        }
        node->hasLazyAssign = false;
        node->lazyAssign = 0;
    }
    void _rangeUpdate(SegmentNode* node, int qL, int qR, int val)
    {
        if (node->r < qL || node->l > qR)
        {
            throw invalid_argument("Invalid update range");
        }
        if (qL <= node->l && node->r <= qR)
        {
            node->sum = (node->r - node->l + 1) * val;
            node->lazyAssign = val;
            node->hasLazyAssign = true;
            return;
        }
        initChildrenIfNeeded(node);

        // 部分覆盖，需要先下传懒标记，再递归更新左右子节点
        pushDown(node); // [!code highlight]

        int mid = node->l + (node->r - node->l) / 2;
        if (qR <= mid)
        {
            _rangeUpdate(node->left, qL, qR, val);
        }
        else if (qL > mid)
        {
            _rangeUpdate(node->right, qL, qR, val);
        }
        else
        {
            _rangeUpdate(node->left, qL, mid, val);
            _rangeUpdate(node->right, mid + 1, qR, val);
        }
        node->sum = node->left->sum + node->right->sum;
    }
    int _query(SegmentNode* node, int qL, int qR)
    {
        if (node->r < qL || node->l > qR)
        {
            throw invalid_argument("Invalid query range");
        }
        if (qL <= node->l && qR >= node->r)
        {
            return node->sum;
        }
        initChildrenIfNeeded(node);
        // 下传懒标记以确保左右子节点的数据正确
        pushDown(node); // [!code highlight]

        int mid = node->l + (node->r - node->l) / 2;
        if (qR <= mid)
        {
            return _query(node->left, qL, qR);
        }
        else if (qL > mid)
        {
            return _query(node->right, qL, qR);
        }
        else
        {
            return _query(node->left, qL, mid) + _query(node->right, mid + 1, qR);
        }
    }
public:
    // 构造方法
    // start, end 表示线段树的区间范围，defaultValue 表示每个区间初始的默认值
    AssignSegmentTree(int start, int end, int defaultvalue)
        : defaultvalue(defaultvalue) {
        int initSum = (end - start + 1) * defaultvalue;
        root = new SegmentNode(start, end, initSum);
    }

    ~AssignSegmentTree() {
        delete root;
    }

    // 单点赋值 val，时间复杂度 O(logN)
    void assign(int index, int val) {
        // 直接复用区间赋值方法
        rangeUpdate(index, index, val);
    }

    // 将闭区间 [qL, qR] 赋值为 val，时间复杂度 O(logN)
    void rangeUpdate(int qL, int qR, int val) {
        _rangeUpdate(root, qL, qR, val);
    }

    // 查询闭区间 [qL, qR] 的元素和，时间复杂度 O(logN)
    int query(int qL, int qR) {
        return _query(root, qL, qR);
    }
};