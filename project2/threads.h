#include "q.h"
#define stack_size 8192

void start_thread(void(*function) (void))
{
	void *stack = malloc(stack_size);
	TCB_t *tcb = (TCB_t *)malloc(sizeof(TCB_t));
	init_TCB(tcb,function,stack,stack_size);
	AddQ(&RunQ,tcb);
}

void run()
{
	ucontext_t parent;
	getcontext(&parent);
	swapcontext(&parent,&(RunQ->context));
}

void yield()
{
	ucontext_t parent;
	getcontext(&parent);
	RunQ->context = parent;
	RotateQ(&RunQ);
	swapcontext(&parent,&(RunQ->context));
}
