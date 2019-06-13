#ifndef __PTHREADPOOL_HPP
#define __PTHREADPOOL_HPP

#include<pthread.h>
#include<queue>

#include<string>
void Log(std::string msg)
{
	std::cout << '['<< msg << ']' << ":" << __FILE__<< ":" << __LINE__ << std::endl;
}

struct task_t{
	void *(*start)(void*);
	void *arg;
};


class PthreadPool
{
		static void *work(void *arg)
		{
			PthreadPool *pool = (PthreadPool*)arg;
			while(1)
			{
				Log("static void *work(void *arg)");

				pthread_mutex_lock(&pool->lock);
				while(pool->task.empty())
					pthread_cond_wait(&pool->cond,&pool->lock);//假如条件成立，则阻塞该线程到cond这个条件变量的队列中

				task_t tt = pool->task.front();//所有的线程从队列中拿数据
				pool->task.pop();

				pthread_mutex_unlock(&pool->lock);
				
				(tt.start)(tt.arg);//拿到数据之后，开始真正的执行
			}
			return pool;
		}
	public:
		PthreadPool(int cur_pthread_ = 3,int max_pthread_ = 10):
		max_pthread(max_pthread_ ),
		cur_pthread(cur_pthread_ ),
		tid(NULL)
		{
			Log("PthreadPool");
			//假定传进来的参数是正确的，我现在不做判断
			pthread_mutex_init(&lock,NULL);
			pthread_cond_init(&cond,NULL);
			for(int i = 0; i < cur_pthread ;++i)
			{
				tid = new pthread_t[cur_pthread];
				pthread_create(tid + i,NULL,work,this);

				pthread_detach(tid[i]);
			}
		}
		~PthreadPool()
		{
			delete []tid;
		}

		void Append(const task_t &t)//把函数指针，函数参数都扔进队列
		{
			Log("Append");
			pthread_mutex_lock(&lock);
			task.push(t);
			pthread_mutex_unlock(&lock);

			pthread_cond_signal(&cond);
		}


	private:
		int max_pthread;//最大线程数量
		int cur_pthread;//现在线程数量
		pthread_t *tid;//该数组存储所有线程的tid
		queue<task_t> task;//任务队列
		
		pthread_mutex_t lock;
		pthread_cond_t cond;
};

#endif
