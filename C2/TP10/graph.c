#include "graph.h"

int writeGraphViz(Graph * g, char * filename) {
    FILE * f = NULL;

    if ((f = (FILE *) fopen(filename, "w")) == (FILE *) NULL) {
        fprintf(stderr, "Error while opening %s\n", filename);
        return 458;
    }

    fprintf(f, "digraph {\n");

    setOnFirstVertex(g);
    while (!outOfVertexList(g)) {
        EdgeList * successors = &(g->current->connect);

        setOnFirstEdge(successors);
        while (!outOfEdgeList(successors)) {
            fprintf(f, "\t%s -> %s;\n", &(g->current->label), &(successors->current->v->label));
            nextEdge(successors);
        }

        nextVertex(g);
    }

    fprintf(f, "}");
    fclose(f);

    return 0;
}

static Vertex * findNearestVertex(Graph * g) {
    int shortestDist = MY_INFINITY;
    Vertex * nearestVertex = NULL;

    setOnFirstVertex(g);
    while (!outOfVertexList(g)) {
        if (g->current->already_visited == 0) {
            if (g->current->dist_to_origin < shortestDist) {
                shortestDist = g->current->dist_to_origin;
                nearestVertex = g->current;
            }
        }

        nextVertex(g);
    }

    return nearestVertex;
}

static void updateDistSuccessors(Vertex * v) {
    EdgeList * successors = &(v->connect);

    setOnFirstEdge(successors);
    while (!outOfEdgeList(successors)) {
        if (successors->current->v->dist_to_origin > v->dist_to_origin + successors->current->dist) {
            successors->current->v->dist_to_origin = v->dist_to_origin + successors->current->dist;
        }

        nextEdge(successors);
    }
}

static void initDijkstra(Graph * g, Vertex * root) {
    setOnFirstVertex(g);
    while (!outOfVertexList(g)) {
        g->current->dist_to_origin = MY_INFINITY;
        g->current->already_visited = 0;

        nextVertex(g);
    }

    root->dist_to_origin = 0;
    root->already_visited = 1;

    updateDistSuccessors(root);

    g->current = root;
}

int shortestPathDijkstra(Graph * g, char val1, char val2) {
    Vertex * min = NULL;

    Vertex * dest = findVertexGraph(g, val2);
    Vertex * root = findVertexGraph(g, val1);
    
    if (root == NULL)
        return -1;

    initDijkstra(g, root);

    while (dest->already_visited == 0) {
        min = findNearestVertex(g);
        min->already_visited = 1;

        printf("%c\n", min->label);

        updateDistSuccessors(min);
        g->current = min;
    }

    return 0;
}
