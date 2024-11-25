#ifndef ALGOS_H
#define ALGOS_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Globals
extern int recursiveCallCount; // Counter for recursive calls
extern int **memoMatrix;       // Memoization matrix
extern int *prefixSum;         // Prefix sum array
extern int n;

int sumArray(int start, int end);

int minRecursive(int arr[], int start, int end);

int minMemoized(int start, int end);

void computePrefixSum(int arr[]);

void printMemoizationMatrix(void);

void printResultsMemoization(void);

void printResultsRecursive(int arr[], int n);

void printRecursiveCallCount(int arr[], int n);

#endif // ALGOS_H
