#include<iostream>
#include<cassert>
#include<vector>
using namespace std;
//0-1背包：
//递归解法
vector<vector<int>>memo;
int knapsack01(int W, vector<int>& weights, vector<int>& values)
{
	memo = vector<vector<int>>(weights.size(), vector<int>(W+1, -666));
	return dp(W, weights, values, 0);
}
int dp(int w, vector<int>& weights, vector<int>& values,int i)
{
	if (i >= weights.size())
	{
		return 0;
	}
	if (w == 0)
	{
		return 0;
	}
	if (memo[i][w] != -666)
	{
		return memo[i][w];
	}
	if (w - weights[i] < 0)
	{
		memo[i][w]=dp(w, weights, values,i+1);
	}
	else
	{
		memo[i][w]=max(dp(w, weights, values, i + 1), dp(w - weights[i], weights, values, i + 1));
	}
	return memo[i][w];
}
//迭代解法
int knapsack02(int W, vector<int>& weights, vector<int>& values)
{
	//二维数组
	int m = weights.size();
	vector<vector<int>>dp(m+1, vector<int>(W+1));
	for (int i = 0; i < m; ++i)
	{
		dp[i][0] = 0;
	}
	for (int j = 0; j < W; ++j)
	{
		dp[0][j] = 0;
	}
	for (int i = 1; i <=m; ++i)
	{
		for (int j = 1; j <= W; ++j)
		{
			if (j < weights[i-1])
			{
				dp[i][j] = dp[i - 1][j];
			}
			else
			{
				dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - weights[i-1]] + values[i-1]);
			}
		}
	}
	return dp[m][W];
}
int knapsack03(int W, vector<int>& weights, vector<int>& values)
{
	//空间压缩
	vector<int>dp(W + 1);
	dp[0] = 0;
	for (int i = 0; i < weights.size(); ++i)
	{
		//容量反向遍历来避免选重复物品
		for (int j = W; j >= weights[i]; --j)
		{
			
			dp[j] = max(dp[j], dp[j - weights[i]] + values[i]);
		}
	}
	return dp[W];
}
//完全背包:
//递归解法
vector<vector<int>>memo_;
int napsack01(int W, vector<int>& weights, vector<int>& values)
{
	memo_ = vector<vector<int>>(weights.size(), vector<int>(W + 1, -2333));
	return dp_(W, weights, values, 0);
}
int dp_(int w, vector<int>& weights, vector<int>& values, int i)
{
	if (i == weights.size())
	{
		return 0;
	}
	if (w == 0)
	{
		return 0;
	}
	if (memo_[i][w] != -233)
	{
		return memo_[i][w];
	}
	if (w - weights[i]<0)
	{
		memo_[i][w] = dp_(w, weights, values, i + 1);
	}
	else
	{
		memo_[i][w] = max(dp_(w - weights[i], weights, values, i)+values[i], dp_(w, weights, values, i + 1));
	}
	return memo_[i][w];
}
//迭代解法
int napsack02(int W, vector<int>& weights, vector<int>& values)
{
	int m = weights.size();
	vector<vector<int>>dp(m + 1, vector<int>(W + 1));
	for (int i = 0; i < m; ++i)
	{
		dp[i][0] = 0;
	}
	for (int j = 0; j < W; ++j)
	{
		dp[0][j] = 0;
	}
	for (int i = 1; i <= m; ++i)
	{
		for (int j = 1; j <= W; ++j)
		{
			if (j > weights[i-1])
			{
				dp[i][j] = max(dp[i-1][j], dp[i][j - weights[i]] + values[i]);
			}
			else
			{
				dp[i][j] = dp[i - 1][j];
			}
		}
	}
	return dp[m][W];
}
//空间压缩
int napsack03(int W, vector<int>& weights, vector<int>& values)
{
	vector<int>dp(W + 1);
	dp[0] = 0;
	for (int i = 0; i < weights.size(); ++i)
	{
		for (int j = weights[i]; j <= W; ++j)
		{
			dp[j] = max(dp[j], dp[j - weights[i]] + values[i]);
		}
	}
	return dp[W];
}