#include<vector>
using namespace std;
int partition(vector<int>& nums, int lo, int hi);
void merge(vector<int>& nums, int lo, int mid, int hi);
void quicksort(vector<int>& res, int lo, int hi)
{
	if (lo >= hi)
	{
		return;
	}
	int p = partition(res, lo, hi);

	quicksort(res, lo, p - 1);

	quicksort(res, p + 1, hi);
}
int partition(vector<int>& nums, int lo, int hi)
{
	int pivot = nums[lo];
	int left = lo+1, right = hi;
	while (left < right)
	{
		while(nums[left] < pivot&&left<=hi)
		{
			left++;
		}
		while(nums[right] > pivot&&right>lo)
		{
			right--;
		}
		if (left >= right)
			break;
		swap(nums[left], nums[right]);
	}
	swap(nums[lo], nums[right]);
	return right;
}
vector<int>temp;
void mergesort(vector<int>& nums, int lo, int hi)
{
	if (lo>= hi)
	{
		return;
	}
	int mid = lo + (hi - lo) / 2;
	mergesort(nums, lo, mid);
	mergesort(nums, mid + 1, hi);
	merge(nums, lo, mid, hi);
}
void merge(vector<int>& nums, int lo, int mid, int hi)
{
	if (temp.size() < nums.size())
	{
		temp.resize(nums.size());
	}
	for (int i = 0; i < nums.size(); ++i)
	{
		temp[i] = nums[i];
	}
	int i = lo, j = mid+1;
	for (int p = lo; p <= hi; p++)
	{
		if (i == mid + 1)
		{
			nums[p] = temp[j++];
		}
		else if (j > hi)
		{
			nums[p] = temp[i++];
		}
		else if (temp[i] < temp[j])
		{
			nums[p] = temp[i++];
		}
		else
		{
			nums[p] = temp[j++];
		}
	}
}