#pragma once

#include<queue>
#include<pthread.h>
//提供一个线程安全的任务队列
struct task_t{
	void *(*start_routine)(void*);
	void *arg;
};

class Safequeue{
		queue<task_t> qu;
		pthread_mutex_t lock;
		
	public:
		Safequeue()
		{
			pthread_mutex_init(lock);
		}
		~Safequeue()
		{
			pthread_mutex_destroy(lock);
		}

		void Push(const task_t &t)
		{
			pthread_mutex_lock(&lock);
			qu.push(t);
			pthread_mutex_unlock(&lock);
		}
		void Pop()
		{
			pthread_mutex_lock(&lock);
			qu.pop();
			pthread_mutex_unlock(&lock);
		}
		task_t Front()
		{
			pthread_mutex_lock(&lock);
			task_t ret = qu.front();
			pthread_mutex_unlock(&lock);
			return ret;
		}
};
