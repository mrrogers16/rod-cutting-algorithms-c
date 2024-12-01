#ifndef ALGOS_H
#define ALGOS_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int sumArray(int start, int end, int *prefixSum);

int minRecursive(int arr[], int start, int end, int n, int *prefixSum, int *recursiveCallCount);

int minMemoized(int start, int end, int n, int *prefixSum, int **memoMatrix);

void computePrefixSum(int arr[], int n, int *prefixSum);

void printMemoizationMatrix(int arr[], int n);

void printResultsMemoization(int arr[], int n);

void printResultsRecursive(int arr[], int n);

void printRecursiveCallCount(int arr[], int n);

#endif // ALGOS_H
