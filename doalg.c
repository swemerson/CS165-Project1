#include <limits.h>

int doalg(int n, int k, int *Best)
{
    if (n < 10 || n > 10000 || k < 1 || k > 100)
		return 0;

    int i, j, l, val;
    
    // Insert first k element indices into Best in decreasing order
    Best[0] = 1;

    // i is the index of the private array (1-based)
    for (i = 2; i <= k; ++i)
    {
        // Start at end of existing elements in Best and find where to insert next element
        for (j = i - 1; j > 0; --j)
        {
            if ((val = COMPARE(i, Best[j - 1])) == -1) return 0;
            if (val == 2) break;			
        }

		// Shift elements over to insert next element
        for (l = i - 1; l > j; --l)
            Best[l] = Best[l - 1];
        Best[j] = i;
    }

    // Check indices after k, insert in descending order, same logic 
    for (i = k + 1; i <= n; ++i)
    {
        for (j = k; j > 0; --j)
        {
            if ((val = COMPARE(i, Best[j - 1])) == -1) return 0;
            if (val == 2) break;			
        }

        for (l = k; l > j; --l)
            Best[l] = Best[l - 1];
        Best[j] = i;
    }  
    
    return 1;
}
