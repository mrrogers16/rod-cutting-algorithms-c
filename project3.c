#include <stdio.h>
#include <limits.h>
#include "algos.h"


int main(int argc, char *argv[])
{

    if (argc < 4)
    {
        printf("Usage: %s 'Algorithm Letter' 'number of rods' '[rod lengths]'\n", argv[0]);
        return 1;
    }

    // parse algo letter
    char algorithm = argv[1][0];
    // parse rods
    n = atoi(argv[2]);
    if (n <= 0)
    {
        printf("Number of rods must be positive.\n");
        return 1;
    }

    if (argc != n + 3)
    {
        printf("Incorrect number of rod lengths.\n");
        return 1;
    }

    // parse rod lengths
    int rods[n];
    for (int i = 0; i < n; i++)
    {
        rods[i] = atoi(argv[3 + i]);
        if (rods[i] <= 0)
        {
            printf("Rod lengths must be positive.\n");
            return 1;
        }
    }

    computePrefixSum(rods);

    switch (algorithm)
    {
    case 'R':
        printResultsRecursive(rods, n);
        break;
    case 'r':
        printRecursiveCallCount(rods, n);
        break;
    case 'M':
        printResultsMemoization();
        break;
    case 'm':
        printMemoizationMatrix();
        break;
    // D d
    default:
        printf("Invalid algorithm letter.\n");
        return 1;
    }
    return 0;
}