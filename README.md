# Algorithms and Data Structures — Benchmarks & Visualizations

High-performance **C++** implementations, step-by-step visualizers, and empirical benchmarks for core sorting algorithms and data structures.

---

## 📚 Included Implementations

### 1. Radix Sort (`radix_algo/`)
- Non-comparative sorting algorithm with time complexity $\\mathcal{O}(d \cdot (n + k))$.
- Includes `radix_sort_step.cpp` to trace and visualize intermediate pass buckets and digit distributions.

### 2. Heap Sort (`heap_sort/`)
- In-place comparative sorting utilizing a max-heap with guaranteed $\\mathcal{O}(n \log n)$ time complexity.
- Includes step-by-step heapify visualization (`heap_sort_step.cpp`).
- Includes a configurable synthetic dataset generator (`dataset_generator.cpp`) for benchmarking.

### 3. Hash Table & Search Analysis (`hash_table/`)
- Custom hash table implementation supporting collision resolution and key search operations.
- Empirical search time benchmarking across variable load factors.

---

## 🚀 Building & Running

### 1. Compile All Modules
```bash
make
```

### 2. Run Benchmarks
- **Heap Sort:**
  ```bash
  ./heap_sort data/dataset_1000.csv
  ```
- **Radix Sort:**
  ```bash
  ./radix_sort data/dataset_1000.csv
  ```
- **Hash Table Search:**
  ```bash
  ./hash_search data/dataset_1000.csv
  ```

### 3. Generate Custom Datasets
```bash
./dataset_gen <num_records> output.csv
```
