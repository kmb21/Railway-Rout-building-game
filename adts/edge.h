#pragma once



/**
 * An Edge is a class that represents a directed, weighted edge in a graph.
 * It is templated on three types.
 * @tparam V a type to represent the vertex labels
 * @tparam E a type to represent the edge labels
 * @tparam W a type to represent the weight (usually an int, float, or double)
 */
template <typename V, typename E, typename W> class Edge {
  public:
    Edge(V source, V destination, E label, W weight = 1);

    E getLabel() {
        return label;
    }
    V getSource() {
        return source;
    }
    V getDestination() {
        return dest;
    }
    W getWeight() {
        return weight;
    }

  private:
    V source;
    V dest;
    W weight;
    E label;
};

template <typename V, typename E, typename W>
Edge<V, E, W>::Edge(V source, V dest, E label, W weight) {
    this->source = source;
    this->label = label;
    this->weight = weight;
    this->dest = dest;
}
