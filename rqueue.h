#ifndef __RICHARD_QUEUE__
#define __RICHARD_QUEUE__

#include "queue.h"

#define STAILQ_POOL_CREATE(head, type) STAILQ_HEAD(head, type) head = STAILQ_HEAD_INITIALIZER(head);

#define STAILQ_POOL_EXTEND(free_queue_head, entry, mem_start, num) do{ \
	        int _block_idx = num - 1; \
	        for (; _block_idx >= 0; --_block_idx) \
	        { \
			STAILQ_INSERT_TAIL(free_queue_head, (mem_start) + _block_idx, entry); \
		} \
} while(0);

#define STAILQ_POOL_ALLOC(free_queue_head, item, entry) do{ \
	        if (STAILQ_EMPTY(free_queue_head)) \
	        { \
			item = NULL; \
		} \
		else \
		{ \
	        	item = STAILQ_FIRST(free_queue_head); \
	        	STAILQ_REMOVE_HEAD(free_queue_head, entry); \
		} \
} while(0);

#define STAILQ_POOL_FREE(free_queue_head, item, entry) do { \
	        STAILQ_INSERT_TAIL(free_queue_head, item, entry); \
} while(0);

#endif
