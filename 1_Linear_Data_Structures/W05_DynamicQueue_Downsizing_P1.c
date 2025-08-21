#include <stdio.h>
#include <stdlib.h>

#define AVAILABLE 0
#define FULL 1
#define EMPTY 2

#define SUCCESS 0
#define FAIL    -1

typedef struct Queue
{    
    int tail;
    int head;
    int queueSize;
    int* data;    
} Queue;

int isFull(Queue* queue)  
{    
    if (queue->tail == queue->queueSize) return FULL;    

    return AVAILABLE;
}

int isEmpty(Queue* queue)  
{
    if (queue->head == queue->tail) return EMPTY;    

    return AVAILABLE;
}

void enqueue(Queue* queue, int data)
{
    if( isFull(queue) == FULL)
    {
        queue->data = (int*)realloc(queue->data, sizeof(int)*(queue->queueSize+1));
        if (queue->data !=NULL )
        {            
            queue->queueSize++;
            printf("[Enqueue] Queue data reallocated ");  
        }
        else
        {
            printf("[Enqueue] Failed\n");
            return;
        }
    }
    
    queue->data[queue->tail] = data;
    queue->tail = queue->tail + 1;

    printf("[Enqueue] data = %d, current head = %d, tail = %d, current queueSize=%d\n", data, queue->head, queue->tail, queue->queueSize);
}

int downsizingCount = 0;

int dequeue(Queue* queue)
{   
    if(isEmpty(queue) == EMPTY)
    {
        printf("[Dequeue] cannot dequeue, current queue is empty\n");
        return FAIL;
    }

    int data = queue->data[queue->head];
    queue->head = queue->head + 1;

    if(queue->head > (queue->queueSize * 7 / 10)) //head 인덱스가 큐 사이즈 70% 이상일 때 다운사이징
    {
        int currentIndex = 0;

        for(int i=queue->head; i < queue->tail ; i++)
        {
            queue->data[currentIndex++] = queue->data[i];
        }

        queue->head = 0;
        queue->tail = currentIndex;
        queue->queueSize = currentIndex;

        queue->data = (int*)realloc(queue->data, sizeof(int)*(queue->queueSize));
        
        downsizingCount++;
        printf("[Dequeue] Queue data reallocated %d time downsizing\n", downsizingCount);  
    }

    printf("[Dequeue] data = %d, current head = %d, tail = %d, queueSize=%d\n", data, queue->head, queue->tail, queue->queueSize);
    return data;
}

void printQueue(Queue* queue)
{
    printf("head -> ");
    int currentIndex = queue->head;

    for(int i=queue->head; i < queue->tail ; i++)
    {
        printf("%d(%d) -> ", queue->data[currentIndex], currentIndex);

        currentIndex = (currentIndex + 1) % queue->queueSize;
    }

    printf("tail\n");
}

int main(int argc, char* argv[])
{   
    Queue queue;
    queue.data=NULL;
    queue.tail=0;
    queue.head=0;
    queue.queueSize=0;

    enqueue(&queue, 1); // queueSize = 1
    enqueue(&queue, 2); // queueSize = 2
    enqueue(&queue, 3); // queueSize = 3
    printf("dequeue %d\n", dequeue(&queue)); // queueSize = 3
    printf("dequeue %d\n", dequeue(&queue)); // queueSize = 3
    enqueue(&queue, 4); // queueSize = 4
    enqueue(&queue, 5); // queueSize = 5
    printf("dequeue %d\n", dequeue(&queue)); // queueSize = 5
    enqueue(&queue, 6); // queueSize = 6
    enqueue(&queue, 7); // queueSize = 7
    enqueue(&queue, 8); // queueSize = 8
    enqueue(&queue, 9); // queueSize = 9
    enqueue(&queue, 10); // queueSize = 10
    enqueue(&queue, 11); // queueSize = 11
    enqueue(&queue, 12); // queueSize = 12
    enqueue(&queue, 13); // queueSize = 13
    printf("dequeue %d\n", dequeue(&queue)); // queueSize = 13
    printf("dequeue %d\n", dequeue(&queue)); // queueSize = 13
    enqueue(&queue, 14); // queueSize = 14
    printf("dequeue %d\n", dequeue(&queue)); // queueSize = 14
    enqueue(&queue, 15); // queueSize = 15
    printf("dequeue %d\n", dequeue(&queue)); // queueSize = 15
    enqueue(&queue, 16); // queueSize = 16
    enqueue(&queue, 17); // queueSize = 17
    enqueue(&queue, 18); // queueSize = 18
    printf("dequeue %d\n", dequeue(&queue)); // queueSize = 18
    printf("dequeue %d\n", dequeue(&queue)); // queueSize = 18
    printf("dequeue %d\n", dequeue(&queue)); // queueSize = 18
    printf("dequeue %d\n", dequeue(&queue)); // queueSize = 18
    enqueue(&queue, 19); // queueSize = 19
    enqueue(&queue, 20); // queueSize = 20
    enqueue(&queue, 21); // queueSize = 21
    enqueue(&queue, 22); // queueSize = 22
    enqueue(&queue, 23); // queueSize = 23
    enqueue(&queue, 24); // queueSize = 24
    enqueue(&queue, 25); // queueSize = 25
    enqueue(&queue, 26); // queueSize = 26
    enqueue(&queue, 27); // queueSize = 27
    enqueue(&queue, 28); // queueSize = 28
    enqueue(&queue, 29); // queueSize = 29
    enqueue(&queue, 30); // queueSize = 30
    printf("dequeue %d\n", dequeue(&queue)); // queueSize = 30
    printf("dequeue %d\n", dequeue(&queue)); // queueSize = 30
    printf("dequeue %d\n", dequeue(&queue)); // queueSize = 30
    printf("dequeue %d\n", dequeue(&queue)); // queueSize = 30
    printf("dequeue %d\n", dequeue(&queue)); // queueSize = 30
    printf("dequeue %d\n", dequeue(&queue)); // queueSize = 30
    printf("dequeue %d\n", dequeue(&queue)); // queueSize = 30
    printf("dequeue %d\n", dequeue(&queue)); // queueSize = 30
    printf("dequeue %d\n", dequeue(&queue)); // queueSize = 30
    printf("dequeue %d\n", dequeue(&queue)); // queueSize = 30
    printf("dequeue %d\n", dequeue(&queue)); // queueSize = 8
    printf("dequeue %d\n", dequeue(&queue)); // queueSize = 8
    printf("dequeue %d\n", dequeue(&queue)); // queueSize = 8
    printf("dequeue %d\n", dequeue(&queue)); // queueSize = 8
    printf("dequeue %d\n", dequeue(&queue)); // queueSize = 8
    printf("dequeue %d\n", dequeue(&queue)); // queueSize = 8
    printf("dequeue %d\n", dequeue(&queue)); // queueSize = 2

    printQueue(&queue);

    return 0;
}
