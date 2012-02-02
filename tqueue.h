#ifndef __RICHARD_THREAD_QUEUE__
#define __RICHARD_THREAD_QUEUE__

#include "rqueue.h"
#include <pthread.h>

#define TQUEUE_ENTRY STAILQ_ENTRY
#define TQUEUE_HEAD STAILQ_HEAD
#define TQUEUE_CREATE(queue_typename, entry_name, type) \
	struct { \
		pthread_mutex_t lock; \
		TQUEUE_HEAD(entry_name, type) entry_name; \
		unsigned int size; \
	} queue_typename;

#define TQUEUE_INIT(queue_head, entry_name) do {\
	pthread_mutex_init(&((queue_head)->lock), NULL); \
	STAILQ_INIT(&((queue_head)->entry_name)); \
} while(0);

#define TQUEUE_EXTEND(queue_head, entry_name, mem_start, num) do { \
	pthread_mutex_lock(&((queue_head)->lock)); \
	STAILQ_POOL_EXTEND(&((queue_head)->entry_name), entry_name, mem_start, num); \
	pthread_mutex_unlock(&((queue_head)->lock)); \
} while(0);

#define TQUEUE_SIZE_INIT(queue_head, entry_name, type, num) do { \
	struct type *mem_start; \
	TQUEUE_INIT(queue_head, entry_name); \
	mem_start = (struct type *)calloc(num, sizeof(struct type)); \
	TQUEUE_EXTEND(queue_head, entry_name, mem_start, num); \
} while(0);

#define TQUEUE_POP(queue_head, item, entry_name) do { \
	pthread_mutex_lock(&((queue_head)->lock)); \
	STAILQ_POOL_ALLOC(&((queue_head)->entry_name), item, entry_name); \
	if ((item) != NULL) \
	{ \
		--((queue_head)->size); \
	} \
	pthread_mutex_unlock(&((queue_head)->lock)); \
	if ((item) == NULL) \
	{ \
		sleep(1); \
	} \
} while((item) == NULL);

#define TQUEUE_PUSH(queue_head, item, entry_name) do { \
	pthread_mutex_lock(&((queue_head)->lock)); \
	STAILQ_POOL_FREE(&((queue_head)->entry_name), item, entry_name); \
	++((queue_head)->size); \
	pthread_mutex_unlock(&((queue_head)->lock)); \
} while(0);

#endif
