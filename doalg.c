int doalg(int n, int k, int *Best)
{
	// Out of bounds argument check
    if (n < 10 || n > 10000 || k < 1 || k > 100)
		return 0;
    int i, j, l, lo, hi, val;
	int temp[10000];
	int pos;
	
	if (n / 2 >= k)
	{
		for (i = 1; i < n; i += 2)
		{
			pos = 0;
			if (n % 2 != 0)
				temp[pos++] = i++;									
			if ((val = COMPARE(i, i + 1)) == -1)
				return 0;
			if (val == 1)
				temp[pos++] = i;
			else
				temp[pos++] = i + 1;
		}

		if (n % 2 != 0) 
			n = n / 2 + 1;
		else
			n /= 2;
	}

	while (n / 2 >= k)
	{
		for (i = 0; i < n - 1; i += 2)
		{
			pos = 0;
			if (n % 2 != 0)
				temp[pos++] = temp[i++];									
			if ((val = COMPARE(temp[i], temp[i + 1])) == -1)
				return 0;
			if (val == 1)
				temp[pos++] = temp[i];
			else
				temp[pos++] = temp[i + 1];
		}

		if (n % 2 != 0) 
			n = n / 2 + 1;
		else
			n /= 2;
	}


    // Insert first k element indices into Best in decreasing order
    
	// Insert 1st
	Best[0] = temp[0];	
	
	// Insert 2nd
	if ((val = COMPARE(temp[1], Best[0])) == -1) 
		return 0;
	if (val == 2)
		Best[1] = temp[1];
	else
	{
		Best[1] = temp[0];
		Best[0] = temp[1];
	}

	// Insert 3rd
	if ((val = COMPARE(temp[2], Best[0])) == -1) 
		return 0;
	if (val == 1)
	{
		Best[2] = Best[1];
		Best[1] = Best[0];
		Best[0] = temp[2];
	}
	else
	{
		if ((val = COMPARE(temp[2], Best[1])) == -1)
			return 0;
		if (val == 1)
		{
			Best[2] = Best[1];
			Best[1] = temp[2];
		}
		else
			Best[2] = temp[2];
	}

    // i is the index of the private array (1-based)
    for (i = 3; i < k; ++i)
    {
		// Using binary search to find where to insert next element (in descending order)
		lo = 0;
		hi = temp[i] - 2;
		while (lo < hi - 1)
		{
			int mid = lo + (hi - lo) / 2;
            if ((val = COMPARE(temp[i], Best[mid])) == -1) 
				return 0;
            if (val == 2)
				lo = mid;
			else
				hi = mid;
		}

		// Case where element is largest
		if (lo == 0)
		{
            if ((val = COMPARE(temp[i], Best[lo])) == -1) 
				return 0;
            if (val == 1)
				hi = 0;
		}

		// Case where element is smallest 
		else if (hi == temp[i] - 2)
		{
            if ((val = COMPARE(temp[i], Best[hi])) == -1) 
				return 0;
            if (val == 2)
				++hi;
		}

		// Shift elements over to insert next element
		for (l = temp[i] - 1; l > hi; --l)
			Best[l] = Best[l - 1];
		Best[hi] = temp[i];
    }

    // Check indices after k, insert in descending order, same logic 
    for (i = k; i < n; ++i)
    {
        // Check if element too small for Best
		if ((val = COMPARE(temp[i], Best[k - 1])) == -1) 
			return 0;
		if (val == 2)
			continue;
	
		lo = 0;
		hi = k - 1;
		while (lo < hi - 1)
		{
			int mid = lo + (hi - lo) / 2;
            if ((val = COMPARE(temp[i], Best[mid])) == -1) 
				return 0;
            if (val == 2)
				lo = mid;
			else
				hi = mid;
		}

		// Case where element is largest
		if (lo == 0)
		{
            if ((val = COMPARE(temp[i], Best[lo])) == -1) 
				return 0;
            if (val == 1)
				hi = 0;
		}

		// Shift elements over to insert next element
		for (l = k; l > hi; --l)
			Best[l] = Best[l - 1];
		Best[hi] = temp[i];
    }  
    
    return 1;
}
