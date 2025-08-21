#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE    1
#define FALSE   0


typedef struct Vertex
{
    char* value;
    int index;
    int visited;

    struct Vertex* nextVertex;
    struct Edge* adjList;

}Vertex;

typedef struct Graph
{
    struct Vertex* vertices;
    int vertexCount;

}Graph;

typedef struct Stack
{
    struct Vertex vertex;
    struct Stack* next;
    struct Stack* prev;
}Stack;


typedef struct Edge
{
    int weight;
    struct Edge* nextEdge;

    struct Vertex* origin;
    struct Vertex* dest;   

}Edge;

Graph* createGraph()
{
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->vertexCount = 0;
    graph->vertices = NULL;

    return graph;
}

void addEdge(Vertex* vertex, Edge* edge)
{
    if (vertex->adjList == NULL)
    {
        vertex->adjList = edge;
    }
    else
    {
        Edge* currentEdge = vertex->adjList;
        while(currentEdge->nextEdge != NULL) currentEdge = currentEdge->nextEdge;
        currentEdge->nextEdge = edge;
    }
}

void addVertex(Graph* graph, Vertex* vertex)
{
    graph->vertexCount++;
    if (graph->vertices == NULL)
    {
        graph->vertices = vertex;
    }
    else
    {
        Vertex* currentVertex = graph->vertices;
        while(currentVertex->nextVertex != NULL) currentVertex = currentVertex->nextVertex;
        currentVertex->nextVertex = vertex;
    }
}


Vertex* createVertex(int index, char* value)
{
    Vertex* vertex = (Vertex*)malloc(sizeof(Vertex));
    vertex->index = index;
    vertex->visited = FALSE;
    vertex->value = (char*)malloc(strlen(value)*sizeof(char));
    strcpy(vertex->value, value);
    vertex->nextVertex = NULL;
    vertex->adjList = NULL;

    return vertex;
}

Vertex* getVertex(Graph* graph, int index)
{
    Vertex* currentVertex = graph->vertices;
    while(currentVertex->index != index)
    {
        if (currentVertex->nextVertex == NULL)
        {
            printf("No such vertex\n");
            return NULL;
        }
        currentVertex = currentVertex->nextVertex;
    }

    return currentVertex;
}

Edge* createEdge(Vertex* origin, Vertex* dest, int weight)
{
    Edge* edge = (Edge*)malloc(sizeof(Edge));

    edge->weight = weight;
    edge->origin = origin;
    edge->dest = dest;
    edge->nextEdge = NULL;    

    return edge;
}

void printStack(Stack* top)
{
    Stack* currentNode = top->next; // bottom
    Stack* starting = currentNode;
    while(1)
    {
        printf("%s -> ", currentNode->vertex.value);
        currentNode = currentNode->next;

        if(currentNode == starting) break;
    }
}

void push(Stack** top, Vertex* vertex)
{
    if(*top == NULL)
    {
        Stack* newNode = (Stack*)malloc(sizeof(Stack));
        newNode->vertex = *vertex;
        newNode->next = newNode;
        newNode->prev = newNode;

        *top = newNode;
    }
    else
    {
        Stack* bottom = (*top)->next;
        Stack* newNode = (Stack*)malloc(sizeof(Stack));
        newNode->vertex = *vertex;
        
        newNode->prev = (*top);
        (*top)->next = newNode;
        
        newNode->next = bottom;
        bottom->prev = newNode;        

        *top = newNode;        
    }
}

Vertex pop(Stack** top)
{
    Stack* deleteNodeP = *top;
    Stack* bottom = (*top)->next;

    Vertex returnVertex = deleteNodeP->vertex;

    if(deleteNodeP->prev == deleteNodeP)
    {
        *top = NULL;         
    }
    else
    {
        *top = deleteNodeP->prev;

        (*top)->next = bottom;
        bottom->prev = *top;           
    }

    free(deleteNodeP);

    return returnVertex;
}

void printGraph(Graph* graph)
{
    Vertex* currentVertex = graph->vertices;

    while(currentVertex != NULL)
    {
        printf("[%d(%s)]\n", currentVertex->index, currentVertex->value);
        Edge* currentEdge = currentVertex->adjList;
        while(currentEdge != NULL)
        {
            // printf("%d->%d (weight: %d)\n", currentEdge->origin->index, currentEdge->dest->index, currentEdge->weight);
            printf("%d(%s)->%d(%s) (weight: %d)\n", 
                currentEdge->origin->index, currentEdge->origin->value, 
                currentEdge->dest->index, currentEdge->dest->value, currentEdge->weight);

            currentEdge = currentEdge->nextEdge;
        }
        currentVertex = currentVertex->nextVertex;
        printf("\n");
    }
}

void detect_cycle_w_dfs(Vertex* vertex, Vertex* starting, Stack** stack)
{
    push(stack, vertex);
    vertex->visited = TRUE;
    printf("현재 정점 %d(%s): 방문완료\n", vertex->index, vertex->value);

    Edge* currentEdge = vertex->adjList;

    while (currentEdge!= NULL)
    {
        if(currentEdge->dest != NULL && currentEdge->dest->visited == FALSE)
        {
            detect_cycle_w_dfs(currentEdge->dest, starting, stack);
            if(stack != NULL) pop(stack);
        }        

        if (currentEdge->dest != NULL && currentEdge->dest == starting)
        {
            
            printf("[순환경로가 탐지 되었습니다]\n");
            printStack(*stack);
            printf("%s\n\n", starting->value); 
            //starting 출력하거나, current의 next를 출력하거나. 
        }

        currentEdge = currentEdge->nextEdge;
    }
    
}

int main(int argc, char* argv[])
{
    Graph* graph = createGraph();
    Stack* stack = NULL;

    Vertex* vertex0 = createVertex(0, "수서");
    Vertex* vertex1 = createVertex(1, "복정");
    Vertex* vertex2 = createVertex(2, "가천대");
    Vertex* vertex3 = createVertex(3, "모란");
    Vertex* vertex4 = createVertex(4, "수내");
    Vertex* vertex5 = createVertex(5, "이매");
    Vertex* vertex6 = createVertex(6, "성남");
    Vertex* vertex7 = createVertex(7, "판교");
    Vertex* vertex8 = createVertex(8, "도곡");
    Vertex* vertex9 = createVertex(9, "양재");

    addVertex(graph, vertex0);
    addVertex(graph, vertex1);
    addVertex(graph, vertex2);
    addVertex(graph, vertex3);
    addVertex(graph, vertex4);
    addVertex(graph, vertex5);
    addVertex(graph, vertex6);
    addVertex(graph, vertex7);
    addVertex(graph, vertex8);
    addVertex(graph, vertex9);

    printf("%s\n", getVertex(graph, 7)->value);
    printf("%s\n", getVertex(graph, 3)->value);
    printf("%s\n", getVertex(graph, 6)->value);
    printf("%s\n", getVertex(graph, 5)->value);
    printf("%s\n", getVertex(graph, 1)->value);
    printf("%s\n", getVertex(graph, 3)->value);
    printf("%s\n", getVertex(graph, 2)->value);
    printf("%s\n", getVertex(graph, 8)->value);
    printf("%s\n", getVertex(graph, 9)->value);

    addEdge(vertex2, createEdge(vertex2, vertex0, 2)); //가천대 -> 수서 = 2역
    addEdge(vertex1, createEdge(vertex1, vertex3, 3)); // 복정 -> 모란 = 3역
    addEdge(vertex6, createEdge(vertex6, vertex5, 1)); // 성남 -> 이매 = 1역
    addEdge(vertex1, createEdge(vertex1, vertex0, 1)); // 복정 -> 수서 = 1역
    addEdge(vertex6, createEdge(vertex6, vertex7, 1)); // 성남 -> 판교 = 1역
    addEdge(vertex2, createEdge(vertex2, vertex1, 1)); // 가천대 -> 복정 = 1역
    addEdge(vertex2, createEdge(vertex2, vertex4, 6)); // 가천대 -> 수내 = 6역
    addEdge(vertex2, createEdge(vertex2, vertex5, 4)); // 가천대 -> 이매 = 4역 
    addEdge(vertex5, createEdge(vertex5, vertex6, 1)); // 이매 -> 성남 = 1역
    addEdge(vertex5, createEdge(vertex5, vertex7, 2)); // 이매 -> 판교 = 2역
    addEdge(vertex0, createEdge(vertex0, vertex8, 4)); // 수서 -> 도곡 = 4역
    addEdge(vertex0, createEdge(vertex0, vertex9, 7)); // 수서 -> 양재 = 7역
    addEdge(vertex0, createEdge(vertex0, vertex6, 1)); // 수서 -> 성남 = 1역
    addEdge(vertex3, createEdge(vertex3, vertex5, 2)); // 모란 -> 이매 = 2역

    addEdge(vertex5, createEdge(vertex5, vertex2, 4)); // 이매 -> 가천대 = 4역
    addEdge(vertex6, createEdge(vertex6, vertex0, 1)); // 성남 -> 수서 = 1역
    addEdge(vertex0, createEdge(vertex0, vertex2, 2)); // 수서 -> 가천대 = 2역

    printGraph(graph);

    detect_cycle_w_dfs(vertex2, vertex2, &stack);

    free(graph);
    if(stack != NULL) free(stack);

    return 0;
}