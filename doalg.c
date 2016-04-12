int doalg_k1(int n, int *Best)
{
	int i, val;

    Best[0] = 1;
    for (i = 2; i <= n; ++i)
    {
        if ((val = COMPARE(i, Best[0])) == -1) return 0;
        if (val == 1)
            Best[0] = i;
    }
    
    return 1;
}

int doalg_k2(int n, int *Best)
{
	int i, val;

    Best[0] = 1;
    if ((val = COMPARE(2, Best[0])) == -1) return 0;
    if (val == 1)
    {
        Best[1] = Best[0];
        Best[0] = 2;
    }
    else
        Best[1] = 2;
    
    for (i = 3; i <= n; ++i)
    {
        if ((val = COMPARE(i, Best[1])) == -1) return 0;
        if (val == 2)
            continue;
        else
        {
            if ((val = COMPARE(i, Best[0])) == -1) return 0;
            if (val == 2)
                Best[1] = i;
            else
            {
                Best[1] = Best[0];
                Best[0] = i;
            }
        }		
    }
    
    return 1;
}

int insert_first_three(int *Best)
{
    int val;
    // Insert 1st
	Best[0] = 1;

	// Insert 2nd
	if ((val = COMPARE(2, Best[0])) == -1) return 0;
	if (val == 2)
		Best[1] = 2;
	else
	{
		Best[1] = 1;
		Best[0] = 2;
	}

	// Insert 3rd
	if ((val = COMPARE(3, Best[0])) == -1) return 0;
	if (val == 1)
	{
		Best[2] = Best[1];
		Best[1] = Best[0];
		Best[0] = 3;
	}
	else
	{
		if ((val = COMPARE(3, Best[1])) == -1) return 0;
		if (val == 1)
		{
			Best[2] = Best[1];
			Best[1] = 3;
		}
		else
			Best[2] = 3;
	}
    
    return 1;
}

int insert_until_k(int k, int *Best)
{
    int i, j, lo, hi, val;
    for (i = 4; i <= k; ++i)
    {
		// Using binary search to find where to insert next element (in descending order)
		lo = 0;
		hi = i - 2;
		while (lo < hi - 1)
		{
			int mid = lo + (hi - lo) / 2;
            if ((val = COMPARE(i, Best[mid])) == -1) return 0;
            if (val == 2)
				lo = mid;
			else
				hi = mid;
		}

		// Case where element is largest
		if (lo == 0)
		{
            if ((val = COMPARE(i, Best[lo])) == -1) return 0;
            if (val == 1)
				hi = 0;
		}

		// Case where element is smallest
		else if (hi == i - 2)
		{
            if ((val = COMPARE(i, Best[hi])) == -1) return 0;
            if (val == 2)
				++hi;
		}

		// Shift elements over to insert next element
		for (j = i - 1; j > hi; --j)
			Best[j] = Best[j - 1];
		Best[hi] = i;
    }
}

int insert_rest(int n, int k, int *Best)
{
    int i, j, lo, hi, val;
    for (i = k + 1; i <= n; ++i)
    {
        // Check if element too small for Best
		if ((val = COMPARE(i, Best[k - 1])) == -1) return 0;
		if (val == 2)
			continue;

        // Using binary search to find where to insert next element (in descending order)
		lo = 0;
		hi = k - 1;
		while (lo < hi - 1)
		{
			int mid = lo + (hi - lo) / 2;
            if ((val = COMPARE(i, Best[mid])) == -1) return 0;
            if (val == 2)
				lo = mid;
			else
				hi = mid;
		}

		// Case where element is largest
		if (lo == 0)
		{
            if ((val = COMPARE(i, Best[lo])) == -1) return 0;
            if (val == 1)
				hi = 0;
		}

		// Shift elements over to insert next element
		for (j = k; j > hi; --j)
			Best[j] = Best[j - 1];
		Best[hi] = i;
    }
}

int doalg(int n, int k, int *Best)
{
	// Out of bounds argument check
    if (n < 10 || n > 10000 || k < 1 || k > 100) return 0;
    
    // Handle k==1, k==2 cases
    if (k == 1) return doalg_k1(n, Best);
    if (k == 2) return doalg_k2(n, Best);

    // Insert in decreasing order
	if (insert_first_three(Best) == 0) return 0;
    if (insert_until_k(k, Best) == 0) return 0;
    if (insert_rest(n, k, Best) == 0) return 0;

    return 1;
}
