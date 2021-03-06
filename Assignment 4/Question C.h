//
// Created by tokoyama on 25/02/21.
//

#ifndef DSALAB_QUESTION_C_H
#define DSALAB_QUESTION_C_H

#endif //DSALAB_QUESTION_C_H

//using graph
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <memory.h>
#include <zconf.h>

int visited[500], queue[100], qsize = 0, qlast = 0;


struct Node {
    int vertex;
    struct Node *next;
};

struct Node *createNode(int);

struct Graph {
    int numVertices;
    struct Node **adjLists;
    int *visited;
};

// BFS algorithm
int bfs(struct Graph *graph, int startVertex, int endVertex) {

    graph->visited[startVertex] = 1;
    queue[qlast++] = startVertex;
    qsize++;
    int distance[1000], first = 0;
//    for (int i = 0; i < 1000; ++i) {
//        distance[i]=-1;
//    }
    distance[startVertex] = 0;
    while (qsize != 0) {
        int currentVertex = queue[first];
        first++;
        qsize--;

        struct Node *temp = graph->adjLists[currentVertex];

        while (temp) {
            int adjVertex = temp->vertex;

            if (graph->visited[adjVertex] == 0) {
                distance[adjVertex] = distance[currentVertex] + 1;
                graph->visited[adjVertex] = 1;
                queue[qlast++] = adjVertex;
                qsize++;

            }
            temp = temp->next;
        }
    }
    return distance[endVertex];
}

// Creating a Node
struct Node *createNode(int v) {
    struct Node *newNode = malloc(sizeof(struct Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

// Creating a graph
struct Graph *createGraph(int vertices) {
    struct Graph *graph = malloc(sizeof(struct Graph));
    graph->numVertices = vertices;
    graph->adjLists = malloc(vertices * sizeof(struct Node *));
    graph->visited = malloc(vertices * sizeof(int));
    int i;
    for (i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
        graph->visited[i] = 0;
    }

    return graph;
}

// Add edge
void addEdge(struct Graph *graph, int src, int dest) {
    struct Node *newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;
    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

bool oneLetterDifference(char a[], char b[]) {
    int n1 = strlen(a);
    int n2 = strlen(b);
    if (n1 != n2)
        return false;
    int c = 0;
    for (int i = 0; i < n1; ++i) {
        if (a[i] == b[i])
            c++;
    }
    if (n1 - c == 1)
        return true;
    else
        return false;

}


bool noSameLetter(char a[], char b[]) {

    int n1 = strlen(a);
    int n2 = strlen(b);
    if (n1 != n2)
        return false;
    for (int i = 0; i < n1; ++i) {
        if (a[i] == b[i])
            return false;

    }
    return true;
}

void solve() {
    int n;
    scanf("%d", &n);
    n++;

    struct Graph *graph = createGraph(n);
    char words[1000][12];
    for (int i = 0; i < n; ++i) {
        scanf("%s", words[i]);
    }
//    printf("%d\n ",oneLetterDifference(words[0],words[1]));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (oneLetterDifference(words[i], words[j]) == true) {
                addEdge(graph, i, j);
//                printf("%s and %s are connected by %d %d\n ",words[i],words[j],i,j);
            }

        }
    }
    int arr[1000], k = 0;
    for (int i = 0; i < n; ++i) {
        if (noSameLetter(words[0], words[i]) == true) {
            arr[k++] = i;
//            printf("%s ",words[i]);
        }
//        printf("%s ",words[i]);
    }
    int min = INT_MAX;
    for (int i = 0; i < k; ++i) {
        int x = bfs(graph, 0, arr[i]) - 1;
//        printf("%d ",x);
        if (min > x)
            min = x;
    }
    if (min > 0)
        printf("%d", min);
    else
        printf("-1");

}






