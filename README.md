# Rod‑Cutting Algorithms in C
Compare the performance and implementation trade‑offs of three approaches to the classic minimum‑cost rod cutting problem:

### Naive recursion 
  – exponential time, elegant but slow

### Top‑down memoization 
  – same recursion, O(n²) time with an n × n memo table

### Bottom‑up dynamic programming 
  – iterative O(n²) solution that also exposes the full DP table

#### The repo contains:

##### algos.c / algos.h 
  – core logic for prefix‑sum preprocessing, recursive, memoized, and DP solvers, plus helpers to print results or full tables.

##### project3.c 
  – CLI driver; choose the algorithm with a single‑letter flag (R, r, M, m, D, d) and pass any list of positive rod lengths.

##### project3.sh 
  – sample script that compiles with gcc, runs each variant, and echoes runtime metrics.

##### Makefile 
  – one‑command build (make all) and clean targets.

## Quick start
```
make               # or: gcc -Wall -O2 project3.c algos.c -o rodcut
./rodcut D 5 4 3 2 6 7   # Dynamic‑programming cost for 5 rods of given lengths
./rodcut m 4 2 2 3 4     # Print memoization table for 4 rods
```
Great for CS courses or anyone benchmarking recursive vs. memoized vs. DP techniques on a real combinatorial‑optimization task.
