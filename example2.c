/*parcurgerge  graf cu DFS/BFS*/

// Imi cer scuze in avans

#include <stdlib.h>

#include <stdio.h>

struct Node
{
    int data;
    struct Node *next;
};

typedef struct Graph
{
    int vertices;
    int *visited;
    struct Node **adjacency_lists;
} GPH;

/// utils
struct Node *create_node(int v)
{
    struct Node *new_node = malloc(sizeof(struct Node));
    new_node->data = v;
    new_node->next = NULL;
    return new_node;
}

GPH *create_graph(int vertices)
{
    int i;
    GPH *graph = malloc(sizeof(GPH));
    graph->vertices = vertices;
    graph->adjacency_lists = malloc(vertices * sizeof(struct Node *));

    graph->visited = malloc(sizeof(int) * vertices);
    for (int i = 0; i < vertices; i++)
    {
        graph->adjacency_lists[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}
void add_edge(GPH *graph, int src, int dest)
{
    struct Node *new_node = create_node(dest);

    new_node->next = graph->adjacency_lists[src];
    graph->adjacency_lists[src] = new_node;

    new_node = create_node(src);

    new_node->next = graph->adjacency_lists[dest];
    graph->adjacency_lists[dest] = new_node;
}

int *insedg(int nr_of_vertices, int nr_of_edges, GPH *graph)
{
    int src, dest, i;
    printf("adauga %d muchii (de la 1 la %d)\n", nr_of_edges, nr_of_vertices);
    for (i = 0; i < nr_of_edges; i++)
    {
        scanf("%d%d", &src, &dest);
        add_edge(graph, src, dest);
    }
}
/// bfs utils
int is_empty(struct Node *queue)
{
    return queue == NULL;
}

void enqueue(struct Node **queue, int data)
{
    struct Node *new_node = create_node(data);

    if (is_empty(*queue))
        *queue = new_node;
    else
    {
        struct Node *temp = *queue;
        while (temp->next)
        {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

int dequeue(struct Node **queue)
{
    int data = (*queue)->data;
    struct Node *temp = *queue;
    *queue = (*queue)->next;
    free(temp);
    return data;
}

void print_graph(GPH *graph)
{
    int i;
    for (i = 0; i < graph->vertices; i += 1)
    {
        struct Node *temp = graph->adjacency_lists[i];

        while (temp)
        {
            printf("%d ", temp->data);
            temp = temp->next;
        }
        printf("\n");
    }
}

void print_queue(struct Node *queue)
{
    while (queue != NULL)
    {
        printf("%d ", queue->data);
        queue = queue->next;
    }
}

void wipe_visited_list(GPH *graph, int nr_of_vertices)
{
    for (int i = 0; i < nr_of_vertices; i++)
    {
        graph->visited[i] = 0;
    }
}

void DFS(GPH *graph, int vertex_nr)
{
    graph->visited[vertex_nr] = 1;
    printf("%d->", vertex_nr);

    struct Node *temp = graph->adjacency_lists[vertex_nr];

    while (temp != NULL)
    {
        int connected_vertex = temp->data;

        if (graph->visited[connected_vertex] == 0)
        {
            DFS(graph, connected_vertex);
        }
        temp = temp->next;
    }
}

void BFS(GPH *graph, int start)
{
    struct Node *queue = NULL;

    graph->visited[start] = 1;
    enqueue(&queue, start);

    while (!is_empty(queue))
    {
        int current = dequeue(&queue);
        printf("%d ", current);

        struct Node *temp = graph->adjacency_lists[current];

        while (temp)
        {
            int adj_vertex = temp->data;

            if (graph->visited[adj_vertex] == 0)
            {
                graph->visited[adj_vertex] = 1;
                enqueue(&queue, adj_vertex);
            }
            temp = temp->next;
        }
    }
}

    int main()
    {

        int nr_of_vertices;
        int nr_of_edges;
        int src, dest;

        int i;
        int starting_vertex;
        int *adj_matrix;
        printf("cate noduri are graful?");
        scanf("%d", &nr_of_vertices);
        printf("cate muchii are graful?");
        scanf("%d", &nr_of_edges);
        GPH *graph = create_graph(nr_of_vertices);
        insedg(nr_of_vertices, nr_of_edges, graph);
        printf("de unde plecam in DFS?");
        scanf("%d", &starting_vertex);
        printf("parcurgere cu DFS:");
        DFS(graph, starting_vertex);
        wipe_visited_list(graph, nr_of_vertices);
    printf("\n");
    printf("de unde plecam in BFS?");
    scanf("%d", &starting_vertex);
    printf("parcurgere cu BFS:");
    BFS(graph, starting_vertex);
    return 0;
}
