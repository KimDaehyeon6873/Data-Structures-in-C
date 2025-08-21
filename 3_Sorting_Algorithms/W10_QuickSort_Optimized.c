#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_VALUE 2147483647
#define MIN_VALUE 1

// 두 값 바꾸는 swap 함수
void swap(int* i, int* j)
{
    int temp;

    temp = *i;
    *i = *j;
    *j = temp;
}

// 피벗을 기준으로 왼쪽이 작은 값, 오른쪽이 큰 값을 가지도록 배열을 분할. 분할 후 피벗의 최종 위치 반환
int swap_by_pivot(int* arr, int size)
{
    // 피벗은 왼쪽 첫번째로 합니다
    int pivot = arr[0];

    // 배열의 크기가 3 이상일 경우, 시작요소와 끝 요소, 중간 요소를 비교해서 중앙값 찾아 피벗 설정
    
    if (size >= 3)
    {
        int firstElement = 0;
        int middleElement = size/2;
        int lastElement = size -1;

        int a = arr[firstElement], b = arr[middleElement], c = arr[lastElement];

        int pivotIdx = 
            (a > b && a < c) ||  (a < b && a > c) ? firstElement:
            (b > a && b < c) ||  (b < a && b > c) ? middleElement: 
            lastElement;

        swap(&arr[0], &arr[pivotIdx]);

        pivot = arr[0];
    }
    

    // 왼쪽은 피벗의 다음 숫자부터 시작합니다
    int leftIdx = 1;

    // 오른쪽은 오른쪽 끝부터 시작합니다
    int rightIdx = size - 1;

    // 왼쪽 인덱스가 오른쪽 인덱스를 넘기 전까지 반복합니다
    // 피벗이 가장 작은값일 때에도 정상 동작해야 하기 때문에 반부등호를 사용합니다
    // 아래 while 조건에 부합하지 않아 중단되는 순간은 피벗을 기준으로 swap이 완료된 것입니다
    while (leftIdx <= rightIdx)
    {
        // 피벗보다 큰 값을 왼쪽부터 오른쪽으로 찾아나갑니다
        while (leftIdx <= rightIdx && arr[leftIdx] <= pivot) leftIdx++;

        // 피벗보다 작은 값을 오른쪽부터 왼쪽으로 찾아나갑니다
        while (leftIdx <= rightIdx && arr[rightIdx] > pivot) rightIdx--;

        // 발견된 "피벗보다 큰 값" 과 "피벗보다 작은 값" 을 바꿉니다
        // 이 때 leftIdx는 rightIdx보다 작아야 바꿀 수 있습니다
        if (leftIdx < rightIdx) swap(&arr[leftIdx++], &arr[rightIdx--]);
    }

    // while 반복문이 중단된 상태에서의 rightIdx는 왼쪽 배열의 오른쪽 끝을 가리킵니다
    // 이 값을 피벗과 교환하여 피벗을 기준으로 왼쪽으로는 작은값들, 오른쪽으로는 큰값들로 위치시킵니다
    swap(&arr[0], &arr[rightIdx]);
    return rightIdx;
}

void quickSort(int* arr, int size)
{
    if (size <= 1)
    {
        return;
    }
    else
    {   
        // 제자리 정렬로 구현하였으므로 별도의 배열을 반환받지 않고 대신 피벗의 위치를 반환받습니다
        int pivotIdx = swap_by_pivot(arr, size);

        // 왼쪽배열의 시작점은 원래 배열과 같습니다
        // 단, 왼쪽배열의 길이는 피벗 위치까지 입니다
        int* leftArray = arr;
        int leftSize = pivotIdx;

        // 제자리정렬이므로 피벗위치는 다시 왼쪽이나 오른쪽 배열범위에 넣을 필요가 없습니다
        // 오른쪽배열의 시작점은 피벗 위치 다음입니다
        // 오른쪽배열의 길이는 전체 길이에서 왼쪽배열의 길이에서 피벗 하나를 뺀 숫자입니다
        int* rightArray = arr + pivotIdx + 1;
        int rightSize = size - leftSize - 1;

        // 왼쪽배열과 오른쪽배열에 대해 퀵정렬을 재귀적으로 진행합니다
        quickSort(leftArray, leftSize);
        quickSort(rightArray, rightSize);
    }
}


int main(int argc, char* argv[])
{
    int arraySize = 1000000;

    // 무작위 배열 생성 
    srand(time(NULL));
    int* randomArray = (int*)malloc((arraySize)*sizeof(int));
    for (int i = 0; i < arraySize; i++) {
        randomArray[i] = ((rand() << 15) | rand()) %  10000000000 +1;
    }  
    
    printf("Before sort\n");
    for(int i=0; i<arraySize; i++)
    {
        printf("%d ", randomArray[i]);
    }
    printf("\n");

    clock_t start, finish;
    double duration;

    start = clock();
    quickSort(randomArray, arraySize);
    finish = clock();
    duration = (double)(finish - start) / CLOCKS_PER_SEC;

    printf("After sort\n");
    for(int i=0; i<arraySize; i++)
    {
        printf("%d ", randomArray[i]);
    }
    printf("\n");

    printf("%f\n", duration);

    free(randomArray);

    return 0;
}
