ROOT_PATH=$(shell pwd)/..

all: build clean

build: vector.o libvector.a
	mkdir -p ${ROOT_PATH}/bin && cp libvector.a ${ROOT_PATH}/bin

vector.o: vector.c
	$(CC) ${CFLAGS} -c vector.c -o vector.o ${INCLUDES}

libvector.a:
	ar rcs libvector.a vector.o

clean:
	rm -f vector.o libvector.a
