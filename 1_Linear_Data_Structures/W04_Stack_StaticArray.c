#include <stdio.h>
#include <stdlib.h>

#define STACK_SIZE 10

void push(int* stack, int* top, int data)
{
    stack[*top] = data;
    *top=*top+1;
}

int pop(int* stack, int* top)
{
    int data = stack[*top-1];
    *top=*top-1;

    return data;
}

void printStack(int* stack, int top)
{
    printf("top -> ");
    for(int i=top-1; i >= 0; i--)
    {
        printf("%d -> ", stack[i]);
    }
    printf("bottom\n");

}

// main 함수에서 선언한 변수 top의 값을 받아 STACK_SIZE와 같은지 확인하는 함수. 4주차 과제 1번
int isFull(int top)
{
    if (top == STACK_SIZE)
    {
        printf("Stack is full! \n");
    }
}

// main 함수에서 선언한 변수 top의 값을 받아 0인지 확인하는 함수. 4주차 과제 2번번
void isEmpty_1(int top)
{
    if (top == 0)
    {
        printf("Stack is Empty! \n");
    }
}

int main(int argc, char* argv[])
{   
    int top=0;
    int stack[STACK_SIZE];
    
    isFull(top);
    isEmpty_1(top);
    push(stack, &top, 1);
    push(stack, &top, 2);
    push(stack, &top, 3);
    // printf("pop %d\n", pop(stack, &top));
    // printf("pop %d\n", pop(stack, &top));
    push(stack, &top, 4);
    push(stack, &top, 5);
    // printf("pop %d\n", pop(stack, &top));
    push(stack, &top, 6);
    push(stack, &top, 7);
    push(stack, &top, 8);
    push(stack, &top, 9);
    push(stack, &top, 10);
    // push(stack, &top, 11); //????
    printStack(stack, top);
    isFull(top);
    isEmpty_1(top);
}

// Q. 현재 stack의 길이를 10의 배열로 설정하였고 배열의 크기는 고정되어 있는데, 11번째 요소가 삽입되는 이유는 무엇인가요?

