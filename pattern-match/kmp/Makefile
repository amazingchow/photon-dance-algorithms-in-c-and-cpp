build:
	gcc -O2 -g -Wall test.c kmp.c -o kmp-tester -std=c99 -ltcmalloc -lprofiler -lunwind

# https://gperftools.github.io/gperftools/heapprofile.html
run-heapprof:
	LD_PRELOAD=/usr/local/lib/libtcmalloc.so HEAPPROFILE=~/Desktop/algo-repo/pattern-match/kmp/prof/heapprof ./kmp-tester

check-heapprof:
	pprof ./kmp-tester ~/Desktop/algo-repo/pattern-match/kmp/prof/heapprof.0001.heap

# https://gperftools.github.io/gperftools/cpuprofile.html
run-cpuprof:
	LD_PRELOAD=/usr/local/lib/libtcmalloc.so CPUPROFILE=~/Desktop/algo-repo/pattern-match/kmp/prof/cpuprof.out ./kmp-tester

check-cpuprof:
	pprof ./kmp-tester ~/Desktop/algo-repo/pattern-match/kmp/prof/cpuprof.out