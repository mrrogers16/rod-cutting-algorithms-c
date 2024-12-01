#ifndef ALGOS_H
#define ALGOS_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Calculates sum of array elements from index 'start' to 'end'
int sumArray(int start, int end, int *prefixSum);

// Compute prefix sum to speed up sum calculations
void computePrefixSum(int arr[], int n, int *prefixSum);

// Recursive solution functions
void printResultsRecursive(int arr[], int n);
void printRecursiveCallCount(int arr[], int n);
int minRecursive(int arr[], int start, int end, int n, int *prefixSum, int *recursiveCallCount);

// Memoization solution functions
int minMemoized(int start, int end, int n, int *prefixSum, int **memoMatrix);
void printResultsMemoization(int arr[], int n);
void printMemoizationMatrix(int arr[], int n);

// Dynamic Programming solution functions
int minDynamic(int arr[], int n, int *prefixSum, int **dpMatrix);
void printResultsDynamic(int arr[], int n);
void printDynamicTable(int arr[], int n);

#endif // ALGOS_H
