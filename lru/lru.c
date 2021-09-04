#include "lru.h"
#include "uthash.h"

// A utility function to create a new Queue Node.
static lru_qnode_t* new_lru_qnode(unsigned page_num)
{
	lru_qnode_t* frame = (lru_qnode_t*)malloc(sizeof(lru_qnode_t));
	frame->page_num = page_num;
	frame->prev = frame->next = NULL;
	return frame;
}

// A utility function to create an empty LRU Queue.
static lru_queue_t* new_lru_queue(int frames_total)
{
	lru_queue_t* queue = (lru_queue_t*)malloc(sizeof(lru_queue_t));
	queue->frames_count = 0;
	queue->frames_total = frames_total;
	queue->front = queue->rear = NULL;
	queue->frames = NULL;
	return queue;
}

// A utility function to check if there is slot available inside LRU Queue.
static int is_lru_queue_full(lru_queue_t* queue)
{
	return queue->frames_count == queue->frames_total;
}

// A utility function to check if there is no slot available inside LRU Queue.
static int is_lru_queue_empty(lru_queue_t* queue)
{
	return queue->frames_count == 0;
}

// A utility function to delete a frame from LRU Queue.
static void lru_dequeue(lru_queue_t* queue)
{
	if (is_lru_queue_empty(queue))
	{
		return;
	}

	// If this is the only frame, then change front
	if (queue->front == queue->rear)
	{
		queue->front = NULL;
	}

	lru_qnode_t* frame = queue->rear;
	queue->rear = queue->rear->prev;
	if (queue->rear)
	{
		queue->rear->next = NULL;
	}

	HASH_DEL(queue->frames, frame);
	free(frame);
	queue->frames_count--;
}

// A function to add a page with given 'page_num' to LRU Queue.
void lru_put(lru_queue_t* queue, uint32_t page_num)
{
	// If the queue is full, remove the frame at the rear
	if (is_lru_queue_full(queue))
	{
		lru_dequeue(queue);
	}

	lru_qnode_t* frame = new_lru_qnode(page_num);
	frame->next = queue->front;

	// If this is the only frame, change both front and rear
	if (is_lru_queue_empty(queue))
	{
		queue->rear = queue->front = frame;

	}
	else // Else change the front
	{
		queue->front->prev = frame;
		queue->front = frame;
	}

	HASH_ADD_INT(queue->frames, page_num, frame);
	queue->frames_count++;
}

// A function to add a page with given 'page_num' to LRU Queue.
void lru_get(lru_queue_t* queue, uint32_t page_num)
{
	lru_qnode_t* ref;
	HASH_FIND_INT(queue->frames, &page_num, ref);

	// If the page is not in cache, bring it
	if (ref == NULL)
	{
		lru_put(queue, page_num);
	}
	else if (ref != queue->front)
	{
		ref->prev->next = ref->next;
		if (ref->next)
		{
			ref->next->prev = ref->prev;
		}

		if (ref == queue->rear) {
			queue->rear = ref->prev;
			queue->rear->next = NULL;
		}

		ref->next = queue->front;
		ref->prev = NULL;

		ref->next->prev = ref;

		queue->front = ref;
	}
}