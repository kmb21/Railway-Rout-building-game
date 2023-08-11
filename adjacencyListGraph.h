/*
  Copyright (c) 2023
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, A. Danner, L. Fontes, L. Meeden, Z. Palmer, A. Soni
  Distributed as course material for Spring 2023
  CPSC 035: Data Structures and Algorithms
*/

#pragma once


#include "adts/edge.h"
#include "adts/graph.h"
#include "adts/stlHashTable.h"

template <typename V, typename E, typename W>
class AdjacencyListGraph : public Graph<V, E, W> {
  public:
    AdjacencyListGraph();
    virtual ~AdjacencyListGraph();

    virtual vector<V> getVertices();
    virtual void insertVertex(V v);
    virtual void removeVertex(V v);
    virtual bool containsVertex(V v);
    virtual void insertEdge(V src, V dest, E label, W weight);
    virtual void removeEdge(V src, V dest);
    virtual bool containsEdge(V source, V destination);
    virtual Edge<V, E, W> getEdge(V source, V destination);
    virtual vector<Edge<V, E, W>> getEdges();
    virtual vector<Edge<V, E, W>> getOutgoingEdges(V source);
    virtual vector<Edge<V, E, W>> getIncomingEdges(V destination);
    virtual vector<V> getNeighbors(V source);

  private:
    STLHashTable<V, bool> vertices;
    STLHashTable<V, STLHashTable<V, pair<E, W>>*> edges;
};

#include "adjacencyListGraph-inl.h"
