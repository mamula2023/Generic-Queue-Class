#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "queue.h"
#include <string.h>
void startInfo(char info[]){
	printf("%s\n", "====================================");
	printf("%s %s\n", "starting", info);
}
void endInfo(char info[]){
	printf("%s\n", "====================================");
	printf("%s %s\n", "finisehd", info);
}
void generalInfo(char info[]){
	printf("-%s\n", info);
}

void testUsingPointerReturning(){
	Queue q;
	QueueNew(&q, sizeof(int), NULL);
	int testSize = 100000000;
	
	printf("populating numbers from 0 to %d\n", testSize);
	for(int i = 0; i<testSize; i++){
		QueueEnqueue(&q, &i);
	}
	printf("populated\n");

	printf("checking if elements are returned in correct order with pointer returning\n");
	for(int i = 0; i<testSize; i++){
		int result = *(int*)(QueuePeek(&q, NULL, true));
		assert(result == i);
		QueueDequeue(&q);
	}
	printf("checked\n");
	QueueDispose(&q); 
	
}
void testWithoutPointerReturning(){
	Queue q;
	QueueNew(&q, sizeof(int), NULL);
	int testSize = 10000000;	
	printf("populating again\n");
	for(int i = 0;i <testSize; i++){
		QueueEnqueue(&q, &i);
	}
	printf("populated\n");
	
	printf("checking if elements are returned in correct order with copying element to provided pointer\n");
	for(int i = 0; i<testSize; i++){
		int test;
		QueuePeek(&q, &test, false);
		assert(test == i);
		QueueDequeue(&q);
	}
	printf("checked\n");
	QueueDispose(&q);

}
void simpleNumberTests(){
	startInfo("simple number tests\n");
	testUsingPointerReturning();
	testWithoutPointerReturning();

	endInfo("simple number test\n");
}
void simpleCharacterTests(){
	
}

void simpleTest(){
	simpleNumberTests();
	simpleCharacterTests();
}

int main(){
	simpleTest();
}
