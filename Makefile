CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

all: hash_search heap_sort heap_step dataset_gen radix_sort radix_step

hash_search: hash_table/Hash_table_search.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

heap_sort: heap_sort/heap_sort.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

heap_step: heap_sort/heap_sort_step.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

dataset_gen: heap_sort/dataset_generator.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

radix_sort: radix_algo/radix_sort.cpp
	$(CXX) $(CXXFLAGS) -Iradix_algo -o $@ $<

radix_step: radix_algo/radix_sort_step.cpp
	$(CXX) $(CXXFLAGS) -Iradix_algo -o $@ $<

clean:
	rm -f hash_search heap_sort heap_step dataset_gen radix_sort radix_step
