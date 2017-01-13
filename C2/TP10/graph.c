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

static void initDijkstra(Graph * g, Vertex * root) {
    setOnFirstVertex(g);
    while (!outOfVertexList(g)) {
        g->current->dist_to_origin = MY_INFINITY;
        g->current->already_visited = 0;

        nextVertex(g);
    }
    root->dist_to_origin = 0;

    g->current = root;
}

static Vertex * findNearestVertex(Graph * g) {
    int shortestDist = 0;
    Vertex * nearestVertex = NULL;
    EdgeList * successors = &(g->current->connect);

    setOnFirstEdge(successors);
    while (!outOfEdgeList(successors)) {
        if (successors->current->dist < shortestDist) {
            shortestDist = successors->current->dist;
            nearestVertex = successors->current;
        }

        nextEdge(successors);
    }

    return nearestVertex;
}

static void updateDist(Vertex * v1, Vertex * v2) {
    int v2IsSuccessorOfV1 = 0;
    int distBetweenVertices = -1;
    EdgeList * successors = &(v1->connect);

    setOnFirstEdge(successors);
    while (!outOfEdgeList(successors)) {
        if (successors->current->v == v2) {
            v2IsSuccessorOfV1 = 1;
            distBetweenVertices = successors->current->dist;
        }
    }

    if (v2IsSuccessorOfV1 == 0) {
        fprintf(stderr, "%c is not a successor of %c\n", v2->label, v1->label);
        return;
    }

    if (v2->dist_to_origin > v1->dist_to_origin + distBetweenVertices) {
        v2->dist_to_origin = v1->dist_to_origin + distBetweenVertices;
    }
}

int shortestPathDijkstra(Graph * g, char val1, char val2) {
    Vertex * min = NULL;
    EdgeList * successors = NULL;
    Vertex * root = findVertexGraph(g, val1);
    if (root == NULL)
        return -1;

    initDijkstra(g, findVertexGraph(g, val1));

    while (1) {
        min = findNearestVertex(g);

        printf("%c\n", min->label);


        min->already_visited = 1;

        /*
        successors = &(min->connect);

        setOnFirstEdge(successors);
        while (!outOfEdgeList(successors)) {
            updateDist(min, successors->current->v);
            nextEdge(successors);
        }
        */
        break;
    }

    return 0;
}
