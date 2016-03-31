#include <limits.h>
#include "COMPARE.c"

void sort_array(int *best, int size)
{
	int i;
	for(i = size-2; i >= 0; i--)
	{
		int x = number[best[i]];
		int j = i + 1;
		while(j <= size && number[best[j]] > x)
		{
			number[best[j-1]] = number[best[j]];
			j++;
		}
		number[best[j+1]] = x;
	}
}

int *doalg(int n, int k, int *best)
{
	int i, j;
	int low = 0;
	int high = k-1;
	for(i = 0; i < k; i++)
	{
		best[i] = i;
	}
	sort_array(best, k);
	for(i = k; i < n; i++)
	{
		if(number[i] > number[best[k-1]])
		{
			while(low <= high)
			{
				int mid = low + (high-low)/2;
				if(number[best[mid]] > number[i] && number[i] > number[best[mid+1]])
				{
					int counter = mid+1;
					while(counter < k-1)
					{
						best[counter+1] = best[counter];
						counter++;
					}
					best[mid+1] = i;
				}
			}
		}
	}
	return best;
}
