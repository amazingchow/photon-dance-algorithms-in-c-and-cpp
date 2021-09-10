#ifndef __LRU__H__
#define __LRU__H__

#include <stdio.h>
#include <stdlib.h>
#include "uthash.h"

// A Queue Node
typedef struct lru_qnode {
    struct lru_qnode *prev;
    struct lru_qnode *next;

    uint32_t page_num;
    char name[10];
    // make this structure hashable
    UT_hash_handle hh;
} lru_qnode_t;

// A Queue implemented using Doubly-Linked-List
typedef struct lru_queue {
    // number of filled frames
    uint32_t frames_count;
    // total number of frames
    uint32_t frames_total;
    lru_qnode_t *front, *rear;
    lru_qnode_t *frames;
} lru_queue_t;

static lru_qnode_t *new_lru_qnode(uint32_t page_num);
static lru_queue_t *new_lru_queue(int frames_total);
static int is_lru_queue_full(lru_queue_t *queue);
static int is_lru_queue_empty(lru_queue_t *queue);
static void lru_dequeue(lru_queue_t *queue);
void lru_put(lru_queue_t *queue, uint32_t page_num);
void lru_get(lru_queue_t *queue, uint32_t page_num);

#endif /* __LRU__H__ */
