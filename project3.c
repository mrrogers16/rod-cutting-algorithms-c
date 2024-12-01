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
    int n = atoi(argv[2]);
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
    int *rods = malloc(n * sizeof(int));
    if (rods == NULL)
    {
        fprintf(stderr, "Memory allocation failed for rods.\n");
        return 1;
    }

    for (int i = 0; i < n; i++)
    {
        rods[i] = atoi(argv[3 + i]);
        if (rods[i] <= 0)
        {
            printf("Rod lengths must be positive.\n");
            free(rods);
            return 1;
        }
    }

    switch (algorithm)
    {
    case 'R':
        printResultsRecursive(rods, n);
        break;
    case 'r':
        printRecursiveCallCount(rods, n);
        break;
    case 'M':
        printResultsMemoization(rods, n);
        break;
    case 'm':
        printMemoizationMatrix(rods, n);
        break;
    case 'D':
        printResultsDynamic(rods, n);
        break;
    case 'd':
        printDynamicTable(rods, n);
        break;
    default:
        printf("Invalid algorithm letter.\n");
        free(rods);
        return 1;
    }

    free(rods);
    return 0;
}