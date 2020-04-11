CURRENT_PATH=$(shell pwd)
VECTOR_INCLUDE=${CURRENT_PATH}/vector

INCLUDES=-I${VECTOR_INCLUDE}

CFLAGS :=  -Wall -Wextra -std=c99 -pedantic -Wmissing-prototypes -Wstrict-prototypes \
    -Wold-style-definition -Werror -O3


MAKE_FLAGS=INCLUDES="${INCLUDES}" CFLAGS="${CFLAGS}"
MODULES_DIRS := vector


all: format modules test-all

build: modules

re: clean all

clean:
	for dir in ${MODULES_DIRS}; do \
		$(MAKE) clean -C $$dir ${MAKE_FLAGS};  \
	done

	rm -rf test/build/

modules:
	for dir in ${MODULES_DIRS}; do \
		$(MAKE) -C $$dir ${MAKE_FLAGS}; \
	done


test-all: test-build test-run

test-build:
	cd test && mkdir -p build && cd build && cmake .. && make

test-run:
	cd test/build && make && ./vector_test


format:
	find . -regex '.*\.\(c\|h\)' -exec clang-format -style=file -i {} \;

cleanall: clean
	rm -rf bin