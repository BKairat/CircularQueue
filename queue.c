#include "queue.h"
 
queue_t* create_queue(int capacity){
    queue_t *ret;
    ret = malloc(sizeof(queue_t));
    if (ret == NULL){
        fprintf(stderr, "Can not allocate memory for queue!\n");
        exit(-1);
    }
    ret -> data = (void *)malloc(sizeof(void*) * capacity);
    if (ret -> data == NULL){
        free(ret);
        ret = NULL;
        fprintf(stderr, "Can not allocate memory for queues data!\n");
        exit(-1);
    }
    ret -> size = 0;
    ret -> capacity = capacity;
    ret -> first = -1;
    ret -> last = 0;
    return ret;
}
 
/* deletes the queue and all allocated memory */
void delete_queue(queue_t *queue){
    if ( queue != NULL ){
        if ( queue -> data != NULL ){
            free( queue->data );
        }
        free(queue);
    }
}
 
/*
 * inserts a reference to the element into the queue
 * returns: true on success; false otherwise
 */
bool push_to_queue(queue_t *queue, void *data){
    if ( queue -> last == queue -> first ) return false;
    if ( queue -> first == -1 ) queue -> first = 0;
    queue -> data[queue -> last] = data;
    queue -> last = (queue -> last + 1) % queue -> capacity;
    queue -> size ++;
    return true;
}
 
/*
 * gets the first element from the queue and removes it from the queue
 * returns: the first element on success; NULL otherwise
 */
void* pop_from_queue(queue_t *queue){
    if (queue -> first == -1) return NULL;
    void *ret = queue -> data[queue -> first];
    queue->first = (queue->first + 1) % queue->capacity;
    queue->size--;
    if (queue->first == queue->last){
        queue->first = -1;
        queue->last = 0;
    }
    return ret;
} 
 
/*
 * gets idx-th element from the queue, i.e., it returns the element that
 * will be popped after idx calls of the pop_from_queue()
 * returns: the idx-th element on success; NULL otherwise
 */
void* get_from_queue(queue_t *queue, int idx){
    if ( idx < 0 || queue -> size <= idx ) return NULL;
    return (queue -> data[(idx + queue->first) % queue->capacity]);
}
 
/* gets number of stored elements */
int get_queue_size(queue_t *queue){
    return queue -> size;
}