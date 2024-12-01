#include <stdio.h>
#include <limits.h>
#include "algos.h"

// Calclate the sum of array elements from index 'start' to 'end'
int sumArray(int start, int end, int *prefixSum)
{
    return prefixSum[end + 1] - prefixSum[start];
}

// Finds the minimum galvanization cost using recursion
int minRecursive(int arr[], int start, int end, int n, int *prefixSum, int *recursiveCallCount)
{
    // Increment our call counter at the start of each recursion
    (*recursiveCallCount)++;

    // Base Case: Single rod or invalid range
    if (start >= end)
    {
        return 0;
    }
    // Initialize min_cost to huge number for always greater than first compared
    int min_cost = INT_MAX;

    // Try all partitions
    for (int k = start; k < end; k++)
    {
        int cost = sumArray(start, end, prefixSum) + minRecursive(arr, start, k, n, prefixSum, recursiveCallCount) + minRecursive(arr, k + 1, end, n, prefixSum, recursiveCallCount);
        // If better min_cost is found, update min_cost to cost
        if (cost < min_cost)
        {
            min_cost = cost;
        }
    }
    return min_cost;
}

// Recursive function using memoization to find min cost
int minMemoized(int start, int end, int n, int *prefixSum, int **memoMatrix)
{
    // Base Case: Single rod or invalid range
    if (start >= end)
    {
        memoMatrix[start][end] = 0; // Set base case value
        return 0;
    }
    // Check if value has already been computed
    if (memoMatrix[start][end] != -1)
    {
        return memoMatrix[start][end];
    }

    int min_cost = INT_MAX;                          // Init min_cost to huge value
    int total_sum = sumArray(start, end, prefixSum); // Total sum of rods from 'start' to 'end

    // Iterate through and try all partitions
    for (int k = start; k < end; k++)
    {
        int cost = total_sum + minMemoized(start, k, n, prefixSum, memoMatrix) + minMemoized(k + 1, end, n, prefixSum, memoMatrix);
        // Update min_cost if lower cost is found
        if (cost < min_cost)
        {
            min_cost = cost;
        }
    }
    memoMatrix[start][end] = min_cost; // Record the computed value in our memoization table
    return min_cost;
}

// Computes prefix sums for array 'arr[]' of size 'n'
void computePrefixSum(int arr[], int n, int *prefixSum)
{
    prefixSum[0] = 0; // Initalize first element to 0
    for (int i = 0; i < n; i++)
    {
        prefixSum[i + 1] = prefixSum[i] + arr[i]; // Build prefix sum array
    }
}

// Prints the memoization matrix after computation
void printMemoizationMatrix(int arr[], int n)
{
    // Allocate memory and check for errors
    int *prefixSum = malloc((n + 1) * sizeof(int));
    if (prefixSum == NULL)
    {
        fprintf(stderr, "Memory allocation fialed for prefixSum.\n");
        exit(1);
    }

    computePrefixSum(arr, n, prefixSum);

    // Initalize our memo matrix
    int **memoMatrix = malloc(n * sizeof(int *));
    if (memoMatrix == NULL)
    {
        fprintf(stderr, "Memory allocation failed for memoMatrix.\n");
        free(prefixSum);
        exit(1);
    }
    // Allocate and init each row of the memo matrix
    for (int i = 0; i < n; i++)
    {
        memoMatrix[i] = malloc(n * sizeof(int));
        if (memoMatrix[i] == NULL)
        {
            fprintf(stderr, "Memory allocation failed for memoMatrix[%d].\n", i);
            free(prefixSum);
            for (int j = 0; j < i; j++)
            {
                free(memoMatrix[j]);
            }
            free(memoMatrix);
            exit(1);
        }
        for (int j = 0; j < n; j++)
        {
            memoMatrix[i][j] = -1; // Init all cells to -1 for uncalculated/default
        }
    }

    minMemoized(0, n - 1, n, prefixSum, memoMatrix); // Compute teh memo matrix

    // Print the matrix
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d", memoMatrix[i][j]);
            if (j < n - 1)
            {
                printf(" "); // Add a space between elements
            }
        }
        printf("\n");
    }
    // Free memory
    for (int i = 0; i < n; i++)
    {
        free(memoMatrix[i]);
    }
    free(memoMatrix);
    free(prefixSum);
}

// Prints the minimum cost using the memoization solution
void printResultsMemoization(int arr[], int n)
{
    // Allocate memory for prefix sums and check for errors
    int *prefixSum = malloc((n + 1) * sizeof(int));
    if (prefixSum == NULL)
    {
        fprintf(stderr, "Memory allocation fialed for prefixSum.\n");
        exit(1);
    }
    // Compute prefix sums
    computePrefixSum(arr, n, prefixSum);

    // Initialize memo matrix
    int **memoMatrix = malloc(n * sizeof(int *));
    if (memoMatrix == NULL)
    {
        fprintf(stderr, "Memory allocation failed for memoMatrix.\n");
        free(prefixSum);
        exit(1);
    }
    // Allocate and initialize each row of the memoization matrix
    for (int i = 0; i < n; i++)
    {
        memoMatrix[i] = malloc(n * sizeof(int));
        if (memoMatrix == NULL)
        {
            fprintf(stderr, "Memory allocation failed for memoMatrix[%d].\n", i);
            free(prefixSum);
            for (int j = 0; j < i; j++)
            {
                free(memoMatrix[j]);
            }
            free(memoMatrix);
            exit(1);
        }
        // Iterate through and init all cells to -1 for uncalculated/default
        for (int j = 0; j < n; j++)
        {
            memoMatrix[i][j] = -1;
        }
    }

    int result = minMemoized(0, n - 1, n, prefixSum, memoMatrix);
    printf("%d\n", result); // print min cost

    // Free memory
    for (int i = 0; i < n; i++)
    {
        free(memoMatrix[i]);
    }
    free(memoMatrix);
    free(prefixSum);
}

// Print the minimum cost for the recursive solution
void printResultsRecursive(int arr[], int n)
{
    // Allocate memory and check for errors
    int *prefixSum = malloc((n + 1) * sizeof(int));
    if (prefixSum == NULL)
    {
        fprintf(stderr, "Memory allocation failed for prefixSum.\n");
        exit(1);
    }

    computePrefixSum(arr, n, prefixSum); // Call computePrefixSum

    int recursiveCallCount = 0;                                                  // Not needed for this
    int result = minRecursive(arr, 0, n - 1, n, prefixSum, &recursiveCallCount); // Print minimum cost
    printf("%d\n", result);
    // Free allocated memory
    free(prefixSum);
}

void printRecursiveCallCount(int arr[], int n)
{
    // Allocate memory and check for errors
    int *prefixSum = malloc((n + 1) * sizeof(int));
    if (prefixSum == NULL)
    {
        fprintf(stderr, "Memory allocation failed for prefixSum.\n");
        exit(1);
    }

    computePrefixSum(arr, n, prefixSum); // Call computePrefixSum

    int recursiveCallCount = 0;                                     // Init recursive call counter
    minRecursive(arr, 0, n - 1, n, prefixSum, &recursiveCallCount); // Call our function
    printf("%d\n", recursiveCallCount);                             // Print number of recursive calls
    free(prefixSum);                                                // Free allocated memory
}

// Dynamic solution to find the minimum cost
int minDynamic(int arr[], int n, int *prefixSum, int **dpMatrix)
{
    // Base case = dpMatrix[i][i] = 0
    // This is set during initialization

    // Fill dp matrix[i][j] for lengths from 2 to n
    for (int length = 2; length <= n; length++)
    {
        for (int i = 0; i <= n - length; i++)
        {
            int j = i + length - 1;
            dpMatrix[i][j] = INT_MAX;                  // Start with large value
            int total_sum = sumArray(i, j, prefixSum); // Total sum of rods from 'i' to 'j'
            // Try all possible partitions
            for (int k = i; k < j; k++)
            {
                int cost = dpMatrix[i][k] + dpMatrix[k + 1][j] + total_sum;
                if (cost < dpMatrix[i][j])
                {
                    dpMatrix[i][j] = cost; // record lowest cost
                }
            }
        }
    }
    return dpMatrix[0][n - 1]; // Return min cost for full range
}

// Prints the minimum cost using the dynamic solution
void printResultsDynamic(int arr[], int n)
{
    // Allocate memory and check for errors
    int *prefixSum = malloc((n + 1) * sizeof(int));
    if (prefixSum == NULL)
    {
        fprintf(stderr, "Memory allocation failed for prefixSum.\n");
        exit(1);
    }
    computePrefixSum(arr, n, prefixSum);

    // Init dpMatrix
    int **dpMatrix = malloc(n * sizeof(int *));
    if (dpMatrix == NULL)
    {
        fprintf(stderr, "Memory allocation failed for dpMatrix.\n");
        free(prefixSum);
        exit(1);
    }
    // Allocate and init each row of the dpMatrix
    for (int i = 0; i < n; i++)
    {
        dpMatrix[i] = malloc(n * sizeof(int));
        if (dpMatrix[i] == NULL)
        {
            fprintf(stderr, "Memory allocation failed for dpMatrix[%d].\n", i);
            free(prefixSum);
            for (int j = 0; j < i; j++)
            {
                free(dpMatrix[j]);
            }
            free(dpMatrix);
            exit(1);
        }
        for (int j = 0; j < n; j++)
        {
            if (i == j)
            {
                dpMatrix[i][j] = 0; // Base case: single rod cost = 0
            }
            else
            {
                dpMatrix[i][j] = -1; // Init other cells to -1
            }
        }
    }
    int result = minDynamic(arr, n, prefixSum, dpMatrix);
    printf("%d\n", result); // Print min cost

    // Free memory
    for (int i = 0; i < n; i++)
    {
        free(dpMatrix[i]);
    }
    free(dpMatrix);
    free(prefixSum);
}
// Print the dynamic table table after its computed
void printDynamicTable(int arr[], int n)
{
    // Allocate memory and check for errors
    int *prefixSum = malloc((n + 1) * sizeof(int));
    if (prefixSum == NULL)
    {
        fprintf(stderr, "Memory allocation failed for prefixSum.\n");
        exit(1);
    }
    computePrefixSum(arr, n, prefixSum);

    // Initialize dpMatrix
    int **dpMatrix = malloc(n * sizeof(int *));
    if (dpMatrix == NULL)
    {
        fprintf(stderr, "Memory allocation failed for dpMatrix.\n");
        free(prefixSum);
        exit(1);
    }
    // Allocate and init each row of the dpMatrix
    for (int i = 0; i < n; i++)
    {
        dpMatrix[i] = malloc(n * sizeof(int));
        if (dpMatrix[i] == NULL)
        {
            fprintf(stderr, "Memory allocation failed for dpMatrix[%d].\n", i);
            free(prefixSum);
            for (int j = 0; j < i; j++)
            {
                free(dpMatrix[j]);
            }
            free(dpMatrix);
            exit(1);
        }
        for (int j = 0; j < n; j++)
        {
            if (i == j)
                dpMatrix[i][j] = 0;
            else if (i > j)
                dpMatrix[i][j] = -1;
            else
                dpMatrix[i][j] = -1;
        }
    }
    minDynamic(arr, n, prefixSum, dpMatrix); // Call function to compute dpMatrix

    // Print the dp table
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d", dpMatrix[i][j]);
            if (j < n - 1)
                printf(" "); // Add space between elements
        }
        printf("\n");
    }

    for (int i = 0; i < n; i++)
    {
        free(dpMatrix[i]);
    }
    free(dpMatrix);
    free(prefixSum);
}