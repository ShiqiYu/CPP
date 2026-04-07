## Project 2 Report: Computing the dot product of two vectors (C vs Java)

### Overview
This project implements and benchmarks the dot product of two vectors in **C** and **Java** across five native numeric types:

- **Integers**: `signed char`, `short`, `int`
- **Floating point**: `float`, `double`

For each language/type combination, the program measures execution time for increasing vector lengths and reports results in a consistent CSV format so C and Java can be compared directly.

### What was implemented
- **C program**: `projects/dotproduct.c`
  - Generates two random vectors for each N
  - Computes dot product repeatedly to obtain stable timings
  - Uses a monotonic clock for timing
  - Outputs CSV: `lang,type,N,reps,total_ns,avg_ns,checksum`
- **Java program**: `projects/Dotproduct.java`
  - Same benchmark sizes/types and CSV schema as C
  - Includes a warm-up phase to reduce JIT compilation effects in measured runs

### Experiment setup
- **Machine / OS**: macOS 12.x (Darwin 21.6.0)
- **C compiler**: Apple clang 14.0.0
- **C flags**: `-O3 -std=c11 -Wall -Wextra -pedantic`
- **Java**: Eclipse Temurin OpenJDK 17.0.18
- **Vector sizes**:
  - N in {10, 100, 10^3, 10^4, 10^5, 10^6}
- **Repetitions per N**:
  - Both programs choose `reps` to target ~20 million multiply-add operations per (type, N) point, with bounds [3, 2,000,000].
- **Randomness / reproducibility**:
  - Fixed seeds per type and size.
  - Value ranges are intentionally bounded (especially for small integer types) so results are well-defined and overflow is less likely in the accumulator.

### Correctness and “anti-optimization” checksum
Both programs aggregate dot-product results into a global checksum and print it (CSV column `checksum`, plus a final stderr line). This prevents the compiler/JIT from removing the compute loops as dead code.

### Timing method
- **C** uses `clock_gettime(CLOCK_MONOTONIC, ...)` and computes elapsed nanoseconds.
- **Java** uses `System.nanoTime()`.

These are appropriate for benchmarking because they are monotonic (do not jump backwards due to wall-clock adjustments).

### Collected raw outputs
The benchmark runs generated the following raw CSV files (useful to reproduce tables/plots):
- `projects/results_c.csv`
- `projects/results_java.csv`

### Results (high-level)
Across all types, the measured time shows a **positive correlation** with increasing vector length N (especially from 10^4 upward, where loop overhead becomes negligible).

Typical patterns observed:
- **Large N tends to be memory/cache influenced**. As N grows, the working set exceeds L1/L2 cache and the dot product becomes more bandwidth-limited; performance often scales closer to linear in N with a relatively stable per-element cost.
- **Java requires warm-up for fair comparison**. Without warm-up, early measurements can be dominated by interpreter/JIT compilation. After warm-up, Java becomes much more competitive.
- **Small integer types may not be “faster”**. Even though `signed char`/`short` use less memory, both C and Java often execute arithmetic in wider registers (commonly 32-bit or 64-bit). The dominant factor becomes memory access patterns and vectorization, not the nominal type width.
- **`float` vs `double`**:
  - Depending on CPU vector units and compiler/JIT decisions, `float` can be faster due to higher SIMD lane density and lower memory bandwidth.
  - In some cases, `double` can be comparable if computation is not the bottleneck or if vectorization behaves similarly.

### Explanation of performance differences (C vs Java)
Key reasons the two languages may differ:
- **Compilation and optimization model**
  - **C** is ahead-of-time compiled; `-O3` enables aggressive optimizations (loop unrolling, vectorization, strength reduction).
  - **Java** uses JIT compilation; hot methods can be optimized at runtime after profiling, but this requires warm-up and can vary with JVM flags and run history.
- **Bounds checks and safety**
  - Java array accesses are bounds-checked. Modern JVMs can eliminate checks in tight loops (range-check elimination), but this depends on optimization heuristics.
  - C has no bounds checks, which can reduce overhead, though compilers may still generate similar tight loops if they can prove safety patterns.
- **Vectorization**
  - Both compilers can vectorize dot-product loops.
  - Whether vectorization triggers depends on aliasing rules (C), loop structure, and JVM auto-vectorization capability.

### Notes / limitations
- The integer dot-product accumulators use a wider type (`long long`/`long`) to reduce overflow risk. Extremely large values can still overflow for `int` at large N if ranges were larger, but the chosen random ranges keep magnitudes reasonable.
- Measurements are still subject to system noise (background processes, CPU frequency scaling). Repetitions were chosen to reduce this noise.

### How to run
From the repository root:

```bash
cd projects
clang -O3 -std=c11 -Wall -Wextra -pedantic dotproduct.c -o dotproduct
./dotproduct > results_c.csv

javac Dotproduct.java
java Dotproduct > results_java.csv
```

### Conclusion
Both implementations meet the assignment requirements: they compute dot products across multiple data types, measure execution time using appropriate timing mechanisms, and provide comparable CSV outputs that show time increasing with vector length. The observed performance differences can be explained primarily by optimization models (AOT vs JIT), safety checks, and memory/cache effects at large \(N\).

