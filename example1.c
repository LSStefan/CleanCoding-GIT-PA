/*Determinati daca exista sau nu drum direct intre doua restaurante dintr-o retea de tip graf*/

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

struct Node 
{
    int data;
    struct Node *next;
};
/// pentru simplitate, folosim int uri pt a numi restaurantel/locatiile
/// ex: 1 - restaurantul 1 si tot asa


typedef struct
{
    int v;
    int *vis;
    struct Node **alst;
} GPH;

typedef struct
{
    int t;
    int scap;
    int *arr;
} STK;

struct Node *create_node(int v)
{
    struct Node *nn = malloc(sizeof(struct Node));
    nn->data = v;
    nn->next = NULL;
    return nn;
}

void add_edge(GPH *g, int src, int dest)
{
    struct Node *nn = create_node(dest);
    nn->next = g->alst[src];
    g->alst[src] = nn;
    nn = create_node(src);
    nn->next = g->alst[dest];
    g->alst[dest] = nn;
}

GPH *create_g(int v)
{
    int i;
    GPH *g = malloc(sizeof(GPH));
    g->v = v;
    g->alst = malloc(sizeof(struct Node *));
    g->vis = malloc(sizeof(int) * v);

    for (int i = 0; i < v; i++)
    {
        g->alst[i] = NULL;
        g->vis[i] = 0;
    }
    return g;
}

STK *create_s(int scap)
{
    STK *s = malloc(sizeof(STK));
    s->arr = malloc(scap * sizeof(int));
    s->t = -1;
    s->scap = scap;

    return s;
}

void push(int pshd, STK *s)
{
    s->t = s->t + 1;
    s->arr[s->t] = pshd;
}

void DFS(GPH *g, STK *s, int v_nr)
{
    struct Node *adj_list = g->alst[v_nr];
    struct Node *aux = adj_list;
    g->vis[v_nr] = 1;
    printf("%d ", v_nr);
    push(v_nr, s);
    while (aux != NULL)
    {
        int con_ver = aux->data;
        if (g->vis[con_ver] == 0)
            DFS(g, s, con_ver);
        aux = aux->next;
    }
}

void insert_edges(GPH *g, int edg_nr, int nrv)
{
    int src, dest, i;
    printf("adauga %d munchii (de la 1 la %d)\n", edg_nr, nrv);
    for (i = 0; i < edg_nr; i++)
    {
        scanf("%d%d", &src, &dest);
        add_edge(g, src, dest);
    }
}

void wipe(GPH *g, int nrv)
{
    for (int i = 0; i < nrv; i++)
    {
        g->vis[i] = 0;
    }
} 


int canbe(GPH *g, int src, int dest)
{
    struct Node *adj_list = g->alst[src];
    struct Node *aux = adj_list;
    while (aux != NULL)
    {
        if (aux->data == dest)
            return 1;
        aux = aux->next;
    }
    return 0;
}

int main()
{
    int nrv;
    int edg_nr;
    int src, dest;
    int i;
    int vortex_1;
    int virtex_2;
    int ans;

    printf("cate noduri are girafa?");
    scanf("%d", &nrv);

    printf("cate muchii are giraful?");
    scanf("%d", &edg_nr);

    GPH *g = create_g(nrv);

    STK *s1 = create_s(2 * nrv);
    STK *s2 = create_s(2 * nrv);

    insert_edges(g, edg_nr, nrv);

    int restaurant1, restaurant2;
    printf("Introduceti doua restaurante pentru a verifica daca exista un drum direct intre ele: ");
    scanf("%d%d", &restaurant1, &restaurant2);

    if (canbe(g, restaurant1, restaurant2))
        printf("Exista un drum direct intre restaurantul %d si restaurantul %d\n", restaurant1, restaurant2);
    else
        printf("Nu exista un drum direct intre restaurantul %d si restaurantul %d\n", restaurant1, restaurant2);

    return 0;
}

