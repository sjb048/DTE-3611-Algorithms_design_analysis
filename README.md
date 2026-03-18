# DTE-3611 — Algorithms Design & Analysis
 
A C++ library and benchmark suite implementing, analysing, and comparing classical algorithms across sorting, string matching, graph traversal, path finding, dynamic programming, and network flow.
 
**Author:** Sumaia Jahan Brinti  
**Build system:** CMake (Qt Creator)  
**Language:** C++17
 
---
 
## Project structure
 
```
.
├── benchmark_and_testing/
│   ├── benchmarks/
│   │   └── my_benchmarks/
│   │       └── my_first_benchmarks.cpp   # Custom benchmark entry point
│   ├── predefined/                        # Provided benchmark harnesses
│   ├── predefined_utils/                  # Benchmark utility helpers
│   ├── templates/                         # Benchmark templates
│   ├── unittests/                         # Unit test suites
│   └── CMakeLists.txt
├── cmake/
│   └── testing_utils.cmake               # Shared CMake helpers for tests
├── lib3611/
│   ├── include/lib3611/
│   │   ├── utils/
│   │   │   ├── concepts/
│   │   │   │   ├── graphs.h
│   │   │   │   └── operators.h
│   │   │   └── graph_utils.h
│   │   ├── w1d1_2_sort/                  # Week 1 — Sorting algorithms
│   │   │   ├── binary_sort.h
│   │   │   ├── counting_sort.h
│   │   │   ├── custom_aa_sort.h
│   │   │   └── radix_sort.h
│   │   ├── w1d3_string_match/            # Week 1 — String matching
│   │   │   ├── bmh_search.h
│   │   │   ├── kmp_search.h
│   │   │   ├── kr_search.h
│   │   │   └── naive_search.h
│   │   ├── w1d4_graph_traversal/         # Week 1 — Graph traversal
│   │   │   ├── breadth_first_search.h
│   │   │   └── depth_first_search.h
│   │   ├── w1d5_graph_path_finding/      # Week 1 — Shortest paths
│   │   │   ├── astar_search.h
│   │   │   ├── dijkstra_shortest_paths.h
│   │   │   └── operators.h
│   │   ├── w2_knapsack/                  # Week 2 — Dynamic programming
│   │   │   └── knapsack.h
│   │   ├── w2_subset_sum/                # Week 2 — NP / DP
│   │   │   └── subset_sum.h
│   │   └── w3_network_flow/              # Week 3 — Network flow
│   │       ├── bellman_ford.h
│   │       ├── network_flow.h
│   │       └── operators.h
│   └── CMakeLists.txt
├── CMakeLists.txt
└── README.md
```
 
---
 
## Algorithm modules
 
### Week 1 — Sorting (w1d1_2_sort)
 
Implements and benchmarks two custom sorting algorithms against the STL sort baseline.
 
| Algorithm | Complexity | Notes |
|-----------|-----------|-------|
| Binary sort | O(n log n) | Uses binary search to find insertion position |
| Counting sort | O(n + k) | Efficient when value range k is small |
| Custom AA sort | varies | Custom hybrid implementation |
| Radix sort | O(nk) | Non-comparison, digit-by-digit sort |
 
Benchmark results show that counting sort achieves near-linear performance for small-range integer data, while binary sort scales better in general-purpose cases.
 
---
 
### Week 1 — String matching (w1d3_string_match)
 
Four pattern-matching algorithms benchmarked on text corpora of varying sizes.
 
| Algorithm | Full name | Complexity |
|-----------|-----------|-----------|
| `naive_search` | Naïve / brute-force | O(nm) |
| `kmp_search` | Knuth-Morris-Pratt | O(n + m) |
| `bmh_search` | Boyer-Moore-Horspool | O(n/m) best case |
| `kr_search` | Karp-Rabin | O(n + m) average |
 
---
 
### Week 1 — Graph traversal (w1d4_graph_traversal)
 
| Algorithm | Data structure | Time complexity |
|-----------|---------------|----------------|
| BFS | Queue (FIFO) | O(V + E) |
| DFS | Stack (LIFO) | O(V + E) |
 
BFS finds the shortest path in unweighted graphs. DFS is edge-based and is used for cycle detection and topological ordering. Both are implemented as header-only templates parameterised over the graph type via `utils/concepts/graphs.h`.
 
---
 
### Week 1 — Shortest path finding (w1d5_graph_path_finding)
 
| Algorithm | Handles negative weights | Complexity |
|-----------|--------------------------|-----------|
| Dijkstra | No | O((V + E) log V) |
| A\* | No | O(E) best case with admissible heuristic |
 
A custom `operators.h` defines the heuristic and edge-cost interfaces required by A\*.
 
---
 
### Week 2 — Dynamic programming: Subset sum (w2_subset_sum)
 
The subset sum problem asks whether any subset of a given integer set sums to a target T. It is NP-complete in the general case. The implementation uses bottom-up tabulation with a 2-D DP table.
 
**Time complexity:** O(N × T) where N is the number of elements and T is the target sum.  
**Space complexity:** O(N × T)
 
Key concepts covered: top-down memoisation vs bottom-up tabulation, NP / NP-complete / NP-hard classification.
 
---
 
### Week 2 — Dynamic programming: 0/1 Knapsack (w2_knapsack)
 
Given N items each with weight w_i and value v_i, and a knapsack capacity W, find the subset with maximum total value that fits.
 
**Time complexity:** O(N × W)  
**Space complexity:** O(N × W)
 
The DP table `V[i][w]` stores the best value achievable using the first i items within capacity w. Traceback recovers the chosen items.
 
Greedy approaches are contrasted against the DP solution to illustrate why greedy fails to guarantee global optimality here.
 
---
 
### Week 3 — Network flow (w3_network_flow)
 
| Algorithm | Complexity | Notes |
|-----------|-----------|-------|
| Ford-Fulkerson | O(E · f\*) | Augmenting-path based; f\* = max flow value |
| Edmonds-Karp | O(V² · E) | Ford-Fulkerson with BFS augmentation; flow-independent |
| Bellman-Ford | O(V · E) | Single-source shortest paths; handles negative edges |
| Push-Relabel (Goldberg-Tarjan) | O(V² · E) | Preflow-based; avoids explicit augmenting paths |
 
The module also covers the **max-flow min-cut theorem**: the value of the maximum flow equals the capacity of the minimum cut. Residual graphs and augmenting paths are central to the Ford-Fulkerson family of algorithms.
 
Bellman-Ford additionally detects negative-weight cycles, making it suitable for graphs where Dijkstra's algorithm cannot be applied.
 
---
 
## Building
 
### Prerequisites
 
- CMake ≥ 3.16
- C++17-capable compiler (GCC ≥ 9, Clang ≥ 10, or MSVC 2019+)
- Qt Creator (optional, for IDE support)
 
### Configure and build
 
```bash
# From the project root
mkdir build && cd build
cmake ..
cmake --build .
```
 
### Running benchmarks
 
```bash
# After building
./benchmark_and_testing/benchmarks/my_benchmarks/my_first_benchmarks
```
 
### Running unit tests
 
```bash
cd build
ctest --output-on-failure
```
---
 
## Key concepts
 
**Dynamic Programming** solves problems by breaking them into overlapping subproblems and storing results (memoisation or tabulation) to avoid redundant computation. Both knapsack and subset sum use this approach.
 
**NP-completeness** — subset sum is NP-complete: any solution can be verified in polynomial time, but no polynomial-time solver is known. The DP approach is pseudo-polynomial, efficient when T is small relative to the input.
 
**Amortised analysis** accounts for the average cost of operations over a sequence rather than the worst individual case. Covered techniques include the aggregate method, accounting method, and potential method.
 
**Max-flow min-cut** — by the theorem, the maximum flow through a network equals the minimum capacity of any cut separating source from sink. Proven via flow conservation and weak duality.
 
---
 
## References
 
- GeeksforGeeks — Dynamic Programming, Sorting Algorithms, Counting Sort, NP-Completeness, Subset Sum
- Programiz — Dynamic Programming
- Software Testing Help — C++ DFS
- Musser, D. (1997). *Introspective Sorting and Selection Algorithms*. Software Practice and Experience, 27:983–993.
- Edmonds, J. & Karp, R. (1972). Theoretical improvements in algorithmic efficiency for network flow problems.
 