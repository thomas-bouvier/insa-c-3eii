#include <stdio.h>
#include <stdlib.h>

#include "graph.h"

int main() {
    Graph g;
    int dist_to_origin;

    initGraph(&g);

    /*
    addVertexGraph(&g, 'A');
    addVertexGraph(&g, 'B');
    addVertexGraph(&g, 'C');
    addVertexGraph(&g, 'D');
    addVertexGraph(&g, 'E');
    addVertexGraph(&g, 'F');
    addVertexGraph(&g, 'G');
    addVertexGraph(&g, 'H');
    addVertexGraph(&g, 'I');
    addVertexGraph(&g, 'J');
    addVertexGraph(&g, 'K');
    addVertexGraph(&g, 'L');
    addVertexGraph(&g, 'M');

    addEdgeGraph(&g, 'A', 'B', 10);
    addEdgeGraph(&g, 'B', 'C', 10);
    addEdgeGraph(&g, 'A', 'C', 10);
    addEdgeGraph(&g, 'D', 'E', 10);
    addEdgeGraph(&g, 'E', 'F', 5);
    addEdgeGraph(&g, 'F', 'E', 5);
    addEdgeGraph(&g, 'F', 'G', 40);
    addEdgeGraph(&g, 'G', 'H', 30);
    addEdgeGraph(&g, 'E', 'M', 30);
    addEdgeGraph(&g, 'M', 'L', 2);
    addEdgeGraph(&g, 'M', 'K', 5);
    addEdgeGraph(&g, 'K', 'G', 5);
    addEdgeGraph(&g, 'D', 'J', 25);
    addEdgeGraph(&g, 'J', 'I', 30);
    addEdgeGraph(&g, 'I', 'H', 5);
    */

    addVertexGraph(&g, 'A');
    addVertexGraph(&g, 'B');
    addVertexGraph(&g, 'C');
    addVertexGraph(&g, 'D');
    addVertexGraph(&g, 'E');
    addVertexGraph(&g, 'F');
    addVertexGraph(&g, 'G');
    addVertexGraph(&g, 'H');
    addVertexGraph(&g, 'I');
    addVertexGraph(&g, 'J');

    addEdgeGraph(&g, 'A', 'B', 85);
    addEdgeGraph(&g, 'A', 'C', 217);
    addEdgeGraph(&g, 'A', 'E', 173);
    addEdgeGraph(&g, 'B', 'F', 80);
    addEdgeGraph(&g, 'C', 'G', 186);
    addEdgeGraph(&g, 'C', 'H', 103);
    addEdgeGraph(&g, 'E', 'J', 502);
    addEdgeGraph(&g, 'F', 'I', 250);
    addEdgeGraph(&g, 'I', 'J', 84);
    addEdgeGraph(&g, 'H', 'J', 167);
    addEdgeGraph(&g, 'H', 'D', 183);

    //printGraph(&g);
    writeGraphViz(&g, "graph.dot");

    dist_to_origin = shortestPathDijkstra(&g, 'A', 'J');
    printf("Shortest path from %c to %c : %dkm\n", 'A', 'J', dist_to_origin);
    printf("This path is \n");
    /*
    printEdgeList(&findVertex(&g,'H')->path);
    */

    deleteGraph(&g);

    return EXIT_SUCCESS;
}
