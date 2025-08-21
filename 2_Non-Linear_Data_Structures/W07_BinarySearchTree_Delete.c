#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEFT 0
#define RIGHT 1
#define ROOT -1

typedef struct Node {
    struct Node* left; 
    struct Node* right; 
    int id;
    char data[10];
} Node;

void printBinaryTree(Node* node, int depth, int direction)
{    
    for (int i = 0; i < depth - 1; i++)    
        printf("\t");    

    if (depth > 1)
    {
        if (direction == LEFT) printf("left child: ");    
        else if (direction == RIGHT) printf("right child: ");    
        else printf("Unknown behavior\n");    
    }
    else
        printf("root: ");    

    printf("%d\n", node->id);

    if (node->left != NULL)    
        printBinaryTree(node->left, depth+1, LEFT);

    if (node->right != NULL)
        printBinaryTree(node->right, depth+1, RIGHT);
}

Node* searchNode(Node* node, int targetId)
{    
    if (node->id == targetId)
        return node;  

    else if (node->id > targetId)    
        return searchNode(node->left, targetId);

    else
        return searchNode(node->right, targetId);
}

Node* createNode(int id, const char* data)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->id = id;
    strcpy(newNode->data, data);
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Node* searchMinimumNode(Node* node)
// // 삭제대상 right기준으로 left == NULL일 때까지 left 따라가기
// {   
//     if (node == NULL)
//         return NULL;

//     else if (node->left == NULL)
//         return node;
//     else  
//         return searchMinimumNode(node->left);
// } 

Node* searchMaximumNode(Node* node)
// 삭제대상 left기준으로 right == NULL일 때까지 right 따라가기
{
    if (node == NULL)
        return NULL;
    else if (node->right == NULL)
        return node;
    else
        return searchMaximumNode(node->right);
}

Node* deleteNode(Node* searchingNode, Node* parent, int targetId)
{
    if (searchingNode == NULL)
        return NULL;

    if (searchingNode->id > targetId) // 삭제하려고 찾는 중인 노드 vs 삭제하려는 값   
        return deleteNode(searchingNode->left, searchingNode, targetId);

    else if (searchingNode->id < targetId) 
        return deleteNode(searchingNode->right, searchingNode, targetId);

    // --> 찾아나가는 과정 

    // 찾은 뒤 !! 삭제대상(자식 x, 왼쪽자식, 오른쪽 자식, 둘 다 있을 때) 4개 상황
    else //if (searchingNode->id == targetId)
    {
        Node* deletingNode = searchingNode;
        // 자식 노드가 모두 없을 때 
        if(deletingNode->left == NULL && deletingNode->right == NULL)
        {
            // 부모 모드에 NULL을 연결
            // Node* parent 로 부모의 정보 가지고 있음.
            if (parent->left == deletingNode) parent->left = NULL;
            else parent->right = NULL;   
            // --> 연결해제. 왼쪽에 있는지, 오른쪽에 있는지 확인하고 NULL 연결         

            return deletingNode;
            // 삭제 노드 반환. 
        }        
        // 자식 노드 중에서 왼쪽 노드만 있는 경우 --> 삭제 대상 아래 왼쪽 노드가 있음
        else if (deletingNode->left != NULL && deletingNode->right == NULL)
        {
            // 왼쪽 노드를 부모노드에 연결
            if (parent->left == deletingNode) parent->left = deletingNode->left;
            else parent->right = deletingNode->left;
            // --> 삭제대상이 부모 왼쪽 오른쪽 확인
            // 현재 위치(부모의 왼쪽 또는 오른쪽)를 deletingNode의 left에 연결

            return deletingNode;
        }
        // 자식 노드 중에서 오른쪽 노드만 있는 경우
        else if (deletingNode->left == NULL && deletingNode->right != NULL)
        {
            // 오른쪽 노드를 부모노드에 연결
            if (parent->left == deletingNode) parent->left = deletingNode->right;
            else parent->right = deletingNode->right;

            return deletingNode; 
        }
        // 자식 노드가 양쪽에 모두 있는 경우
        // --> 삭제노드의 오른쪽에서 가장 작은 값을 찾아 대체하기
        // else // (treeNode->left != NULL || treeNode->right != NULL)
        // {
        //     Node* minimumNode = searchMinimumNode(deletingNode->right);
        //     deleteNode(deletingNode, NULL, minimumNode->id);
        //     deletingNode->id =  minimumNode->id;
        //     strcpy(deletingNode->data, minimumNode->data);

        //     return minimumNode;  
            
        //     // 삭제대상 right의 Min의 id 찾아서 삭제대상id와 바꾸기(값복사) --> 장점은 연결을 다시 안해줘도 된다!!!
        //     // 실제 삭제하는 것은 삭제대상 right Min 
        //     // 지우는 과정은 deleteNode 재귀를 통해서... 
        // }
        
        
        // --> 삭제노드의 왼쪽에서 가장 큰 값을 찾아 대체하기 (과제)
        else
        {
            Node* maximumNode = searchMaximumNode(deletingNode->left);
            deleteNode(deletingNode, NULL, maximumNode->id);
            deletingNode->id = maximumNode->id;
            strcpy(deletingNode->data, maximumNode->data);   

            return maximumNode;
        }
        
    }     
}

void insertChildNode(Node* rootNode, Node* newNode)
{
    if (rootNode->id > newNode->id)
    {
        if(rootNode->left == NULL) 
        // 왼쪽에 들어가야 하니까 왼쪽 NULL체크
            rootNode->left = newNode;
        else
            insertChildNode(rootNode->left, newNode); 
            //왼쪽 NULL 아니면 왼쪽노드 기준으로 재귀해서 또 비교
            //루트노드와 비교해서 왼쪽에 위치한다는 것을 알았음. 근데 또 비교할 기준이 생겼기에, 그 기준을 유지.
    }
    else
    {
        if(rootNode->right == NULL)
        // 오른쪽에 들어가야 하니까 왼쪽 NULL체크
            rootNode->right = newNode;
        else
            insertChildNode(rootNode->right, newNode); 
            // 오른쪽 NULL아니면 오른쪽노드 기준으로 재귀하여 비교
    }
}

int main()
{
    Node* root = createNode(10, "a");
    insertChildNode(root, createNode(20, "b"));
    insertChildNode(root, createNode(5, "c"));
    insertChildNode(root, createNode(25, "d"));
    insertChildNode(root, createNode(18, "e"));
    insertChildNode(root, createNode(19, "f"));
    insertChildNode(root, createNode(1, "g"));
    insertChildNode(root, createNode(4, "h"));
    insertChildNode(root, createNode(33, "i"));

    printBinaryTree(root, 1, ROOT);

    Node* foundNode = searchNode(root, 18);
    printf("\nFound data [%s] at id %d\n", foundNode->data, foundNode->id);

    Node* deleteTargetNode = deleteNode(root, NULL, 20);
    if (deleteTargetNode != NULL)
        printf("\nFound deleting data [%s] at id %d\n", deleteTargetNode->data, deleteTargetNode->id);
    else
        printf("\nNot found\n");
    free(deleteTargetNode);

    printBinaryTree(root, 1, ROOT);

    return 0;
}