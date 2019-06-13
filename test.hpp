
struct task_t{
	void *(*start_routine)(void*);
	void *arg;
};

void *func(void* arg)
{
	int *pa = (int*)arg;
	cout << *pa << endl;
	return pa;
}

