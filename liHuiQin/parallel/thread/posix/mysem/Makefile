LDFLAGS+=-pthread

all:mysem

mysem:main.o mysem.o
	gcc $^ -o $@ ${LDFLAGS}

.PHONY:clean
clean:
	rm -rf *.o mysem