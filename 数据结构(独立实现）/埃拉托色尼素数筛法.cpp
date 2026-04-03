#include<iostream>
#include<vector>
using namespace std;
vector<bool>sieveOfEratosthenes(int n)
{
	vector<bool>isprime(n + 1, true);
	
	if (n >= 0)
	{
		isprime[0] = false;
	}
	if (n >= 1)
	{
		isprime[1] = false;
	}
	for (int i = 2; i * i <= n; ++i)
	{
		if (isprime[i])
		{
			for (int j = i * i; j <= n; j += i)
			{
				isprime[j] = false;
			}
		}
	}
	return isprime;
}