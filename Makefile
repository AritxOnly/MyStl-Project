COMPILER=clang++
CFLAGS=-Wall
CXXVERSION=c++20

stackbench: stack-base-test.o
	${COMPILER} ${CFLAGS} -std=${CXXVERSION} $< -o $@
	./$@

stack-base-test.o: ./test-case/stack-base-test.cpp
	${COMPILER} ${CFLAGS} -std=${CXXVERSION} -c $< -o $@

# 通用配置
%.o: %.cpp %.h
	${COMPILER} ${CFLAGS} -std=${CXXVERSION} -c $< -o $@

clean:
	rm -f stackbench *.o