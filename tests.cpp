/*
  Copyright (c) 2023
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, A. Danner, L. Fontes, L. Meeden, Z. Palmer, A. Soni
  Distributed as course material for Spring 2023
  CPSC 035: Data Structures and Algorithms
*/

#include <algorithm>
#include <fstream>
#include <string>
#include <vector>

#include <UnitTest++/UnitTest++.h>

#include "adjacencyListGraph.h"
#include "adjacencyListUndirectedGraph.h"
#include "adts/dictionary.h"
#include "adts/graph.h"
#include "graphAlgorithms.h"
#include "ioUtils.h"

using namespace std;

/* helper check function that verifies there are no
   duplicate values in a vector */
template <typename T> void noDupesCheck(std::vector<T> expr);

/* helper check function that verifies that
   two vectors are set equivalent. An item
   is in the first vector iff it is in the
   second vector.  */
template <typename T>
void vectorsEqualCheck(std::vector<T> first, std::vector<T> second);

/* helper function to check if two paths are equivalent */
void checkEqualPath(vector<string> expected, vector<string> actual);

template <typename V, typename E, typename W,
          template <class, class, class> class G = AdjacencyListUndirectedGraph>
Graph<V, E, W>* makeGraph(vector<V> vertices, vector<Edge<V, E, W>> edges) {
    Graph<V, E, W>* graph = new G<V, E, W>();
    for (int i = 0; i < vertices.size(); i++) {
        graph->insertVertex(vertices.at(i));
    }
    for (int i = 0; i < edges.size(); i++) {
        Edge<V, E, W> edge = edges.at(i);
        graph->insertEdge(edge.getSource(), edge.getDestination(),
                          edge.getLabel(), edge.getWeight());
    }
    return graph;
}

TEST(numGraph) {
    // Creates a graph with integer vertices
    Graph<int,int,int>* graph = new AdjacencyListUndirectedGraph<int,int,int>();
    graph->insertVertex(1);
    graph->insertVertex(2);
    graph->insertEdge(1, 2, 0, 8);
    CHECK_EQUAL(1, graph->getEdges().size());
    delete graph;
}

TEST(getEdges) {
    // Creates an undirected graph with 4 edges:
    // "1"  ---  1,"12"  ***  "2"  ---  1,"24"  --- "4"
    //    \                  /
    //     \                /
    //   1,"13"            1,"23"
    //        \          /
    //         \        /
    //            "3"
    // and queries getEdges to ensure duplicates are correctly removed
    Graph<string, string, int>* graph = makeGraph<string, string, int>(
        {"1", "2", "3", "4"}, {{"1", "2", "12", 1},
                               {"1", "3", "13", 1},
                               {"2", "3", "23", 1},
                               {"2", "4", "24", 1}});
    vector<Edge<string, string, int>> edges = graph->getEdges();
    CHECK_EQUAL(4, edges.size());
    vector<string> labels = {edges[0].getLabel(), edges[1].getLabel(),
                             edges[2].getLabel(), edges[3].getLabel()};
    sort(labels.begin(), labels.end());
    vector<string> answer = {"12", "13", "23", "24"};
    vectorsEqualCheck(answer, labels);
    delete graph;
}

TEST(dfsTwoVertexGraph) {
    // This creates the *undirected* graph:
    //    "1"  --- 1,true ---  "2"
    Graph<string, bool, int>* graph =
        makeGraph<string, bool, int>({"1", "2"}, {{"1", "2", true, 1}});
    CHECK(reachableDFS(string("1"), string("2"), graph));
    CHECK(reachableDFS(string("2"), string("1"), graph));
    delete graph;
}

TEST(dfsTwoDisconnectedVertices) {
    // This creates the *undirected* graph:
    //    "1"                  "2"
    Graph<string, bool, int>* graph =
        makeGraph<string, bool, int>({"1", "2"}, {});
    CHECK(!reachableDFS(string("1"), string("2"), graph));
    CHECK(!reachableDFS(string("2"), string("1"), graph));
    delete graph;
}

TEST(dfsThreeVertexDirectedGraph) {
    // This call makes a *directed* graph!
    Graph<string, bool, int>* graph =
        makeGraph<string, bool, int, AdjacencyListGraph>(
            {"1", "2", "3"},
            {
                {"1", "2", true, 1}, {"1", "3", true, 1},
            });
    CHECK(reachableDFS(string("1"), string("1"), graph));
    CHECK(reachableDFS(string("1"), string("2"), graph));
    CHECK(reachableDFS(string("1"), string("3"), graph));
    CHECK(!reachableDFS(string("3"), string("1"), graph));
    CHECK(!reachableDFS(string("2"), string("1"), graph));
    CHECK(!reachableDFS(string("2"), string("3"), graph));
    delete graph;
}

TEST(dfsSocialNetwork25) {
    Graph<string, int, int>* graph =
        readRailwayGraph("test_data/socialNetwork_25.graph");
    vector<string> vertices = graph->getVertices();
    CHECK(reachableDFS(vertices[3], vertices[17], graph));
    CHECK(reachableDFS(vertices[18], vertices[9], graph));
    CHECK(reachableDFS(vertices[22], vertices[12], graph));
    CHECK(reachableDFS(vertices[1], vertices[18], graph));
    delete graph;
}

TEST(dfsSocialNetwork1000) {
    Graph<string, int, int>* graph =
        readRailwayGraph("test_data/socialNetwork_1000.graph");
    vector<string> vertices = graph->getVertices();
    CHECK(reachableDFS(vertices[34], vertices[71], graph));
    CHECK(reachableDFS(vertices[18], vertices[92], graph));
    CHECK(reachableDFS(vertices[46], vertices[15], graph));
    CHECK(reachableDFS(vertices[8], vertices[66], graph));
    delete graph;
}

TEST(dfsSocialNetworkDisconnected20) {
    Graph<string, int, int>* graph =
        readRailwayGraph("test_data/socialNetworkDisconnected_20.graph");
    vector<string> vertices = graph->getVertices();
    CHECK(reachableDFS(string("Kevin Bacon"), string("Pigby Strangepork"),
                       graph));
    CHECK(reachableDFS(string("Pigby Strangepork"), string("Nanny Summer"),
                       graph));
    CHECK(
        reachableDFS(string("Hogzilla Bland"), string("Piglet Corpus"), graph));
    CHECK(reachableDFS(string("Hamlet Pigasus"), string("Toot Bacon"), graph));
    CHECK(!reachableDFS(string("Kevin Bacon"), string("Toot Bacon"), graph));
    CHECK(!reachableDFS(string("Pigby Strangepork"), string("Hogzilla Bland"),
                        graph));
    CHECK(
        !reachableDFS(string("Nanny Summer"), string("Piglet Corpus"), graph));
    CHECK(!reachableDFS(string("Hamlet Pigasus"), string("Pigby Strangepork"),
                        graph));
    delete graph;
}

TEST(bfsThreeVertexClique) {
    // This call makes an undirected graph.
    Graph<string, bool, int>* graph = makeGraph<string, bool, int>(
        {"1", "2", "3"},
        {
            {"1", "2", true, 1}, {"1", "3", true, 1}, {"2", "3", true, 1},
        });
    vector<string> path = {"1", "3"};
    checkEqualPath(path,
                   shortestLengthPathBFS(string("1"), string("3"), graph));
    path = {"1", "2"};
    checkEqualPath(path,
                   shortestLengthPathBFS(string("1"), string("2"), graph));
    delete graph;
}

TEST(bfsFiveVertex) {
    // This call makes an undirected graph.
    Graph<string, bool, int>* graph = makeGraph<string, bool, int>(
        {"start", "1", "2", "finish", "alt"}, {{"start", "1", true, 1},
                                               {"1", "2", true, 1},
                                               {"2", "finish", true, 1},
                                               {"start", "alt", true, 1},
                                               {"alt", "finish", true, 1}});
    vector<string> path = {"start", "alt", "finish"};
    checkEqualPath(
        path, shortestLengthPathBFS(string("start"), string("finish"), graph));
    delete graph;
}

TEST(bfsFiveVertexDirected) {
    // This call makes a directed graph.
    Graph<string, bool, int>* graph =
        makeGraph<string, bool, int, AdjacencyListGraph>(
            {"start", "1", "2", "finish", "alt"}, {{"start", "1", true, 1},
                                                   {"1", "2", true, 1},
                                                   {"2", "finish", true, 1},
                                                   {"finish", "alt", true, 1},
                                                   {"alt", "start", true, 1}});
    vector<string> path = {"start", "1", "2", "finish"};
    checkEqualPath(
        path, shortestLengthPathBFS(string("start"), string("finish"), graph));
    delete graph;
}

TEST(bfsSocialNetwork25) {
    Graph<string, int, int>* graph =
        readRailwayGraph("test_data/socialNetwork_25.graph");
    vector<string> path = {"Jaimie Dengar", "Kevin Bacon"};
    checkEqualPath(path, shortestLengthPathBFS(string("Jaimie Dengar"),
                                               string("Kevin Bacon"), graph));
    delete graph;
}

TEST(bfsSocialNetwork1000) {
    Graph<string, int, int>* graph =
        readRailwayGraph("test_data/socialNetwork_1000.graph");
    vector<string> path = {"Jaimie Dengar", "Kevin Bacon"};
    checkEqualPath(path, shortestLengthPathBFS(string("Jaimie Dengar"),
                                               string("Kevin Bacon"), graph));
    path = {"Sam Curlytail", "Waddles Hog", "Kevin Bacon"};
    checkEqualPath(path, shortestLengthPathBFS(string("Sam Curlytail"),
                                               string("Kevin Bacon"), graph));
    delete graph;
}

TEST(bfsSocialNetworkDisconnected20) {
    Graph<string, int, int>* graph =
        readRailwayGraph("test_data/socialNetworkDisconnected_20.graph");
    vector<string> path = {"Piglet Corpus", "Rooter Ziffel", "Hogzilla Bland"};
    checkEqualPath(path,
                   shortestLengthPathBFS(string("Piglet Corpus"),
                                         string("Hogzilla Bland"), graph));
    path = {"Freddy Wen", "Kevin Bacon"};
    checkEqualPath(path, shortestLengthPathBFS(string("Freddy Wen"),
                                               string("Kevin Bacon"), graph));
    CHECK_THROW(shortestLengthPathBFS(string("Edessa Pork"),
                                      string("Kevin Bacon"), graph),
                std::exception);
    delete graph;
}

TEST(ssspFiveVertex) {
    // This call makes an undirected graph.
    Graph<string, bool, int>* graph = makeGraph<string, bool, int>(
        {"start", "1", "2", "finish", "alt"}, {{"start", "1", false, 3},
                                               {"1", "2", false, 4},
                                               {"2", "finish", false, 2},
                                               {"start", "alt", false, 5},
                                               {"alt", "finish", false, 6}});
    Dictionary<string, int>* results =
        singleSourceShortestPath(string("start"), graph);
    CHECK_EQUAL(9, results->get("finish"));
    CHECK_EQUAL(7, results->get("2"));
    CHECK_EQUAL(5, results->get("alt"));
    CHECK_EQUAL(5, results->getSize());
    delete results;
    delete graph;
}

TEST(ssspFiveVertexDirected) {
    // This call makes a directed graph.
    Graph<string, bool, int>* graph =
        makeGraph<string, bool, int, AdjacencyListGraph>(
            {"start", "1", "2", "finish", "alt"},
            {{"finish", "2", false, 3},
             {"2", "1", false, 4},
             {"1", "start", false, 2},
             {"start", "alt", false, 5},
             {"alt", "finish", false, 6}});
    Dictionary<string, int>* results =
        singleSourceShortestPath(string("start"), graph);
    CHECK_EQUAL(11, results->get("finish"));
    CHECK_EQUAL(14, results->get("2"));
    CHECK_EQUAL(5, results->get("alt"));
    CHECK_EQUAL(5, results->getSize());
    delete results;
    delete graph;
}

TEST(ssspFiveVertexDirectedUnreachable) {
    // This call makes a directed graph.
    Graph<string, bool, int>* graph =
        makeGraph<string, bool, int, AdjacencyListGraph>(
            {"start", "1", "2", "finish", "alt"},
            {{"finish", "2", false, 3},
             {"1", "start", false, 2},
             {"start", "alt", false, 5},
             {"alt", "finish", false, 6}});
    Dictionary<string, int>* results =
        singleSourceShortestPath(string("start"), graph);

    CHECK_EQUAL(4, results->getSize());
    CHECK_EQUAL(11, results->get("finish"));
    CHECK_EQUAL(14, results->get("2"));
    CHECK_EQUAL(5, results->get("alt"));
    CHECK(!results->contains("1"));
    delete results;
    delete graph;
}


TEST(ssspTown8) {
    // Creates an undirected graph
    Graph<string, int, int>* graph = readRailwayGraph("test_data/town_8.graph");
    Dictionary<string, int>* results =
        singleSourceShortestPath(string("Pigma's Jewelry Museum"), graph);
    CHECK_EQUAL(15, results->get("Arnold's Convenience Stand"));
    CHECK_EQUAL(1, results->get("Petunia's Bowling Town"));
    CHECK_EQUAL(16, results->get("Sam's Photo Retailer"));
    delete results;
    delete graph;
}

TEST(ssspTown100) {
    // Creates an undirected graph
    Graph<string, int, int>* graph =
        readRailwayGraph("test_data/town_100.graph");
    Dictionary<string, int>* results =
        singleSourceShortestPath(string("Cochon's Movie Vault"), graph);
    CHECK_EQUAL(24, results->get("Hamhock's Trinket Ltd"));
    CHECK_EQUAL(22, results->get("Toby's Furniture Warehouse"));
    CHECK_EQUAL(22, results->get("Saddlebottom's Photo Trough"));
    delete results;
    results = singleSourceShortestPath(string("Babe's Produce Store"), graph);
    CHECK_EQUAL(23, results->get("Arnold's Convenience Stand"));
    CHECK_EQUAL(35, results->get("Takako's Antique Vault"));
    CHECK_EQUAL(25, results->get("Major's Spice Ltd"));
    delete results;
    delete graph;
}

int main() {
    return UnitTest::RunAllTests();
}

void checkEqualPath(vector<string> expected, vector<string> actual) {
    string expectedPath = "";
    for (int i = 0; i < expected.size(); i++) {
        if (expectedPath.size() > 0) {
            expectedPath += " -- ";
        }
        expectedPath += expected.at(i);
    }
    string actualPath = "";
    for (int i = 0; i < actual.size(); i++) {
        if (actualPath.size() > 0) {
            actualPath += " -- ";
        }
        actualPath += actual.at(i);
    }
    CHECK_EQUAL("path = " + expectedPath, "path = " + actualPath);
}

template <typename T> void noDupesCheck(std::vector<T> expr) {
    auto vec = expr;
    auto it = vec.begin();
    while (it < vec.end()) {
        if (std::find(it + 1, vec.end(), *it) != vec.end()) {
            CHECK_EQUAL(*it + " to be unique in vector",
                        *it + " in vector twice");
        }
        it++;
    }
}

template <typename T>
void vectorsEqualCheck(std::vector<T> first, std::vector<T> second) {
    auto expected = first;
    auto actual = second;
    noDupesCheck(actual);
    CHECK_EQUAL(expected.size(), actual.size());
    for (int i = 0; i < expected.size(); i++) {
        if (std::find(actual.begin(), actual.end(), expected[i]) ==
            actual.end()) {
            CHECK_EQUAL(expected[i] + " to be in vector", "no such result");
        }
    }
    for (int i = 0; i < actual.size(); i++) {
        if (std::find(expected.begin(), expected.end(), actual[i]) ==
            expected.end()) {
            CHECK_EQUAL(actual[i] + " not to be in vector",
                        actual[i] + " in vector");
        }
    }
}
