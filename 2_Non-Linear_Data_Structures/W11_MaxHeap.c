#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define HEAP_SIZE 100

void swap(int* a, int* b)
{
    int temp;
    temp = *b;
    *b = *a;
    *a = temp;
}

void printHeap(int* heap, int lastIdx)
{
    printf("[START] printHeap\n");
    int currentTab = (int)log2(lastIdx);
    int currentDepth = 0;
    int currentIdx = 0;
    while(currentIdx <= lastIdx)
    {
        int currentNodes = pow(2.0, currentDepth);
        for(int j=0; j<currentTab; j++) printf("\t");
        
        for(int i=0; i<currentNodes; i++)
        {   
            if(currentIdx <= lastIdx) printf("%d\t", heap[currentIdx++]);            
        }
        printf("\n");
        currentTab--;
        currentDepth++;
    }
    printf("[END] printHeap\n");
}

void insertHeap(int* heap, int* lastIdx, int data)
{
    heap[++*lastIdx] = data;
    int currentIdx = *lastIdx;
    int parentIdx = (currentIdx - 1)/2;

    if (parentIdx >= 0)
    {
        while(heap[parentIdx] < data)
        {
            swap(&heap[parentIdx], &heap[currentIdx]);
            currentIdx = parentIdx;
            parentIdx = (currentIdx - 1)/2;
        }    
    }
}

int deleteHeap(int* heap, int* lastIdx)
{
    int returnValue = heap[0];
    swap(&heap[0], &heap[(*lastIdx)--]);
    int currentIdx = 0;

    while(currentIdx <= *lastIdx)
    {        
        int leftChildIdx = currentIdx*2 + 1;
        int rightChildIdx = currentIdx*2 + 2;

        /******************************/
        /* maxHeapify가 완료되는 2가지 상황 */
        /******************************/
        // 자식 element가 없는 경우 heapify 완료 
        if (leftChildIdx > *lastIdx) break;
        // 왼쪽 자식 element만 있지만 현재 탐색중인 element의 값보다 작은 경우 heapify 완료
        else if (heap[currentIdx] > heap[leftChildIdx] && rightChildIdx > *lastIdx ) break;


        /*****************************/
        /* 왼쪽 자식 element만 있을 때 */
        /****************************/
        // 오른쪽 자식 element는 없는데 왼쪽 자식 element가 현재 탐색중인 element의 값보다 큰 경우 swap
        // 현재 탐색중인 element의 인덱스를 왼쪽 자식 element의 인덱스로 이동
        if (heap[currentIdx] < heap[leftChildIdx] && rightChildIdx > *lastIdx )
        {
            swap(&heap[currentIdx], &heap[leftChildIdx]);
            currentIdx = leftChildIdx;
        }

        /***************************************************************************/
        /* 양쪽 자식 element가 다 있는데 한쪽만 부모 element의 값보다 클 때 그 값과 swap */
        /***************************************************************************/
        // 왼쪽 자식 element의 값은 부모의 값보다 크고 오른쪽 자식 element의 값은 부모보다 작은 상황
        // 현재 탐색중인 element의 인덱스를 왼쪽 자식 element의 인덱스로 이동
        else if (heap[currentIdx] < heap[leftChildIdx] && heap[currentIdx] > heap[rightChildIdx])
        {
            swap(&heap[currentIdx], &heap[leftChildIdx]);
            currentIdx = leftChildIdx;
        }
        // 왼쪽 자식 element의 값은 부모의 값보다 작고 오른쪽 자식 element의 값은 부모보다 큰 상황
        // 현재 탐색중인 element의 인덱스를 오른쪽 자식 element의 인덱스로 이동
        else if (heap[currentIdx] < heap[rightChildIdx] && heap[currentIdx] > heap[leftChildIdx])
        {
            swap(&heap[currentIdx], &heap[rightChildIdx]);
            currentIdx = rightChildIdx;
        }        

        /**************************************************************************************/
        /* 양쪽 자식 element가 다 있고 모두 부모 보다 값이 큰 상황에서는 더 큰 element와 swap */
        /**************************************************************************************/        
        // 왼쪽이 오른쪽보다 큰 경우
        else if (heap[currentIdx] < heap[leftChildIdx] && heap[currentIdx] < heap[rightChildIdx] 
            && heap[leftChildIdx] > heap[rightChildIdx])
        {
            swap(&heap[currentIdx], &heap[leftChildIdx]);
            currentIdx = leftChildIdx;
        }        
        // 오른쪽이 왼쪽보다 큰 경우
        else if (heap[currentIdx] < heap[leftChildIdx] && heap[currentIdx] < heap[rightChildIdx] 
            && heap[leftChildIdx] < heap[rightChildIdx])
        {
            swap(&heap[currentIdx], &heap[rightChildIdx]);
            currentIdx = rightChildIdx;
        }
        
        // 이외의 모든 상황은 heapify 완료 상황
        else
        {
            break;
        }
    }

    return returnValue;
}

int main(int argc, char* argv[])
{
    int* heap = (int*)malloc(HEAP_SIZE*sizeof(int));
    int lastIdx = -1;

    insertHeap(heap, &lastIdx, 10);
    insertHeap(heap, &lastIdx, 9);
    insertHeap(heap, &lastIdx, 13);
    insertHeap(heap, &lastIdx, 6);
    insertHeap(heap, &lastIdx, 8);
    insertHeap(heap, &lastIdx, 3);
    insertHeap(heap, &lastIdx, 7);
    insertHeap(heap, &lastIdx, 21);
    insertHeap(heap, &lastIdx, 15);
    insertHeap(heap, &lastIdx, 1);
    insertHeap(heap, &lastIdx, 5);

    printHeap(heap, lastIdx);
    int returnValue = deleteHeap(heap, &lastIdx);
    printf("\n### Returned from heap: %d\n", returnValue);
    printHeap(heap, lastIdx);
    returnValue = deleteHeap(heap, &lastIdx);
    printf("\n### Returned from heap: %d\n", returnValue);
    printHeap(heap, lastIdx);
    returnValue = deleteHeap(heap, &lastIdx);
    printf("\n### Returned from heap: %d\n", returnValue);
    printHeap(heap, lastIdx);
    returnValue = deleteHeap(heap, &lastIdx);
    printf("\n### Returned from heap: %d\n", returnValue);
    printHeap(heap, lastIdx);
    returnValue = deleteHeap(heap, &lastIdx);
    printf("\n### Returned from heap: %d\n", returnValue);
    printHeap(heap, lastIdx);
    returnValue = deleteHeap(heap, &lastIdx);
    printf("\n### Returned from heap: %d\n", returnValue);
    printHeap(heap, lastIdx);
    returnValue = deleteHeap(heap, &lastIdx);
    printf("\n### Returned from heap: %d\n", returnValue);
    printHeap(heap, lastIdx);
    returnValue = deleteHeap(heap, &lastIdx);
    printf("\n### Returned from heap: %d\n", returnValue);
    printHeap(heap, lastIdx);
    returnValue = deleteHeap(heap, &lastIdx);
    printf("\n### Returned from heap: %d\n", returnValue);
    printHeap(heap, lastIdx);
    returnValue = deleteHeap(heap, &lastIdx);
    printf("\n### Returned from heap: %d\n", returnValue);
    printHeap(heap, lastIdx);
    returnValue = deleteHeap(heap, &lastIdx);
    printf("\n### Returned from heap: %d\n", returnValue);
    printHeap(heap, lastIdx);

    return 0;
}