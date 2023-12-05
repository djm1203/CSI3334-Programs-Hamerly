/* CSI 3334
* Project 6 -- Network Broadcasting
* Filename: graph-proj6.cpp
* Student name: Derek Martinez
* assignment: project 6
* due date: December 8,2023
* version: 1.0
*
* This file implements the function from graph
*/

#include "graph-proj6.h"
#include "arrayheap-student-proj6.h"

/* addEdge
*
*  Parameters:
*       from -- source
*       to   -- destination
*       cost -- cost of  traversal
*  Return value: none
*
*  This adds the destination to the source vertex list,
*  adding an edge
*/
void Graph::addEdge(int from, int to, int cost){
    if (inVertexRange(from) && inVertexRange(to)) {
        adjacencyList[from].push_back(Edge(to, cost));
    }
}

/* dijkstra
*
*  Parameters:
*       source -- source of paths
*  Return value: cost of travel to each destination from source
*
*  This finds the shortest path from source to every vertex
*/
vector<int> Graph::dijkstra(int source) const{
    const int numVertices = adjacencyList.size();

    vector<int> distanceList(numVertices, INFINITE_COST);
    vector<int> keys(numVertices, -1);

    ArrayHeap<pair<int, int>> frontier;
    distanceList[source] = 0;

    pair<int, int> sourcePair = {0, source};
    keys[source] = frontier.insert(sourcePair);

    while (frontier.getNumItems() != 0) {
        int curr = frontier.getMinItem().second;
        frontier.removeMinItem();

        for(auto i = adjacencyList[curr].begin(); i != adjacencyList[curr].end(); i++){
            auto& neighbor = *i;
            int to = neighbor.to;
            int weight = neighbor.cost;

            if (distanceList[curr] + weight < distanceList[to]) {
                distanceList[to] = weight + distanceList[curr];

                if (!frontier.isOnHeap(keys[to])) {
                    keys[to] = frontier.insert({distanceList[to], to});
                } else {
                    frontier.changeItemAtKey(keys[to], {distanceList[to], to});
                }
            }
        }
    }
    return distanceList;
}