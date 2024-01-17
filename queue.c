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
	//TODO
}

void expandMemory(Queue* queue){
	if(queue->currentElement == 0){
		queue->physicalSize *= 2;
		queue->generalMemory = realloc(queue->generalMemory, queue->elemSize*queue->physicalSize);
	}
	else{
		int offset = queue->elemSize*queue->currentElement;
		void* source = queue->generalMemory + offset;
		int size = queue->logicalSize * queue->elemSize;
		memmove(queue->generalMemory, source, size);
		queue->currentElement = 0;

		//not the most elegant approach
		queue->physicalSize *= 1.5;
		queue->generalMemory = realloc(queue->generalMemory, queue->elemSize*queue->physicalSize);
	}
}

void QueueEnqueue(Queue* queue, void* elemAddr){
	if(queue->logicalSize+queue->currentElement == queue->physicalSize)
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
	assert(queue->logicalSize > 0);
	if(queue->freeFn != NULL){
		int offset = queue->elemSize * queue->currentElement;	
		void* address = queue->generalMemory + offset;
		queue->freeFn(address);
	}
	queue->logicalSize--;
	queue->currentElement++;
}

int QueueSize(Queue* queue){
	return queue->logicalSize;
}
