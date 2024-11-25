#include <stdio.h>
#include <limits.h>

// Calclate the sum of array elements from index 'start' to 'end'
int sumArray(int arr[], int start, int end)
{
    int sum = 0;
    for (int i = start; i <= end; i++)
    {
        sum += arr[i];
    }
    return sum;
}

int minRecursive(int arr[], int start, int end)
{

    // Base Case: Single rod or invalid range
    if (start >= end)
    {
        return 0;
    }

    int min_cost = INT_MAX;

    // Try all partitions
    for (int k = start; k < end; k++)
    {
        int cost = sumArray(arr, start, end) + minRecursive(arr, start, k) + minRecursive(arr, k + 1, end);

        if (cost < min_cost)
        {
            min_cost = cost;
        }
    }
    return min_cost;
}

void printResultsRecursive(int arr[], int n)
{
    int result = minRecursive(arr, 0, n - 1);
    printf("Minimum galvanization cost: %d\n", result);
}

int main(int argc, char *argv[])
{

    if (argc < 3)
    {
        printf("Usage: %s 'number of rods' '[rod lengths]'", argv[0]);
        return 1;
    }

    // parse rods
    int n = atoi(argv[1]);
    if (n <= 0)
    {
        printf("Number of rods must be positive.");
        return 1;
    }

    // parse rod lengths
    int rods[n];
    for (int i = 0; i < n; i++)
    {
        rods[i] = atoi(argv[2 + i]);
        if (rods[i] <= 0)
        {
            printf("Rod lengths must be positive.");
            return 1;
        }
    }

    // Call printResults() for output.
    printResultsRecursive(rods, n);

    return 0;
}