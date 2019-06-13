#include<iostream>
using namespace std;

#include"test.hpp"

int main()
{
	struct task_t tt;
	int a = 10;

	tt.start_routine = &func;
	tt.arg = (void*)&a;
	(tt.start_routine)(tt.arg);

	return 0;
}
