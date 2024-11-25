#include <stdio.h>
#include <limits.h>
#include "algos.h"

// Globals
int recursiveCallCount = 0; // counter
int **memoMatrix = NULL;
int n;                 // Make n global for ease of access
int *prefixSum = NULL; // For calculating sum

// Calclate the sum of array elements from index 'start' to 'end'
int sumArray(int start, int end)
{
    return prefixSum[end + 1] - prefixSum[start];
}

int minRecursive(int arr[], int start, int end)
{
    // Increment our call counter at the start of each recursion
    recursiveCallCount++;

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
        int cost = sumArray(start, end) + minRecursive(arr, start, k) + minRecursive(arr, k + 1, end);
        // If better min_cost is found, update min_cost to cost
        if (cost < min_cost)
        {
            min_cost = cost;
        }
    }
    return min_cost;
}

int minMemoized(int start, int end)
{
    if (start >= end)
    {
        return 0;
    }

    if (memoMatrix[start][end] != -1)
    {
        return memoMatrix[start][end];
    }

    int min_cost = INT_MAX;
    int total_sum = sumArray(start, end);

    for (int k = start; k < end; k++)
    {
        int cost = total_sum + minMemoized(start, k) + minMemoized(k + 1, end);
        if (cost < min_cost)
        {
            min_cost = cost;
        }

        memoMatrix[start][end] = min_cost;
        return min_cost;
    }
}

void computePrefixSum(int arr[])
{
    prefixSum = malloc((n + 1) * sizeof(int));
    prefixSum[0] = 0;
    for (int i = 0; i < n; i++)
    {
        prefixSum[i + 1] = prefixSum[i] + arr[i];
    }
}

void printMemoizationMatrix()
{

    // Initalize our memo matrix and fill with -1's
    memoMatrix = malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
    {
        memoMatrix[i] = malloc(n * sizeof(int));
        for (int j = 0; j < n; j++)
        {
            memoMatrix[i][j] = -1;
        }
    }

    minMemoized(0, n - 1);

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
}

void printResultsMemoization()
{
    memoMatrix = malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
    {
        memoMatrix[i] = malloc(n * sizeof(int));
        for (int j = 0; j < n; j++)
        {
            memoMatrix[i][j] = -1;
        }
    }

    int result = minMemoized(0, n - 1);
    printf("%d\n", result);

    // Free memory
    for (int i = 0; i < n; i++)
    {
        free(memoMatrix[i]);
    }
    free(memoMatrix);
}

void printResultsRecursive(int arr[], int n)
{
    int result = minRecursive(arr, 0, n - 1);
    printf("%d\n", result);
}

void printRecursiveCallCount(int arr[], int n)
{
    recursiveCallCount = 0;
    minRecursive(arr, 0, n - 1);
    printf("%d\n", recursiveCallCount);
}