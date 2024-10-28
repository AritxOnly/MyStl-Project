COMPILER=clang++
CFLAGS=-Wall -g
CXXVERSION=c++20

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

all: stackbench vectorbench stringbench

stack-base-test.o: ./test-case/stack-base-test.cpp
	@${COMPILER} ${CFLAGS} -std=${CXXVERSION} -c $< -o $@
	@echo Compiling $@

vector-base-test.o: ./test-case/vector-base-test.cpp
	@${COMPILER} ${CFLAGS} -std=${CXXVERSION} -c $< -o $@
	@echo Compiling $@

string-base-test.o: ./test-case/string-base-test.cpp
	@${COMPILER} ${CFLAGS} -std=${CXXVERSION} -c $< -o $@
	@echo Compiling $@

# 通用配置
%.o: %.cpp %.h
	@${COMPILER} ${CFLAGS} -std=${CXXVERSION} -c $< -o $@

clean:
	@rm -f stackbench vectorbench stringbench *.o