#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE    1
#define FALSE   0
#define UNDEFINED   -1
#define INF 2147483647


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

Edge* getEdge(Vertex* vertex, int index)
{
    Edge* currentEdge = vertex->adjList;
    if (currentEdge == NULL)
    {
        return NULL;
    }
    while(currentEdge->dest->index != index)
    {
        if (currentEdge->nextEdge == NULL)
        {
            // printf("No such edge\n");
            return NULL;
        }
        currentEdge = currentEdge->nextEdge;
    }

    return currentEdge;
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

void dijkstra(Graph* graph, int start)
{
    // 그래프가 가진 정점의 수만큼 dist, visited, prev 라는 동적 배열을 생성합니다
    int* dist = (int*)malloc(graph->vertexCount * sizeof(int)); // start 정점으로부터 각 정점까지의 거리를 담는 배열입니다
    int* visited = (int*)malloc(graph->vertexCount * sizeof(int)); // 각 정점에 대해 방문했는지 확인하는 배열입니다
    int* prev = (int*)malloc(graph->vertexCount * sizeof(int)); // start 정점으로부터 각 정점까지의 최단 경로상에서 이전 정점을 저장하는 배열입니다

    // i를 정점의 번호로 하여 각 정점에 대한 값을 초기화 합니다
    // 거리는 시작점을 제외하고는 모두 무한대로 설정합니다
    // 방문하지 않은 정점에 대해서는 0으로 처리합니다
    for (int i = 0; i < graph->vertexCount; i++)
    {
        dist[i] = INF;
        visited[i] = FALSE;
        prev[i] = UNDEFINED;
    }

    // 시작점에 대한 거리는 0으로 설정합니다
    dist[start] = 0;

    // 이 부분이 Dijkstra 알고리즘 구현부 입니다
    // 총 n제곱의 시간복잡도 입니다
    for (int i = 0; i < graph->vertexCount - 1; i++)
    {
        int min = INF;
        int u = UNDEFINED;

        // 방문하지 않은 정점 중에서 시작점에 대한 거리가 가장 작은 정점을 선택합니다
        // 이 값은 최초에 시작점 그 자체가 됩니다 (위의 dist[start] = 0 때문입니다, 그 외에는 모두 INF로 초기화 됩니다)
        // 각 정점에 대한 거리는 점점 업데이트될 것입니다
        for (int j = 0; j < graph->vertexCount; j++)
        {
            if (visited[j] == FALSE && dist[j] <= min)
            {
                min = dist[j];
                u = j;
            }
        }

        if (u == UNDEFINED) break;

        // 방문한 정점은 visited 플래그를 TRUE로 설정하여 다음에는 방문하지 않도록 합니다
        // 위의 반복문에서 다시 방문하지 않도록 하는 것입니다
        visited[u] = TRUE;

        for (int v = 0; v < graph->vertexCount; v++)
        {
            Vertex* currentVertex = getVertex(graph, u);
            Edge* currentEdge = getEdge(currentVertex, v);
            if (currentEdge == NULL) continue;

            // 위의 루프에서 정해진 정점 인덱스를 고정하고(현재 선택된 정점) 이를 기준으로 인접행렬상의 모든 정점 v를 순회하며 weight를 확인합니다
            int weight = currentEdge->weight;

            // dist[u] + weight는 u정점을 거쳐서 v정점으로 가는 거리가 됩니다
            // 이 값이 기존 dist[v]보다 작으면 이를 dist[v]로 업데이트 하고 v의 이전 정점을 u로 설정합니다
            // 이 과정을 모든 정점에 대해 수행하여 v정점으로 가는 최단 경로상에서 목적지 v정점의 이전 정점 정보를 갖게 됩니다
            // 그리고 prev 배열을 추적하면 각각의 정점까지의 최단경로를 역추적할 수 있습니다
            if (visited[v] == FALSE && weight > 0 && dist[u] + weight < dist[v])
            {
                dist[v] = dist[u] + weight;
                prev[v] = u;
            }
        }
    }

    // start정점으로부터 각 정점 i까지의 최단경로를 출력합니다
    // prev배열을 i부터 시작하여 역추적하면 됩니다
    for (int i = 0; i < graph->vertexCount; i++)
    {        
        if (dist[i] == INF)
        {
            printf("경로없음\n");
            continue;
        }
        printf("%d(%s)까지 최단경로 (총 %d역): ", i, getVertex(graph, i)->value, dist[i]);
        int path[graph->vertexCount];
        int len = 0;

        // dist[i]가 INF가 아니라면 이렇게 역추적했을 때 v는 start까지 오게 됩니다
        // path배열에는 목적지부터 역순으로 담깁니다
        for (int v = i; v != -1; v = prev[v])
        {
            path[len++] = v;
        }

        // path배열을 역순으로 출력하면 start부터 목적지까지의 경로가 됩니다
        for (int j = len - 1; j >= 0; j--)
        {
            printf("%d(%s)", path[j],  getVertex(graph, path[j])->value);
            if (j > 0) printf(" -> ");
        }
        printf("\n");
    }

    free(dist);
    free(visited);
    free(prev);
}

int main(int argc, char* argv[])
{
    Graph* graph = createGraph();

    Vertex* vertex0 = createVertex(0, "수서");
    Vertex* vertex1 = createVertex(1, "가천대");
    Vertex* vertex2 = createVertex(2, "이매");
    Vertex* vertex3 = createVertex(3, "성남");
    Vertex* vertex4 = createVertex(4, "판교");

    addVertex(graph, vertex0);
    addVertex(graph, vertex1);
    addVertex(graph, vertex2);
    addVertex(graph, vertex3);
    addVertex(graph, vertex4);

    printf("%s\n", getVertex(graph, 0)->value);
    printf("%s\n", getVertex(graph, 1)->value);
    printf("%s\n", getVertex(graph, 2)->value);
    printf("%s\n", getVertex(graph, 3)->value);
    printf("%s\n", getVertex(graph, 4)->value);

    addEdge(vertex1, createEdge(vertex1, vertex0, 2)); // 가천대 -> 수서 = 2역
    addEdge(vertex1, createEdge(vertex1, vertex2, 4)); // 가천대 -> 이매 = 4역
    addEdge(vertex2, createEdge(vertex2, vertex3, 1)); // 이매 -> 성남 = 1역
    addEdge(vertex3, createEdge(vertex3, vertex4, 1)); // 성남 -> 판교 = 1역
    addEdge(vertex0, createEdge(vertex0, vertex3, 1)); // 수서 -> 성남 = 1역
    addEdge(vertex1, createEdge(vertex1, vertex3, 2)); // 가천대 -> 성남 = 2역 가중치


    printGraph(graph);

    dijkstra(graph, 1);

    return 0;
}