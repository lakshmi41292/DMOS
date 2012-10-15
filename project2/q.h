#include <stdio.h>
#include <stdlib.h>
#include "TCB.h"


void InitQ (TCB_t *Q)
{
	Q = NULL;
}

void AddQ (TCB_t **Q, TCB_t *item)
{
	TCB_t *temp =  NULL;
	//Check if the queue is empty
	if (*Q == NULL)	{	
		//since it is the only item in the queue...
		*Q = item;
		(*Q)->prev = *Q;
		(*Q)->next = *Q;
	}
	else	{		
		//There are more than 1 elements present in the queue
		//hence adding the new element at the end of the list
		//pointed by the previous pointer of Q
		temp = (*Q)->prev;
		temp->next = item;
		temp = temp->next;
		temp->next = *Q;
		temp->prev = (*Q)->prev;
		(*Q)->prev = temp;
	}
}

TCB_t *DelQ (TCB_t **Q)	
{
	TCB_t *temp = NULL;

	//Check to see if the Queue is empty
	if ( *Q == NULL)	{	 
		printf("Queue Empty, No TCB context present!\n");
		return NULL;
	}
	else if ((*Q)->next == *Q)	{ 
	//Check to see if there is only one element present in the queue
		temp = *Q;
		*Q = NULL;
		return temp;
	}
	else	{
	//More than one element present in the queue
		temp = *Q;
		(*Q) = (*Q)->next;
		(*Q)->prev = temp->prev;
		temp->prev->next=*Q;
		temp->next = NULL;
		temp->prev = NULL; 
		return temp;
	}
}

void RotateQ(TCB_t **Q)
{
	if ( *Q == NULL)	{		
		//Check if the queue is empty
		printf("Queue Empty , No TCB Context present\n");
		return;
	}
	*Q = (*Q)->next;
}
