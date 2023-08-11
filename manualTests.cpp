/*
  Copyright (c) 2023
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, A. Danner, L. Fontes, L. Meeden, Z. Palmer, A. Soni
  Distributed as course material for Spring 2023
  CPSC 035: Data Structures and Algorithms
*/

#include <string>
#include <algorithm>
#include <fstream>

#include <string>
#include <vector>
#include <iostream>
#include <UnitTest++/UnitTest++.h>

#include "adjacencyListGraph.h"
#include "adjacencyListUndirectedGraph.h"
#include "adts/dictionary.h"
#include "adts/graph.h"
#include "graphAlgorithms.h"
#include "ioUtils.h"
#include "player.h"
#include "railwayGame.h"


using namespace std;


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



int main(int argc, char** argv) {
    // You can use this main to experiment with the code you have written
    string p= "hello";
    string q= "hey";
    string s= "true";
    Graph<string, int, int>* graph = new AdjacencyListUndirectedGraph<string, int, int>();
    graph->insertVertex(p);
    graph->insertVertex(q);
    graph->insertVertex(s);
    graph->insertEdge(p,q, 2, 3);
    graph->insertEdge(p,s, 3, 4);
    graph->insertEdge(q,s, 4, 5);
    

    Player* player1 = new Player(1);
    RailwayGame* game = new RailwayGame();
    player1->goals= game->makeGoal(player1->goals, graph);
    cout<<player1->goals.size()<<endl;
    for(int i= 0; i<player1->goals.size(); i++){
 
        cout<< player1->goals[i]->getMessage()<<endl;
        cout<< player1->goals[i]->getLocation(1)<<endl;
         cout<< player1->goals[i]->getLocation(2)<<endl;
    }
    delete graph;
    return 0;
}
