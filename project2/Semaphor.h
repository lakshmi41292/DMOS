#include "threads.h"

typedef struct Semaphore
{
	int val;
	TCB_t *waitQ;

}Sem_t;

Sem_t *CreateSemaphore(int val)
{
	Sem_t * temp = malloc(sizeof(Sem_t));
	InitQ(temp->waitQ);
	temp->val = val;
	return temp;
}

void thread1(Sem_t *sem)
{
	TCB_t *processblock = 0 ,*processnext = 0;
	sem->val--;
	if( sem->val < 0 )
	{
		processblock = (TCB_t *)DelQ(&RunQ);
		AddQ(&(sem->waitQ),processblock);
		processnext = RunQ;
		swapcontext(&(processblock->context),&(processnext->context));
	}
}

void thread2(Sem_t *sem)
{
	
	TCB_t *proc = 0;
	sem->val++;
	if( sem->val <= 0 )
	{
		proc = (TCB_t *)DelQ(&(sem->waitQ));
		AddQ(&RunQ,proc);
	}
	yield();
}
