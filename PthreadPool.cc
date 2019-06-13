#include<iostream>
using namespace std;
#include<unistd.h>
#include"PthreadPool.hpp"

void *func(void *arg)
{
	int *pa = (int*)arg;
	cout << *pa << endl;
	return pa;
}

int main()
{
	PthreadPool pp;
	for(int i = 0;;++i)
	{
		sleep(1);

		task_t t;
		t.start = func;
		t.arg = &i;
		pp.Append(t);
	}
	return 0;
}
