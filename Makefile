CC=g++
CFLAGS=-O0 -fPIC -Werror -Wall

TESTS=test1 t-test1
HEADERS=buddyAlgorithmHeader.h

all:	${TESTS} libmalloc.so

clean:
	rm -rf *.o *.so ${TESTS}

libmalloc.so: malloc.o realloc.o calloc.o free.o reallocArray.o memalign.o posixMemAlign.o
	$(CC) $(CFLAGS) -shared -Wl,--unresolved-symbols=ignore-all $^ -o $@

%: %.cpp
	$(CC) $(CFLAGS) $< -o $@ -lpthread

# For every XYZ.c file, generate XYZ.o.
%.o: %.cpp ${HEADERS}
	$(CC) $(CFLAGS) $< -c -o $@

check1:	libmalloc.so test1 t-test1
	LD_PRELOAD=`pwd`/libmalloc.so

check:	libmalloc.so ${TESTS}
	LD_PRELOAD=`pwd`/libmalloc.so ./test1 ./t-test1

dist: clean
	dir=`basename $$PWD`; cd ..; tar cvf $$dir.tar ./$$dir; gzip $$dir.tar
