/*
  Copyright (c) 2023
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, A. Danner, L. Fontes, L. Meeden, Z. Palmer, A. Soni
  Distributed as course material for Spring 2023
  CPSC 035: Data Structures and Algorithms
*/

#include <functional>
#include <ostream>
#include <string>
#include <utility>
#include <vector>

#include "../adts/dictionary.h"
#include "../adts/edge.h"
#include "../adts/graph.h"
#include "../adts/list.h"
#include "dataWriter.h"

template <typename T, typename U>
void DataWriter::writePair(std::pair<T, U> pair,
                           std::function<void(T)> firstWriter,
                           std::function<void(U)> secondWriter) {
    writeCharToStream('p');
    firstWriter(pair.first);
    secondWriter(pair.second);
    writeCharToStream('$');
}

template <typename T>
void DataWriter::writeList(List<T>* elements,
                           std::function<void(T)> elementWriter) {
    writeCharToStream('l');
    writeCharToStream('[');
    for (int i = 0; i < elements->getSize(); i++) {
        writeCharToStream(',');
        elementWriter(elements->get(i));
    }
    writeCharToStream(']');
}

template <typename T>
void DataWriter::writeVector(vector<T> elements,
                             std::function<void(T)> elementWriter) {
    writeCharToStream('l');
    writeCharToStream('[');
    for (int i = 0; i < elements.size(); i++) {
        writeCharToStream(',');
        elementWriter(elements[i]);
    }
    writeCharToStream(']');
}

template <typename K, typename V>
void DataWriter::writeDictionary(Dictionary<K, V>* dictionary,
                                 std::function<void(K)> keyWriter,
                                 std::function<void(V)> valueWriter) {
    writeCharToStream('d');
    writeCharToStream('{');
    vector<pair<K, V>> items = dictionary->getItems();
    writeVector<pair<K, V>>(items, [&](pair<K, V> pair) {
        return writePair(pair, keyWriter, valueWriter);
    });
    writeCharToStream('}');
}

template <typename V, typename E, typename W>
void DataWriter::writeEdge(Edge<V, E, W> edge,
                           std::function<void(V)> vertexWriter,
                           std::function<void(E)> edgeDataWriter,
                           std::function<void(W)> weightWriter) {
    writeCharToStream('e');
    vertexWriter(edge.getSource());
    edgeDataWriter(edge.getLabel());
    weightWriter(edge.getWeight());
    vertexWriter(edge.getDestination());
    writeCharToStream('$');
}

template <typename V, typename E, typename W>
void DataWriter::writeGraph(Graph<V, E, W>* graph,
                            std::function<void(V)> vertexWriter,
                            std::function<void(E)> edgeDataWriter,
                            std::function<void(W)> weightWriter) {
    writeCharToStream('g');
    writeCharToStream('{');

    vector<V> vertices = graph->getVertices();
    writeVector<V>(vertices, vertexWriter);

    vector<Edge<V, E, W>> edges = graph->getEdges();
    writeVector<Edge<V, E, W>>(edges, [&](Edge<V, E, W> edge) {
        return writeEdge(edge, vertexWriter, edgeDataWriter, weightWriter);
    });

    writeCharToStream('}');
}
