#include <stdlib.h>

void insert_first_three(int n, int k, int *Best)
{
    int val;
    // Insert 1st
	Best[0] = 1;

	// Insert 2nd
	if ((val = COMPARE(2, Best[0])) == -1)
		return 0;
	if (val == 2)
		Best[1] = 2;
	else
	{
		Best[1] = 1;
		Best[0] = 2;
	}

	// Insert 3rd
	if ((val = COMPARE(3, Best[0])) == -1)
		return 0;
	if (val == 1)
	{
		Best[2] = Best[1];
		Best[1] = Best[0];
		Best[0] = 3;
	}
	else
	{
		if ((val = COMPARE(3, Best[1])) == -1)
			return 0;
		if (val == 1)
		{
			Best[2] = Best[1];
			Best[1] = 3;
		}
		else
			Best[2] = 3;
	}
}

void insert_until_k(int n, int k, int *Best)
{
    int i, l, lo, hi, val;
    for (i = 4; i <= k; ++i)
    {
		// Using binary search to find where to insert next element (in descending order)
		lo = 0;
		hi = i - 2;
		while (lo < hi - 1)
		{
			int mid = lo + (hi - lo) / 2;
            if ((val = COMPARE(i, Best[mid])) == -1)
				return 0;
            if (val == 2)
				lo = mid;
			else
				hi = mid;
		}

		// Case where element is largest
		if (lo == 0)
		{
            if ((val = COMPARE(i, Best[lo])) == -1)
				return 0;
            if (val == 1)
				hi = 0;
		}

		// Case where element is smallest
		else if (hi == i - 2)
		{
            if ((val = COMPARE(i, Best[hi])) == -1)
				return 0;
            if (val == 2)
				++hi;
		}

		// Shift elements over to insert next element
		for (l = i - 1; l > hi; --l)
			Best[l] = Best[l - 1];
		Best[hi] = i;
    }
}

void insert_rest(int n, int k, int *Best)
{
    int i, l, lo, hi, val;
    for (i = k + 1; i <= n; ++i)
    {
        // Check if element too small for Best
		if ((val = COMPARE(i, Best[k - 1])) == -1)
			return 0;
		if (val == 2)
			continue;

		lo = 0;
		hi = k - 1;
		while (lo < hi - 1)
		{
			int mid = lo + (hi - lo) / 2;
            if ((val = COMPARE(i, Best[mid])) == -1)
				return 0;
            if (val == 2)
				lo = mid;
			else
				hi = mid;
		}

		// Case where element is largest
		if (lo == 0)
		{
            if ((val = COMPARE(i, Best[lo])) == -1)
				return 0;
            if (val == 1)
				hi = 0;
		}

		// Shift elements over to insert next element
		for (l = k; l > hi; --l)
			Best[l] = Best[l - 1];
		Best[hi] = i;
    }
}

int doalg(int n, int k, int *Best)
{
	// Out of bounds argument check
    if (n < 10 || n > 10000 || k < 1 || k > 100)
		return 0;

    // Insert first k element indices into Best in decreasing order

	insert_first_three(n, k, Best);

    // i is the index of the private array (1-based)

    insert_until_k(n, k, Best);

    // Check indices after k, insert in descending order, same logic

    insert_rest(n, k, Best);

    return 1;
}
