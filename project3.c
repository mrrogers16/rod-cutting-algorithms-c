#include <stdio.h>
#include <limits.h>
#include "algos.h"

int main(int argc, char *argv[])
{
    // Check for number of arguments (4)
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
    // Check if the correct number of rod lengths is provided by user
    if (argc != n + 3)
    {
        printf("Incorrect number of rod lengths.\n");
        return 1;
    }

    // Allocate memory for rods array
    int *rods = malloc(n * sizeof(int));
    if (rods == NULL)
    {
        fprintf(stderr, "Memory allocation failed for rods.\n");
        return 1;
    }
    // Parse rod lengths and validate positive
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
    // Switch to call the appropriate function in regards to the user provided algorithm letter
    // 'R': prints single line containing a single number for RECURSIVE SOLUTION
    // 'r': Prints single line containing a single number which is the number of times teh recursive function was called while solving 
    // 'M': Prints single line containing a single number for the memo-ing algorithm
    // 'm': Prints n lines showing teh values in the memoing matrix at the end of teh computation. A -1 is printed for uncalculated cells
    // 'D': Prints single line containing single number for dynamic algorithm
    // 'd': Prints n lines showing the values in the dynamic table at teh end of computation. A -1 is printed for uncalculated cells
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