COMPILER=clang++
CFLAGS=-Wall -g
CXXVERSION=c++20
ALL=stackbench vectorbench stringbench mapbench

stackbench: stack-base-test.o
	@${COMPILER} ${CFLAGS} -std=${CXXVERSION} $< -o $@
	@echo Compile finished, running
	@./$@

vectorbench: vector-base-test.o
	@${COMPILER} ${CFLAGS} -std=${CXXVERSION} $< -o $@
	@echo Compile finished, running
	@./$@

stringbench: string-base-test.o
	@${COMPILER} ${CFLAGS} -std=${CXXVERSION} $< -o $@
	@echo Compile finished, running
	@./$@

mapbench: map-base-test.o
	@${COMPILER} ${CFLAGS} -std=${CXXVERSION} $< -o $@
	@echo Compile finished, running
	@./$@

all: ${ALL}

stack-base-test.o: ./test-case/stack-base-test.cpp
	@${COMPILER} ${CFLAGS} -std=${CXXVERSION} -c $< -o $@
	@echo Compiling $@

vector-base-test.o: ./test-case/vector-base-test.cpp
	@${COMPILER} ${CFLAGS} -std=${CXXVERSION} -c $< -o $@
	@echo Compiling $@

string-base-test.o: ./test-case/string-base-test.cpp
	@${COMPILER} ${CFLAGS} -std=${CXXVERSION} -c $< -o $@
	@echo Compiling $@

map-base-test.o: ./test-case/map-base-test.cpp
	@${COMPILER} ${CFLAGS} -std=${CXXVERSION} -c $< -o $@
	@echo Compiling $@

# 通用配置
%.o: %.cpp %.h
	@${COMPILER} ${CFLAGS} -std=${CXXVERSION} -c $< -o $@

clean:
	@rm -f ${ALL} *.o