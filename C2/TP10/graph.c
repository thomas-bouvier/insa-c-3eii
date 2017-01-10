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
            fprintf(f, "\t%s -> %s,\n", &(g->current->label), &(successors->current->v->label));
            nextEdge(successors);
        }

        nextVertex(g);
    }

    fprintf(f, "}");
    fclose(f);

    return 0;
}
