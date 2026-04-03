#include<iostream>
#include<vector>
using namespace std;
//输入数组nums，在start及以后索引在nums中找n个数，使其和为target（递归实现）
//ps：nums升序排列
vector<vector<int>>nsumtarget(vector<int>& nums, int n, int start, long long target)
{
    int sz = nums.size();
    vector<vector<int>>res;
    if (n < 2 || sz < n)return res;
    if (n == 2)//twosum（basecase）
    {
        int lo = start, hi = sz - 1;
        while (lo < hi)
        {
            int sum = nums[lo] + nums[hi];
            int left = nums[lo], right = nums[hi];
            if (sum < target)
            {
                while (lo < hi && nums[lo] == left)lo++;//去重
            }
            else if (sum > target)
            {
                while (lo < hi && nums[hi] == right)hi--;//去重
            }
            else
            {
                res.push_back({ left,right });
                while (lo < hi && nums[lo] == left)lo++;//去重
                while (lo < hi && nums[hi] == right)hi--;//去重
            }
        }
    }
    else
    {
        for (int i = start; i < sz; ++i)
        {
            vector<vector<int>>curr = nsumtarget(nums, n - 1, i + 1, target - nums[i]);
            for (vector<int>curr : curr)
            {
                curr.push_back(nums[i]);
                res.push_back(curr);
            }
            while (i < sz - 1 && nums[i] == nums[i + 1])i++;//去重
        }
    }
    return res;
}