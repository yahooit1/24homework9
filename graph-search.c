#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 10 // 최대 정점 수 정의

typedef struct Node {
    int vertex; // 연결된 정점 번호
    struct Node* next; // 다음 노드를 가리키는 포인터
} Node;

typedef struct Graph {
    Node* adjLists[MAX_VERTICES]; // 인접 리스트 배열
    int visited[MAX_VERTICES]; // 방문 배열
    int vertexCount; // 현재 정점 수
} Graph;

Graph* createGraph();
void initializeGraph(Graph* graph);
void addVertex(Graph* graph, int vertex);
void addEdge(Graph* graph, int src, int dest);
void printGraph(Graph* graph);
void DFS(Graph* graph, int vertex);
void BFS(Graph* graph, int startVertex);
void resetVisited(Graph* graph);

Graph* createGraph() {
    Graph* graph = (Graph*)malloc(sizeof(Graph)); // 그래프 메모리 할당
    for (int i = 0; i < MAX_VERTICES; i++) {
        graph->adjLists[i] = NULL; // 인접 리스트 초기화
        graph->visited[i] = 0; // 방문 배열 초기화
    }
    graph->vertexCount = 0; // 현재 정점 수 초기화
    return graph; // 그래프 반환
}

void initializeGraph(Graph* graph) {
    for (int i = 0; i < MAX_VERTICES; i++) {
        graph->adjLists[i] = NULL; // 모든 인접 리스트 초기화
        graph->visited[i] = 0; // 모든 방문 배열 초기화
    }
    graph->vertexCount = 0; // 현재 정점 수 초기화
    printf("Graph initialized.\n");
}

void addVertex(Graph* graph, int vertex) {
    if (graph->vertexCount >= MAX_VERTICES) {
        printf("Maximum vertices reached.\n");
        return;
    }
    if (graph->adjLists[vertex] == NULL) {
        graph->adjLists[vertex] = (Node*)malloc(sizeof(Node));
        graph->adjLists[vertex]->vertex = vertex;
        graph->adjLists[vertex]->next = NULL;
        graph->vertexCount++;
        printf("Vertex %d added.\n", vertex);
    } else {
        printf("Vertex %d already exists.\n", vertex);
    }
}

void addEdge(Graph* graph, int src, int dest) {
    if (src >= MAX_VERTICES || dest >= MAX_VERTICES) {
        printf("Vertex number out of bounds.\n");
        return;
    }
    if (graph->adjLists[src] == NULL || graph->adjLists[dest] == NULL) {
        printf("One or both vertices do not exist.\n");
        return;
    }

    // src에서 dest로 간선 추가
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = dest;
    newNode->next = graph->adjLists[src]->next;
    graph->adjLists[src]->next = newNode;

    // dest에서 src로 간선 추가 (무방향 그래프의 경우)
    newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = src;
    newNode->next = graph->adjLists[dest]->next;
    graph->adjLists[dest]->next = newNode;

    printf("Edge added between %d and %d.\n", src, dest);
}

void printGraph(Graph* graph) {
    for (int v = 0; v < MAX_VERTICES; v++) {
        if (graph->adjLists[v] != NULL) {
            Node* temp = graph->adjLists[v];
            printf("\n Vertex %d\n: ", v); // 현재 정점 번호 출력
            temp = temp->next; // 첫 번째 노드는 스킵
            while (temp) {
                printf("%d -> ", temp->vertex); // 연결된 정점 번호 출력
                temp = temp->next;
            }
            printf("NULL\n");
        }
    }
}

void DFS(Graph* graph, int vertex) {
    if (vertex >= MAX_VERTICES) {
        printf("Vertex number out of bounds.\n");
        return;
    }

    Node* adjList = graph->adjLists[vertex];
    Node* temp = adjList;
    
    graph->visited[vertex] = 1; // 현재 정점을 방문으로 표시
    printf("Visited %d\n", vertex); // 방문한 정점 출력
    
    while (temp != NULL) {
        int connectedVertex = temp->vertex;
        
        if (graph->visited[connectedVertex] == 0) {
            DFS(graph, connectedVertex); // 재귀적으로 DFS 호출
        }
        temp = temp->next;
    }
}

void BFS(Graph* graph, int startVertex) {
    if (startVertex >= MAX_VERTICES) {
        printf("Vertex number out of bounds.\n");
        return;
    }

    // 큐 초기화
    int queue[MAX_VERTICES];
    int front = -1;
    int rear = -1;
    
    graph->visited[startVertex] = 1;
    queue[++rear] = startVertex;
    
    while (front != rear) {
        int currentVertex = queue[++front];
        printf("Visited %d\n", currentVertex); // 방문한 정점 출력
        
        Node* temp = graph->adjLists[currentVertex];
        
        while (temp) {
            int adjVertex = temp->vertex;
            
            if (graph->visited[adjVertex] == 0) {
                queue[++rear] = adjVertex;
                graph->visited[adjVertex] = 1;
            }
            temp = temp->next;
        }
    }
}

void resetVisited(Graph* graph) {
    for (int i = 0; i < MAX_VERTICES; i++) {
        graph->visited[i] = 0; // 모든 방문 배열 초기화
    }
}

int main() {
    Graph* graph = createGraph(); // 그래프 생성
    char command;
    int vertex, vertex1, vertex2;

    printf("----- [Your Name] [Your Student ID] -----\n");

    while (1) {
        printf("\n----------------------------------------------------------------\n");
        printf("Graph Searches\n");
        printf("----------------------------------------------------------------\n");
        printf("Initialize Graph = z\n");
        printf("Insert Vertex = v\n");
        printf("Insert Edge = e\n");
        printf("Depth First Search = d\n");
        printf("Breadth First Search = b\n");
        printf("Print Graph = p\n");
        printf("Quit = q\n");
        printf("----------------------------------------------------------------\n");
        printf("Enter command: ");
        scanf(" %c", &command);

        switch (command) {
            case 'z':
                initializeGraph(graph);
                break;
            case 'v':
                printf("Enter vertex to add (0-9): ");
                scanf("%d", &vertex);
                addVertex(graph, vertex);
                break;
            case 'e':
                printf("Enter two vertices to connect with an edge (0-9): ");
                scanf("%d %d", &vertex1, &vertex2);
                addEdge(graph, vertex1, vertex2);
                break;
            case 'd':
                printf("Enter starting vertex for DFS (0-9): ");
                scanf("%d", &vertex1);
                resetVisited(graph);
                DFS(graph, vertex1);
                break;
            case 'b':
                printf("Enter starting vertex for BFS (0-9): ");
                scanf("%d", &vertex1);
                resetVisited(graph);
                BFS(graph, vertex1);
                break;
            case 'p':
                printGraph(graph);
                break;
            case 'q':
                printf("Quitting program.\n");
                return 0;
            default:
                printf("Invalid command. Please try again.\n");
        }
    }

    return 0;
}
