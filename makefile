
MALLOB_BASE_DIRECTORY?='"."'

all: libipasirmallob.a

mallob_ipasir.o: src/mallob_ipasir.cpp src/mallob_ipasir.hpp
	g++ -DMALLOB_BASE_DIRECTORY=${MALLOB_BASE_DIRECTORY} -c -std=c++17 src/mallob_ipasir.cpp -Isrc

libipasirmallob.a: mallob_ipasir.o
	ar rvs libipasirmallob.a mallob_ipasir.o

runtest: test/ipasir_test.cpp mallob_ipasir.o
	g++ -o $@ $^
	mkdir -p .api/jobs.0/done .api/jobs.0/new .api/jobs.0/pending
	./runtest

clean:
	rm -rf mallob_ipasir.o libipasirmallob.a runtest .api