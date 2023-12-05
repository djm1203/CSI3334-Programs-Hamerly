/* CSI 3334
* Project 6 -- Network Broadcasting
* Filename: driver-proj6.cpp
* Student name: Derek Martinez
* assignment: project 6
* due date: December 8,2023
* version: 1.0
*
* This file implements the classes arrayHeap and graph
*/

#include <iostream>
#include <map>
#include <vector>
#include <sstream>
#include "arrayheap-student-proj6.h"
#include "graph-proj6.h"

using namespace std;

const int INFINITE_COST = 1000000000;
const int SERVER_STRING = 7;

/* isServer
*
*  Parameters:
*       network -- name of a network
*  Return value: whether string contains "_server"
*
*  This function returns true if string contains _server
*  to check for valid networks.
*/
bool isServer(string network) {
    if (network.size() > SERVER_STRING) {
        return network.substr(network.size() - SERVER_STRING) == "_server";
    }
    return false;
}

/* main
 *  Parameters:
 *      argc -- the number of arguments from the command line
 *      argv -- the command line argument values
 *  Return value: 0
 *
 * The main takes in a number of edges in the network. Then checks
 * for unique vertices and if each input is a valid server. The edges
 * are added into a graph where Dijsktra's algorithm is used to
 * calculate minimum total delay from each vertex to the others.
 * Valid servers are outputted with the minimum delay.
 */
int main(){
    int count, cost;
    int minCost = INFINITE_COST;
    int vertCount = 0;
    map<string, int> eMap;
    vector<bool> servers;
    vector<int> delayArray;
    string net1, net2;
    stringstream inSS;

    inSS.clear();

    cin >> count;

    for (int i = 0; i < count; i++) {
        cin >> net1 >> net2 >> cost;
        inSS << net1 << " " << net2 << " " << cost << endl;

        if(eMap.find(net1) == eMap.end()){
            eMap[net1] = vertCount;
            servers.push_back(isServer(net1));
            vertCount++;
        }
        if(eMap.find(net2) == eMap.end()){
            eMap[net2] = vertCount;
            servers.push_back(isServer(net2));
            vertCount++;
        }
    }

    Graph uGraph(eMap.size());

    for (int i = 0; i < count; i++) {
        inSS >> net1 >> net2 >> cost;
        uGraph.addEdge(eMap[net1], eMap[net2], cost);
    }

    for (int i = 0; i < servers.size(); i++) {
        if (servers[i]) {
            delayArray.push_back(0);
            vector<int> aEdges = uGraph.dijkstra(i);

            for (int j = 0; j < servers.size(); j++) {
                if (aEdges[j] >= 0 && delayArray[i] < INFINITE_COST) {
                    delayArray[i] += aEdges[j];
                }
            }

            if (delayArray[i] < INFINITE_COST) {
                minCost = min(minCost, delayArray[i]);
            }
        } else {
            delayArray.push_back(INFINITE_COST);
        }
    }

    if(minCost >= INFINITE_COST){
        cout << "no server can serve the whole network" << endl;
    } else{
        cout << "total delay: " << minCost << endl;
        for(const auto& pair : eMap){
            int ndx = pair.second;
            if(servers[ndx] && delayArray[ndx] == minCost){
                cout << pair.first << endl;
            }
        }
    }

    return 0;
}