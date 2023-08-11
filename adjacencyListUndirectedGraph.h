/*
  Copyright (c) 2023
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, A. Danner, L. Fontes, L. Meeden, Z. Palmer, A. Soni
  Distributed as course material for Spring 2023
  CPSC 035: Data Structures and Algorithms
*/

#pragma once


#include "adjacencyListGraph.h"

/**
 * AdjacencyListUndirectedGraph is a class representing
 *   undirected, weighted graphs.
 *
 * It is a subclass of AdjacencyListGraph for the purpose of code reuse.
 * @tparam V a type to represent the vertex labels
 * @tparam E a type to represent the edge labels
 * @tparam W a type to represent the weight (usually an int, float, or double)
 */
template <typename V, typename E, typename W>
class AdjacencyListUndirectedGraph : public AdjacencyListGraph<V, E, W> {
  public:
    /**
    * Adds an undirected edge to this graph.
    * @param source The source vertex for the edge.
    * @param destination The destination vertex for the edge.
    * @param label The label of the edge to add.
    * @param weight The weight of the edge to add.
    * @throws runtime_error If an edge already exists between the given source
    *                       and target.
    */
    void insertEdge(V src, V dest, E label, W weight);

    /**
     * Removes an edge from this graph.
     * @param source The source vertex for the edge.
     * @param destination The destination vertex for the edge.
     * @throws runtime_error If the edge does not exist.
     */
    void removeEdge(V src, V dest);

    /**
   * Retrieves all edges from this graph.
   * @return A vector containing every edge in this graph.
   */
    vector<Edge<V, E, W>> getEdges();
};

#include "adjacencyListUndirectedGraph-inl.h"
