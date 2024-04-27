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

typedef struct s
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


void canbe(GPH *g, int nrv, STK *s1, STK *s2) // 0 sau 1 daca poate fi sau nu ajuns
{
    int *canbe = calloc(nrv, sizeof(int));
    for (int i = 0; i < nrv; i++) // aici i tine loc de numar adica de restaurant{for (int j = 0; j < 5; j++)
    {
        DFS(g, s1, i);
        wipe(g, nrv);
        int j = 0;
        int ans = 0;
        DFS(g, s2, j);
        for (int j = 0; j < nrv && !ans; j++)
            for (int i = 0; i < nrv && !ans; i++)
                if ((s1->arr[i] == j) && (s2->arr[j] == i))
                    canbe[i] = 1;
    }

    for (int i = 0; i < nrv; i++)
    {
        if (canbe[i] == 1)
            printf("restaurantul %d poate fi ajuns\n", i);
        else
            printf("restaurantul %d nu poate fi ajuns\n", i);
    }
    
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

    insert_edges(g,edg_nr,nrv);

    

    canbe(g, nrv, s1, s2);
}
