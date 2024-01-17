#ifndef _queue_
#define _queue_

#include "stdbool.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>

typedef void (*QueueFreeFunction)(void *elemAddr);

typedef struct{
	int logicalSize;
	int physicalSize;
	int currentElement;
	void* generalMemory;
	int elemSize;
	QueueFreeFunction freeFn;
	
} Queue;
/*
 * contructor for new queue. User should create own 
 * object of Queue structure and pass it to the contructor
 * by reference. This is generic class, so user should 
 * specify size of their own data type, usually using sizeof() 
 * functions. User should provide with function that will 
 * will be called on element during deleting queue or element.
 * It is useful if element is referencing another element, 
 * since this structure does not know about insides of elments.
 * User can provide NULL if other memory does not have to be
 * deallocated.
*/
void QueueNew(Queue* queue, int elementSize, QueueFreeFunction freefn);
/*
 * Frees all memory of specified queue and its elements. 
 * Does not automatically free other memory if element
 * has pointer outside queue. That is where provided 
 * QueueFreeFunction is neccessary.
*/
void QueueDispose(Queue* queue);

/*
 * Addes new element to end of the queue.
 * User should pass element by reference but, that original
 * element can be deleted as Queue will make its own copy.
 */
void QueueEnqueue(Queue* queue, void *elemAddr);

/*
 * QueuePeek method does not dequeue first element, but 
 * allows user to see its content. There are two possibilities:
 *  1. If user wants to get copy to its own memory, they should
 *  pass already allocated memory to auxData and false to 
 *  returnPointer parameter. method will return NULL
 *  2. If user wants to get pointer to original element 
 *  in the queue, they can pass false to auxData and true to
 *  returnPonter parameters. method will return pointer to
 *  first element. It is user's responsibity if they change original element in queue
*/
void* QueuePeek(Queue* queue, void* auxData, bool returnPointer);

/*
 * QueueDequeue method does not return anything. It just 
 * removes first element (using LIFO principle) and 
 * calls QueueFreeFunction if provided.
*/
void QueueDequeue(Queue* queue);

/*
 * returns number of elements in queue currently
*/
int QueueSize(Queue* queue);

/*
 * self-explanatory, returns false if there is at least one element
*/
bool QueueEmpty(Queue* queue);

#endif
