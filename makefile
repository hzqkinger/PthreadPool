PthreadPool:PthreadPool.cc
	g++ $^ -o $@ -lpthread
.PHONY:clean
clean:
	rm -f PthreadPool
