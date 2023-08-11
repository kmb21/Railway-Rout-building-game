/*
  Copyright (c) 2023
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, A. Danner, L. Fontes, L. Meeden, Z. Palmer, A. Soni
  Distributed as course material for Spring 2023
  CPSC 035: Data Structures and Algorithms
*/

#pragma once


template <typename V, typename E, typename W>
void AdjacencyListUndirectedGraph<V, E, W>::insertEdge(V src, V dest, E label,
                                                       W weight) {
    // insert the edge as two directional edges.
    // This lets getNeighbors to work without changes
    AdjacencyListGraph<V, E, W>::insertEdge(src, dest, label, weight);
    AdjacencyListGraph<V, E, W>::insertEdge(dest, src, label, weight);
}
  
template <typename V, typename E, typename W>
void AdjacencyListUndirectedGraph<V, E, W>::removeEdge(V src, V dest) {
    AdjacencyListGraph<V, E, W>::removeEdge(src, dest);
    AdjacencyListGraph<V, E, W>::removeEdge(dest, src);
}

template <typename V, typename E, typename W>
vector<Edge<V, E, W>> AdjacencyListUndirectedGraph<V, E, W>::getEdges() {
    vector<Edge<V, E, W>> toReturn;
    vector<Edge<V, E, W>> withDups = AdjacencyListGraph<V, E, W>::getEdges();
    bool foundDup = false;

    // iterate over withDups.  add in only if not already there.
    for (int i = 0; i < withDups.size(); i++) {
        foundDup = false;
        for (int j = 0; j < toReturn.size(); j++) {
            if ((withDups[i].getSource() == toReturn[j].getDestination()) &&
                (withDups[i].getDestination() == toReturn[j].getSource())) {
                foundDup = true;
                break;
            }
        }
        if (!foundDup) {
            toReturn.push_back(withDups[i]);
        }
    }

    return toReturn;
}
