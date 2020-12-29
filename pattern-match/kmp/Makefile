build:
	gcc -O2 -g -Wall test.c kmp.c -o kmp-tester -std=c99 -ltcmalloc -lprofiler -lunwind

# https://gperftools.github.io/gperftools/heapprofile.html
run-heapprof:
	LD_PRELOAD=/usr/local/lib/libtcmalloc.so HEAPPROFILE=./prof/heapprof ./kmp-tester

check-heapprof:
	pprof ./kmp-tester ./prof/heapprof.0001.heap

# https://gperftools.github.io/gperftools/cpuprofile.html
run-cpuprof:
	LD_PRELOAD=/usr/local/lib/libtcmalloc.so CPUPROFILE=./prof/cpuprof.out ./kmp-tester

check-cpuprof:
	pprof ./kmp-tester ./prof/cpuprof.out
