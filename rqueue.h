#ifndef __RICHARD_QUEUE__
#define __RICHARD_QUEUE__

#include "queue.h"

#define STAILQ_POOL_CREATE(head, type) STAILQ_HEAD(head, type) head = STAILQ_HEAD_INITIALIZER(head);

#define STAILQ_POOL_EXTEND(head, entry, mem_start, num) do{ \
	        int _block_idx = num - 1; \
	        for (; _block_idx >= 0; --_block_idx) \
	        { \
			STAILQ_INSERT_TAIL(head, (mem_start) + _block_idx, entry); \
		} \
} while(0);

#define STAILQ_POOL_ALLOC(head, item, entry) do{ \
	        if (STAILQ_EMPTY(head)) \
	        { \
			item = NULL; \
		} \
		else \
		{ \
	        	item = STAILQ_FIRST(head); \
	        	STAILQ_REMOVE_HEAD(head, entry); \
		} \
} while(0);

#define STAILQ_POOL_FREE(head, item, entry) do { \
	        STAILQ_INSERT_TAIL(head, item, entry); \
} while(0);

#endif
