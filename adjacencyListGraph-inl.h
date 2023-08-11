/*
  Copyright (c) 2023
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, A. Danner, L. Fontes, L. Meeden, Z. Palmer, A. Soni
  Distributed as course material for Spring 2023
  CPSC 035: Data Structures and Algorithms
*/

#pragma once

#include "stringUtils.h"

template <typename V, typename E, typename W>
AdjacencyListGraph<V, E, W>::AdjacencyListGraph() {
}

template <typename V, typename E, typename W>
AdjacencyListGraph<V, E, W>::~AdjacencyListGraph() {
    vector<V> sources = this->edges.getKeys();
    for (int i = 0; i < sources.size(); i++) {
        delete this->edges.get(sources[i]);
    }
}


template <typename V, typename E, typename W>
vector<V> AdjacencyListGraph<V, E, W>::getVertices() {
    return this->vertices.getKeys();
}

template <typename V, typename E, typename W>
void AdjacencyListGraph<V, E, W>::insertVertex(V v) {
    if (!this->vertices.contains(v)) {
        this->vertices.insert(v, true);
        this->edges.insert(v, new STLHashTable<V, pair<E, W>>());
    }
}

template <typename V, typename E, typename W>
void AdjacencyListGraph<V, E, W>::removeVertex(V v) {
    if (this->vertices.contains(v)) {
        this->vertices.remove(v);
    }
}

template <typename V, typename E, typename W>
bool AdjacencyListGraph<V, E, W>::containsVertex(V v) {
    return this->vertices.contains(v);
}

template <typename V, typename E, typename W>
void AdjacencyListGraph<V, E, W>::insertEdge(V src, V dest, E label, W weight) {
    if (!containsVertex(src)) {
        throw runtime_error(std::string("Vertex ") + cs35::to_string(src) +
                            " not present in graph");
    }
    if (!containsVertex(dest)) {
        throw runtime_error(std::string("Vertex ") + cs35::to_string(dest) +
                            " not present in graph");
    }
    if (this->edges.get(src)->contains(dest)) {
        throw runtime_error(std::string("Edge already exists from ") +
                            cs35::to_string(src) + " to " +
                            cs35::to_string(dest));
    } else {
        this->edges.get(src)->insert(dest, pair<E, W>(label, weight));
    }
}

template <typename V, typename E, typename W>
void AdjacencyListGraph<V, E, W>::removeEdge(V src, V dest) {
    if (this->edges.contains(src) && this->edges.get(src)->contains(dest)) {
        this->edges.get(src)->remove(dest);
    } else {
        throw runtime_error(std::string("Edge does not exist from ") +
                            cs35::to_string(src) + " to " +
                            cs35::to_string(dest));
    }
}

template <typename V, typename E, typename W>
bool AdjacencyListGraph<V, E, W>::containsEdge(V source, V destination) {
    return this->edges.contains(source) &&
           this->edges.get(source)->contains(destination);
}

template <typename V, typename E, typename W>
Edge<V, E, W> AdjacencyListGraph<V, E, W>::getEdge(V source, V destination) {
    if (this->edges.contains(source) &&
        this->edges.get(source)->contains(destination)) {
        pair<E, W> data = this->edges.get(source)->get(destination);
        return Edge<V, E, W>(source, destination, data.first, data.second);
    } else {
        throw runtime_error(std::string("Edge does not exist from ") +
                            cs35::to_string(source) + " to " +
                            cs35::to_string(destination));
    }
}

template <typename V, typename E, typename W>
vector<Edge<V, E, W>> AdjacencyListGraph<V, E, W>::getEdges() {
    vector<Edge<V, E, W>> results;
    vector<V> sources = this->edges.getKeys();
    for (int i = 0; i < sources.size(); i++) {
        vector<V> targets = this->edges.get(sources[i])->getKeys();
        for (int j = 0; j < targets.size(); j++) {
            pair<E, W> data = this->edges.get(sources[i])->get(targets[j]);
            results.push_back(
                Edge<V, E, W>(sources[i], targets[j], data.first, data.second));
        }
    }
    return results;
}

template <typename V, typename E, typename W>
vector<Edge<V, E, W>> AdjacencyListGraph<V, E, W>::getOutgoingEdges(V source) {
    vector<Edge<V, E, W>> results;
    vector<V> targets = this->edges.get(source)->getKeys();
    for (int j = 0; j < targets.size(); j++) {
        pair<E, W> data = this->edges.get(source)->get(targets[j]);
        results.push_back(
            Edge<V, E, W>(source, targets[j], data.first, data.second));
    }
    return results;
}

template <typename V, typename E, typename W>
vector<Edge<V, E, W>>
AdjacencyListGraph<V, E, W>::getIncomingEdges(V destination) {
    vector<Edge<V, E, W>> results;
    vector<V> sources = this->edges.getKeys();
    for (int i = 0; i < sources.size(); i++) {
        if (this->edges.get(sources[i])->contains(destination)) {
            pair<E, W> data = this->edges.get(sources[i])->get(destination);
            results.push_back(Edge<V, E, W>(sources[i], destination, data.first,
                                            data.second));
        }
    }
    return results;
}

template <typename V, typename E, typename W>
vector<V> AdjacencyListGraph<V, E, W>::getNeighbors(V source) {
    if (this->edges.contains(source)) {
        return this->edges.get(source)->getKeys();
    } else {
        return vector<V>();
    }
}
