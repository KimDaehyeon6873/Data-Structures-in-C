#include <stdio.h>
#include <stdlib.h>

typedef int DataType;

typedef struct LinkedStack {    
    struct LinkedStack* next; 
    struct LinkedStack* prev; 
    DataType data;    
} LinkedStack; 


void printListPointer(LinkedStack* topNodeP) {
    // 마지막 노드에 도달할때 까지 리스트를 순회하면서 출력
    // 마지막 노드를 출력하고 루프를 탈출
    printf("Top -> ");
    for(; topNodeP != NULL ; topNodeP =  topNodeP->prev )
    {
        printf("%d -> ", topNodeP->data);
        if (topNodeP->prev == NULL) break;
    }
    printf("Bottom\n");

    printf("Bottom -> ");
    for(; topNodeP != NULL ; topNodeP =  topNodeP->next )
    {
        printf("%d -> ", topNodeP->data);
        if (topNodeP->next == NULL) break;
    }
    printf("Top\n");    
}    

// topNodeP가 NULL인지 확인하는 함수
void isEmpty_2(LinkedStack* topNodeP)
{
    if(topNodeP == NULL)
    {
        printf("Stack is Empty! \n");
    }
}

void push(LinkedStack** topNodePP, int newData)
{
    // 처음으로 push 하는 경우, 처음으로 Node를 추가하는 경우
    if (*topNodePP == NULL)
    {
        LinkedStack* newNodeP = (LinkedStack*) malloc(sizeof(LinkedStack));
        newNodeP->data = newData;

        // Node가 하나뿐이라 next,prev 모두 NULL
        newNodeP->next = NULL;
        newNodeP->prev = NULL;

        // Node가 하나뿐이라 새 Node가 top
        *topNodePP = newNodeP;
    }    
    else
    {            
        LinkedStack* newNodeP = (LinkedStack*) malloc(sizeof(LinkedStack));
        newNodeP->data = newData;

        // 새 Node는 top 위에 추가되므로 새 Node의 prev는 기존의 top
        newNodeP->prev = *topNodePP;

        // 새 Node는 top이 될 것이므로 새 Node의 next는 NULL
        newNodeP->next = NULL;

        // 기존의 top의 next는 NULL 이었으나 이제는 새 Node가 next
        (*topNodePP)->next = newNodeP;

        // 새 Node가 새로운 top
        *topNodePP = newNodeP;
    }
}

DataType pop(LinkedStack** topNodePP)
{   
    // 삭제 대상이자 출력 대상은 top
    LinkedStack* deleteNodeP = *topNodePP;

    // 출력 데이터 추출
    DataType returnData = deleteNodeP->data;

    // 삭제 대상 Node의 이전 Node가 새로운 top
    *topNodePP = deleteNodeP->prev;

    if (*topNodePP != NULL)
    {
        // 새로운 top의 prev는 NULL
        (*topNodePP)->next = NULL;
        // 삭제 대상을 삭제
        free(deleteNodeP);

        return returnData;
    }
    else
    {
        // 삭제 후 stack이 비어있다면 topNodeP는 NULL
        *topNodePP = NULL;
        printf("Last pop: %d\n", returnData);
        printf("There is no more data in the stack. \n");
        free(deleteNodeP);
        exit(0);
    }
}




int main()
{
    LinkedStack* topNodeP = NULL;

    isEmpty_2(topNodeP);
    push(&topNodeP, 10);
    push(&topNodeP, 20);
    push(&topNodeP, 30);
    printf("pop: %d\n", pop(&topNodeP));
    push(&topNodeP, 40);
    push(&topNodeP, 50);
    push(&topNodeP, 60);
    printListPointer(topNodeP);

    printf("pop: %d\n", pop(&topNodeP));
    push(&topNodeP, 70);
    push(&topNodeP, 80);
    printListPointer(topNodeP);

    printf("pop: %d\n", pop(&topNodeP));
    printf("pop: %d\n", pop(&topNodeP));
    isEmpty_2(topNodeP);
    printListPointer(topNodeP);

    printf("pop: %d\n", pop(&topNodeP));
    printf("pop: %d\n", pop(&topNodeP));
    printf("pop: %d\n", pop(&topNodeP));
    isEmpty_2(topNodeP);

    printListPointer(topNodeP);
    printf("pop: %d\n", pop(&topNodeP));
    // 여기 이후로 exit(0)이 호출되므로 아래 코드는 실행되지 않음
    // 모든 스택을 비우고 나서 다시 채울 수 없는 문제가 발생함. 
    // Q. exit(0)을 사용하지 않고 pop에서 exited with code=3221225477 를 다룰 수 있는 방법이 무엇인가요?

    printf("pop: %d\n", pop(&topNodeP));
    printf("pop: %d\n", pop(&topNodeP));
    isEmpty_2(topNodeP);
    printListPointer(topNodeP);


    push(&topNodeP, 22);
    push(&topNodeP, 33);
    isEmpty_2(topNodeP);
    printListPointer(topNodeP);
    printf("pop: %d\n", pop(&topNodeP));
    printf("pop: %d\n", pop(&topNodeP));


    return 0;
}


