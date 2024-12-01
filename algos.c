#include <stdio.h>
#include <limits.h>
#include "algos.h"

// Calclate the sum of array elements from index 'start' to 'end'
int sumArray(int start, int end, int *prefixSum)
{
    return prefixSum[end + 1] - prefixSum[start];
}

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

int minMemoized(int start, int end, int n, int *prefixSum, int **memoMatrix)
{
    if (start >= end)
    {
        memoMatrix[start][end] = 0; // Set base case value
        return 0;
    }

    if (memoMatrix[start][end] != -1)
    {
        return memoMatrix[start][end];
    }

    int min_cost = INT_MAX;
    int total_sum = sumArray(start, end, prefixSum);

    for (int k = start; k < end; k++)
    {
        int cost = total_sum + minMemoized(start, k, n, prefixSum, memoMatrix) + minMemoized(k + 1, end, n, prefixSum, memoMatrix);
        if (cost < min_cost)
        {
            min_cost = cost;
        }
    }
    memoMatrix[start][end] = min_cost;
    return min_cost;
}

void computePrefixSum(int arr[], int n, int *prefixSum)
{
    // prefixSum = malloc((n + 1) * sizeof(int));
    prefixSum[0] = 0;
    for (int i = 0; i < n; i++)
    {
        prefixSum[i + 1] = prefixSum[i] + arr[i];
    }
}

void printMemoizationMatrix(int arr[], int n)
{
    int *prefixSum = malloc((n + 1) * sizeof(int));

    if (prefixSum == NULL)
    {
        fprintf(stderr, "Memory allocation fialed for prefixSum.\n");
        exit(1);
    }

    computePrefixSum(arr, n, prefixSum);

    // Initalize our memo matrix and fill with -1's
    int **memoMatrix = malloc(n * sizeof(int *));
    if (memoMatrix == NULL)
    {
        fprintf(stderr, "Memory allocation failed for memoMatrix.\n");
        free(prefixSum);
        exit(1);
    }

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
            memoMatrix[i][j] = -1;
        }
    }

    minMemoized(0, n - 1, n, prefixSum, memoMatrix);

    // Print the matrix
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d", memoMatrix[i][j]);
            if (j < n - 1)
            {
                printf(" ");
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

void printResultsMemoization(int arr[], int n)
{
    int *prefixSum = malloc((n + 1) * sizeof(int));
    if (prefixSum == NULL)
    {
        fprintf(stderr, "Memory allocation fialed for prefixSum.\n");
        exit(1);
    }

    computePrefixSum(arr, n, prefixSum);

    // Initialize memo matrix
    int **memoMatrix = malloc(n * sizeof(int *));
    if (memoMatrix == NULL)
    {
        fprintf(stderr, "Memory allocation failed for memoMatrix.\n");
        free(prefixSum);
        exit(1);
    }

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

        for (int j = 0; j < n; j++)
        {
            memoMatrix[i][j] = -1;
        }
    }

    int result = minMemoized(0, n - 1, n, prefixSum, memoMatrix);
    printf("%d\n", result);

    // Free memory
    for (int i = 0; i < n; i++)
    {
        free(memoMatrix[i]);
    }
    free(memoMatrix);
    free(prefixSum);
}

void printResultsRecursive(int arr[], int n)
{
    int *prefixSum = malloc((n + 1) * sizeof(int));
    if (prefixSum == NULL)
    {
        fprintf(stderr, "Memory allocation failed for prefixSum.\n");
        exit(1);
    }
    computePrefixSum(arr, n, prefixSum);
    int recursiveCallCount = 0; // Not needed for this
    int result = minRecursive(arr, 0, n - 1, n, prefixSum, &recursiveCallCount);
    printf("%d\n", result);

    free(prefixSum);
}

void printRecursiveCallCount(int arr[], int n)
{
    int *prefixSum = malloc((n + 1) * sizeof(int));
    if (prefixSum == NULL)
    {
        fprintf(stderr, "Memory allocation failed for prefixSum.\n");
        exit(1);
    }

    computePrefixSum(arr, n, prefixSum);

    int recursiveCallCount = 0;
    minRecursive(arr, 0, n - 1, n, prefixSum, &recursiveCallCount);
    printf("%d\n", recursiveCallCount);

    free(prefixSum);
}

int minDynamic(int arr[], int n, int *prefixSum, int **dpMatrix)
{
    // Base case = dpMatrix[i][i] = 0
    // This is set during initialization

    // Fill dp matrix
    for (int length = 2; length <= n; length++)
    {
        for (int i = 0; i <= n - length; i++)
        {
            int j = i + length - 1;
            dpMatrix[i][j] = INT_MAX;
            int total_sum = sumArray(i, j, prefixSum);
            for (int k = i; k < j; k++)
            {
                int cost = dpMatrix[i][k] + dpMatrix[k + 1][j] + total_sum;
                if (cost < dpMatrix[i][j])
                {
                    dpMatrix[i][j] = cost;
                }
            }
        }
    }
    return dpMatrix[0][n - 1];
}

void printResultsDynamic(int arr[], int n)
{
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
                dpMatrix[i][j] = 0;
            }
            else
            {
                dpMatrix[i][j] = -1;
            }
        }
    }
    int result = minDynamic(arr, n, prefixSum, dpMatrix);
    printf("%d\n", result);

    // Free memory
    for (int i = 0; i < n; i++)
    {
        free(dpMatrix[i]);
    }
    free(dpMatrix);
    free(prefixSum);
}

void printDynamicTable(int arr[], int n)
{
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
    minDynamic(arr, n, prefixSum, dpMatrix);

    // Print the dpMatrix
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d", dpMatrix[i][j]);
            if (j < n - 1)
                printf(" ");
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