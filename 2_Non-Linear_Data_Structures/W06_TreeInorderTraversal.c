#include <stdio.h>
#include <stdlib.h>

#define LEFT 0
#define RIGHT 1
#define ROOT -1

typedef struct Node {
    struct Node* left; 
    struct Node* right; 
    int data;    
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

    printf("%d\n", node->data);

    if (node->left != NULL)    
        printBinaryTree(node->left, depth+1, LEFT); // direction을 여기서 준다. 
        // 다음 재귀하여 tap 하고 (depth=2) Left child 출력
        // depth = 2 

    if (node->right != NULL)
        printBinaryTree(node->right, depth+1, RIGHT);
}

void printNodePrefix(Node* node, int depth)
{    
    if (node == NULL) return;   
    
    printf("%d ", node->data);

    if (node->left != NULL)    
        printNodePrefix(node->left, depth+1);

    if (node->right != NULL)
        printNodePrefix(node->right, depth+1);
}

// 중위순회 우측부터 출력 
void printNodeInfix(Node* node, int depth)
{    
    if (node == NULL) return;    

    if (node->right != NULL)    
        printNodeInfix(node->right, depth+1);

    printf("%d ", node->data);

    if (node->left != NULL)
        printNodeInfix(node->left, depth+1);
}

void printNodePostfix(Node* node, int depth)
{    
    if (node == NULL) return;   

    if (node->left != NULL)    
        printNodePostfix(node->left, depth+1);

    if (node->right != NULL)
        printNodePostfix(node->right, depth+1);

    printf("%d ", node->data);
}

Node* createNode(int data)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void deleteNode(Node* node)
{
    free(node);
}

Node* insertChildNode(Node* node, int data, int direction)
{

    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;

    if (direction == LEFT && node -> left == NULL)
        node -> left = newNode;
    else if (direction == RIGHT && node -> right == NULL)
        node -> right = newNode;
    else
        printf("Unexpected behavior");

    return newNode; 
}

int main()
{
    Node* root = createNode(10);
        Node* insertedNode1 = insertChildNode(root, 20, LEFT);
            Node* insertedNode4 = insertChildNode(insertedNode1, 30, LEFT);
                Node* insertedNode7 = insertChildNode(insertedNode4, 40, LEFT);
                Node* insertedNode9 = insertChildNode(insertedNode4, 41, RIGHT);
            Node* insertedNode5 = insertChildNode(insertedNode1, 31, RIGHT);
                Node* insertedNode10 = insertChildNode(insertedNode5, 42, LEFT);
                Node* insertedNode11 = insertChildNode(insertedNode5, 43, RIGHT);
            
        Node* insertedNode2 = insertChildNode(root, 21, RIGHT);
            Node* insertedNode3 = insertChildNode(insertedNode2, 32, LEFT);
                Node* insertedNode12 = insertChildNode(insertedNode3, 44, LEFT);
                Node* insertedNode13 = insertChildNode(insertedNode3, 45, RIGHT);
            Node* insertedNode6 = insertChildNode(insertedNode2, 33, RIGHT);
                Node* insertedNode14 = insertChildNode(insertedNode6, 46, LEFT);
                Node* insertedNode15 = insertChildNode(insertedNode6, 47, RIGHT);
    
    
    printBinaryTree(root, 1, ROOT);
    printf("\n================== Prefix ====================\n");
    printNodePrefix(root, 1);
    printf("\n================== Infix =====================\n");
    printNodeInfix(root, 1);
    printf("\n================== Postfix ===================\n");
    printNodePostfix(root, 1);
    // printf("\n================== RightInfix ==============================\n");
    // printNodeRightInfix(root, 1);
    printf("\n==============================================\n");

    //printNodeWithLevel(root, 1, 3);

    return 0;
}