/*******************************************************************/
/*	CSE 531 Distributed Multiprocessor Operating Systems	   */
/*				Project 2			   */
/*	Group members: Mugdha Kolhatkar Vijayalakshmi Kothandan    */
/*******************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Semaphor.h"

int readwritec = 0 , writewritec = 0 , readc = 0 , writec = 0, global_ID = 0;

Sem_t *read_sem,*write_sem,*mutex;

void reader_entry(int ID)
{

	printf("[reader: %d] Trying to read\n",ID);
	thread1(mutex);
	if(writewritec > 0 || writec > 0)
	{
		printf("[reader: %d] blocking for writer\n", ID);
		//We then increment the read counter and let other
		//other process use this mutex
		readwritec++;
		thread2(mutex);
		//Sleep on the read semaphore
		thread1(read_sem);
		readwritec--;

	}
	readc++;
	if( readwritec > 0 )
		thread2(read_sem);
	else
		thread2(mutex);
}

void reader_exit(int ID)
{
	thread1(mutex);
	readc--;
	if(readc == 0 && writewritec > 0 )
	{
		//If the code enters here we have waiting writers
		//the write_sem is for these open writers
		thread2(write_sem);
	}
	else
		thread2(write_sem);
	
}

void writer_entry(int ID)
{
	printf("[writer: %d] trying to write\n",ID);
	thread1(mutex);
	if(readc > 0 || writec > 0 )
	{
		printf("[writer: %d] blocking for others\n", ID);
		writewritec++;
		thread2(mutex);
		thread1(write_sem);
		writewritec--;
	}
	writewritec++;
	thread2(mutex);
}

void writer_exit(int ID)
{
	thread1(mutex);
	writec--;
	if(readwritec > 0)
		thread2(read_sem);
	else if( writewritec > 0 )
		thread2(write_sem);
	else
		thread2(mutex);
}

void reader()
{
	int ID;
	thread1(mutex);
	ID = global_ID++;
	thread2(mutex);
	while(1)
	{
		reader_entry(ID);
		printf("[writer: %d] Writing :-) \n",ID);
		sleep(1);
		writer_exit(ID);
	}

}

int main()
{
	mutex = CreateSemaphore(1);
	read_sem = CreateSemaphore(0);
	write_sem = CreateSemaphore(0);
	
	start_thread(reader);
	start_thread(reader);
	start_thread(reader);
	start_thread(reader);
	start_thread(reader);
	start_thread(reader);
	start_thread(reader);
	start_thread(reader);
	
	run();
}
