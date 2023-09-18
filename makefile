all:
	g++ tsalloc.cpp test.cpp -lgtest -pthread -o tsalloc-test