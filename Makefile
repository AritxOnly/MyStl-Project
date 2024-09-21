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

stack-base-test.o: ./test-case/stack-base-test.cpp
	${COMPILER} ${CFLAGS} -std=${CXXVERSION} -c $< -o $@

vector-base-test.o: ./test-case/vector-base-test.cpp
	${COMPILER} ${CFLAGS} -std=${CXXVERSION} -c $< -o $@

# 通用配置
%.o: %.cpp %.h
	@${COMPILER} ${CFLAGS} -std=${CXXVERSION} -c $< -o $@

clean:
	@rm -f stackbench vectorbench *.o