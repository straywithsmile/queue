#include "tqueue.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct ob_t {
	TQUEUE_ENTRY(ob_t) head_entry;
	int append;
}ob;

TQUEUE_CREATE(tqueue, head_entry, ob_t);
int main()
{
	ob *data;
	ob *item;
	int i;

	//ob_header *empty_queue = &(free_queue);
	TQUEUE_SIZE_INIT(&tqueue, head_entry, ob_t, 5);
	for (i = 0; i < 100; ++i)
	{
		TQUEUE_POP(&tqueue, item, head_entry);
		if (item->append == 0)
		{
			item->append = i + 1;
			printf("init %d %d\n", i, item->append);
		}
		else
		{
			printf("reuse %d %d\n", i, item->append);
		}
		TQUEUE_PUSH(&tqueue, item, head_entry);
	}

	/*
	TQUEUE_INIT(&tqueue, head_entry);
	data = (ob *)calloc(sizeof(ob), EXTEND_SIZE);
	do {
	        int _block_idx = EXTEND_SIZE - 1;
		pthread_mutex_lock(&((&tqueue)->lock));
	        for (; _block_idx >= 0; --_block_idx)
	        {
			STAILQ_INSERT_TAIL(&(tqueue.head_entry), data + _block_idx, head_entry);
		}
		pthread_mutex_unlock(&((&tqueue)->lock)); 
	} while(0);
	*/

	/*
	for (i = 0; i < EXTEND_SIZE; ++i)
	{
		data[i].append = EXTEND_SIZE - i;
	}
	STAILQ_POOL_EXTEND(&free_queue, head_entry, data, EXTEND_SIZE); 

	for (i = 0; i < EXTEND_SIZE; ++i)
	{
		TQUEUE_POP(&tqueue, item, head_entry);
		if (item->append == 0)
		{
			item->append = i;
			printf("init %d\n", i);
		}
		else
		{
			printf("reuse %d\n", i);
		}
		TQUEUE_PUSH(&tqueue, item, entry1);
	}
	for (i = 0; i < EXTEND_SIZE; ++i)
	{
		STAILQ_POOL_ALLOC(empty_queue, item, head_entry);
		printf("%d ", item->append);
		STAILQ_POOL_FREE(&free_queue, item, head_entry);
	}

	for (i = 0; i < EXTEND_SIZE; ++i)
	{
		STAILQ_POOL_ALLOC(empty_queue, item, head_entry);
		printf("%d ", item->append);
	}

	data = (ob *)calloc(sizeof(ob), EXTEND_SIZE);
	for (i = 0; i < EXTEND_SIZE; ++i)
	{
		data[i].append = EXTEND_SIZE - i + 200;
	}
	STAILQ_POOL_EXTEND(empty_queue, head_entry, data, EXTEND_SIZE);
	for (i = 0; i < EXTEND_SIZE; ++i)
	{
		STAILQ_POOL_ALLOC(empty_queue, item, head_entry);
		printf("%d ", item->append);
	}
	*/
}
