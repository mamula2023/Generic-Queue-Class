#include "queue.h"
/*
 typedef struct{
	int length;
	void* firstElement;
	int elementSize;
	QueueFreeFunction freeFn;
} Queue;
*/
// typedef void (*QueueFreeFunction)(void *elemAddr);

void QueueNew(Queue* queue, int elementSize, QueueFreeFunction freeFn){
	queue->logicalSize = 0;
	queue->physicalSize = 1;
	queue->currentElement = 0;
	queue->elemSize = elementSize;
	queue->freeFn = freeFn;	
	queue->generalMemory = malloc(queue->elemSize*queue->physicalSize);
}

void QueueDispose(Queue* queue){
}

void expandMemory(Queue* queue){

}

void QueueEnqueue(Queue* queue, void* elemAddr){
	if(queue->logicalSize == queue->physicalSize)
		expandMemory(queue);
	int offset/*it bytes*/ = queue->elemSize * (queue->currentElement + queue->logicalSize);
	void* destination = queue->generalMemory + offset;
	memcpy(destination, elemAddr, queue->elemSize);
	queue->logicalSize = queue->logicalSize + 1;
}

void* QueuePeek(Queue* queue, void* auxData, bool returnPointer){
	int offset = queue->elemSize * queue->currentElement;
	void* addr = queue->generalMemory + offset;

	if(returnPointer){
		return addr;
	}
	memcpy(auxData, addr, queue->elemSize);	
	return NULL;
}

void QueueDequeue(Queue* queue){

}

int QueueSize(Queue* queue){
	return queue->logicalSize;
}
