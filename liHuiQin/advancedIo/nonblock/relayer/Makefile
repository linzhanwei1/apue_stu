CFLAGS+=-D_FILE_OFFSET_BITS=64 -D_GNU_SOURCE -Wall
LDFLAGS+=-pthread
all:relayer
relayer:relayer.o main.o
	gcc $^ -o $@ ${LDFLAGS}

.PHONY:clean
clean:
	rm -rf *.o relayer