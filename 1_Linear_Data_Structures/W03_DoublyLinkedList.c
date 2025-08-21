#include <stdio.h>
#include <stdlib.h>


typedef struct Node {
    struct Node* next; 
    struct Node* prev; 
    int data;    
} Node;

void printListPointer(Node* headPointer) {
    // 마지막 노드에 도달할때 까지 리스트를 순회하면서 출력
    // 마지막 노드를 출력하고 루프를 탈출
    for(; headPointer != NULL ; headPointer =  headPointer->next )
    {
        printf("%d -> ", headPointer->data);
        if (headPointer->next == NULL) break;
    }
    printf("NULL\n");

    for(; headPointer != NULL ; headPointer =  headPointer->prev )
    {
        printf("%d -> ", headPointer->data);
        if (headPointer->prev == NULL) break;
    }
    printf("NULL\n");
    
}
    

Node* insertNode(Node** headPP, Node* followingNodeP, int newData)
{
    Node* tempNodeP = *headPP;

    // head 앞에 Node를 추가하는 경우
    if (*headPP == followingNodeP)
    {
        Node* newNodeP = (Node*) malloc(sizeof(Node));
        newNodeP->data = newData;
        newNodeP->next = *headPP;

        //새 Node가 head가 될 것이기 때문에 새 Node의 prev는 NULL
        newNodeP->prev = NULL;
        //새 Node 다음 Node가 NULL인 상황은 처음으로 Node를 추가하는 상황
        if (followingNodeP != NULL) followingNodeP->prev = newNodeP;

        *headPP = newNodeP;
        return newNodeP;
    }
    // head외 다른 Node 앞에 Node를 추가하는 경우
    else
    {
        tempNodeP = followingNodeP->prev; //  변경한 내용: tempNode의 시작주소는 followingNode의 prev에 담겨있다. 

        // 새로운 Node를 선언
        Node* newNodeP = (Node*) malloc(sizeof(Node));
        newNodeP->data = newData;

        // 새로운 Node의 next와 prev를 연결
        newNodeP->next = tempNodeP->next;
        newNodeP->prev = tempNodeP;

        // 새로운 Node 이전 Node의 next를 수정
        tempNodeP->next = newNodeP;

        // 새로운 Node 다음 Node의 prev를 수정
        if (newNodeP->next != NULL) tempNodeP->next->prev = newNodeP;

        return newNodeP;
    }
}

void deleteNode(Node** headPP, Node* deleteNodeP)
{
    Node* tempNodeP = *headPP;

    // head를 삭제하는 경우
    if (*headPP == deleteNodeP)
    {
        if(tempNodeP->next != NULL)        
            tempNodeP->next->prev = NULL;
        *headPP = tempNodeP->next;
        free(tempNodeP);
    }
    // head외 다른 Node를 삭제하는 경우
    else
    {
        tempNodeP = deleteNodeP->prev; // 변경한 내용: tempNode의 시작주소는 deleteNode의 prev에 담겨있다. 

        // 삭제 대상 Node의 next의 prev가 temp Node가 됩니다
        if(deleteNodeP->next != NULL)
            deleteNodeP->next->prev = tempNodeP;

        // 삭제 대상 Node의 next가 삭제 대상 Node 이전 Node의 next
        tempNodeP->next = deleteNodeP->next;

        // 삭제 대상 Node를 삭제
        free(deleteNodeP);
    }
}

int main()
{
    Node* headPointer = NULL;

    Node* insertedNode1 = insertNode(&headPointer, headPointer, 10);
    Node* insertedNode2 = insertNode(&headPointer, headPointer, 20);
    Node* insertedNode3 = insertNode(&headPointer, headPointer, 30);
    Node* insertedNode4 = insertNode(&headPointer, headPointer, 40);
    Node* insertedNode5 = insertNode(&headPointer, headPointer, 50);
    printListPointer(headPointer);

    deleteNode(&headPointer, insertedNode1);
    //deleteNode(&head, insertedNode2);
    //deleteNode(&head, insertedNode3);
    //deleteNode(&head, insertedNode4);
    deleteNode(&headPointer, insertedNode5);
    printListPointer(headPointer);

    return 0;
}