#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE    1
#define FALSE   0
#define UNDEFINED   -1
#define GRAPH_SIZE 5
#define LABEL_LENGTH 10
#define INF 2147483647

typedef struct Graph
{
    int size;
    int** adj_matrix;
    char** labels;

}Graph;

void dijkstra(Graph* graph, int start)
{

    // 그래프가 가진 정점의 수만큼 dist, visited, prev 라는 동적 배열을 생성합니다
    int* dist = (int*)malloc(graph->size * sizeof(int)); // start 정점으로부터 각 정점까지의 거리를 담는 배열입니다
    int* visited = (int*)malloc(graph->size * sizeof(int)); // 각 정점에 대해 방문했는지 확인하는 배열입니다
    int* prev = (int*)malloc(graph->size * sizeof(int)); // start 정점으로부터 각 정점까지의 최단 경로상에서 이전 정점을 저장하는 배열입니다

    // i를 정점의 번호로 하여 각 정점에 대한 값을 초기화 합니다
    // 거리는 시작점을 제외하고는 모두 무한대로 설정합니다
    // 방문하지 않은 정점에 대해서는 0으로 처리합니다
    for (int i = 0; i < graph->size; i++)
    {
        dist[i] = INF;
        visited[i] = FALSE;
        prev[i] = UNDEFINED;
    }

    // 시작점에 대한 거리는 0으로 설정합니다
    dist[start] = 0;

    // 이 부분이 Dijkstra 알고리즘 구현부 입니다
    // 총 n제곱의 시간복잡도 입니다
    for (int i = 0; i < graph->size - 1; i++)
    {
        int min = INF;
        int u = UNDEFINED;

        // 방문하지 않은 정점 중에서 시작점에 대한 거리가 가장 작은 정점을 선택합니다
        // 이 값은 최초에 시작점 그 자체가 됩니다 (위의 dist[start] = 0 때문입니다, 그 외에는 모두 INF로 초기화 됩니다)
        // 각 정점에 대한 거리는 점점 업데이트될 것입니다
        for (int j = 0; j < graph->size; j++)
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
        
        for (int v = 0; v < graph->size; v++)
        {
            // 위의 루프에서 정해진 정점 인덱스를 고정하고(현재 선택된 정점) 이를 기준으로 인접행렬상의 모든 정점 v를 순회하며 weight를 확인합니다
            int weight = graph->adj_matrix[u][v];

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
    for (int i = 0; i < graph->size; i++)
    {
        if (dist[i] == INF)
        {
            printf("경로없음\n");
            continue;
        }
        printf("%d(%s)까지 최단경로 (총 %d역): ", i, graph->labels[i], dist[i]);
        int path[GRAPH_SIZE];
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
            printf("%d(%s)", path[j], graph->labels[path[j]]);
            if (j > 0) printf(" -> ");
        }
        printf("\n");
    }

    free(dist);
    free(visited);
    free(prev);
}


Graph* createGraph(int size)
{
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->size = size;
    graph->adj_matrix = (int**)malloc(size*sizeof(int*));
    graph->labels = (char**)malloc(size*sizeof(char*));
    for(int i=0; i<size; i++)
    {
        graph->adj_matrix[i] = (int*)malloc(size*sizeof(int));
        memset(graph->adj_matrix[i], 0x0, size*sizeof(int));

        graph->labels[i] = (char*)malloc(size*sizeof(char));
        memset(graph->labels[i], 0x0, size*sizeof(int));
    }

    return graph;
}

void printGraph(Graph* graph)
{
    for(int i=0; i<graph->size; i++)
    {
        for(int j=0; j<graph->size; j++)
        {
            printf("%d ",graph->adj_matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void deleteGraph(Graph* graph)
{
    for(int i=0; i<graph->size; i++)
    {
        free(graph->adj_matrix[i]);
    }
}

void updatelabel(Graph* graph, int index, char* label)
{
    strcpy(graph->labels[index], label);
}

void updateEdge(Graph* graph, int origin, int destination, int value)
{
    graph->adj_matrix[origin][destination] = value;
}

int main(int argc, char* argv[])
{
    Graph* graph = createGraph(GRAPH_SIZE);

    updatelabel(graph, 0, "수서");
    updatelabel(graph, 1, "가천대");
    updatelabel(graph, 2, "이매");
    updatelabel(graph, 3, "성남");
    updatelabel(graph, 4, "판교");

    updateEdge(graph, 1, 0, 2); // 가천대 -> 수서 = 2역
    updateEdge(graph, 1, 2, 4); // 가천대 -> 이매 = 4역
    updateEdge(graph, 2, 3, 1); // 이매 -> 성남 = 1역
    updateEdge(graph, 3, 4, 1); // 성남 -> 판교 = 1역
    updateEdge(graph, 0, 3, 1); // 수서 -> 성남 = 1역
    updateEdge(graph, 1, 3, 2); // 가천대 -> 성남 = 2역 가중치

    printGraph(graph);

    dijkstra(graph, 1);

    deleteGraph(graph);
    return 0;
}