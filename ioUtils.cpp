/*
  Copyright (c) 2023
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, A. Danner, L. Fontes, L. Meeden, Z. Palmer, A. Soni
  Distributed as course material for Spring 2023
  CPSC 035: Data Structures and Algorithms
*/

#include "ioUtils.h"
#include "adjacencyListUndirectedGraph.h"
#include "adts/graph.h"
#include "adts/stlBST.h"

using namespace std;

Dictionary<string, pair<int, int>>* readVertexPositions(string filename) {
    ifstream file(filename);
    string line;
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    Dictionary<string, pair<int, int>>* dictionary =
        new STLBST<string, pair<int, int>>();

    try {
        getline(file, line);
        while (line != "end") {
            string key = line;
            getline(file, line);
            int x = stoi(line);
            getline(file, line);
            int y = stoi(line);
            dictionary->insert(key, pair<int, int>(x, y));
            getline(file, line);
        }
    } catch (std::exception& e) {
        delete dictionary;
        throw;
    }

    return dictionary;
}

Graph<string, int, int>* readRailwayGraph(string filename) {
    ifstream file(filename);
    string line;
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    Graph<string, int, int>* graph =
        new AdjacencyListUndirectedGraph<string, int, int>();

    try {
        getline(file, line);
        while (line != "end") {
            if (line == "vertex") {
                getline(file, line);
                graph->insertVertex(line);
            } else if (line == "edge") {
                string location1;
                getline(file, location1);
                string location2;
                getline(file, location2);
                int weight;
                getline(file, line);
                weight = stoi(line);
                graph->insertEdge(location1, location2, 0, weight);
            } else {
                throw std::runtime_error("Unexpected command: " + line);
            }
            getline(file, line);
        }
    } catch (std::exception& e) {
        delete graph;
        throw;
    }

    return graph;
}
