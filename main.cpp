/*
  Copyright (c) 2023
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, A. Danner, L. Fontes, L. Meeden, Z. Palmer, A. Soni
  Distributed as course material for Spring 2023
  CPSC 035: Data Structures and Algorithms
*/

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>

#include "ioUtils.h"
#include "railwayGUI.h"
#include "railwayGame.h"


using namespace std;

int main(int argc, char** argv) {
    // Check command line arguments and give up if necessary.
    if (argc != 2) {
        cerr << "Expected one argument:" << endl;
        cerr << "  Base filename of map data" << endl;
        cerr << "  e.g., test_data/Europe " << endl;
        return 1;
    }

    // Initialize randomizer.  This should happen before any random numbers are
    // selected.
    srand(time(nullptr));

    // Get command-line arguments.
    string baseName(argv[1]);
    string graphDataFilename = baseName + "_graphData.txt";
    string vertexPositionFilename = baseName + "_vertexPositions.txt";
    string backgroundImageFilename = baseName + "_background.png";

    // Retrieve vertex positions (so we know where each vertex goes on the map).
    Dictionary<string, pair<int, int>>* vertexPositions;
    try {
        vertexPositions = readVertexPositions(vertexPositionFilename);
    } catch (exception e) {
        cout << "Could not read vertex positions file "
             << vertexPositionFilename << ": " << e.what() << endl;
        return 1;
    }

    // Load the initial graph.
    Graph<string, int, int>* graph;
    Graph<string, int, int>* graphcopy1;
    Graph<string, int, int>* graphcopy2;
    try {
        graph = readRailwayGraph(graphDataFilename);
        graphcopy1 = readRailwayGraph(graphDataFilename);//make copy of graph to use in impossible
        graphcopy2 = readRailwayGraph(graphDataFilename);
    } catch (exception e) {
        cout << "Could not read graph data file " << graphDataFilename << ": "
             << e.what() << endl;
        delete vertexPositions;
        return 1;
    }

    // Create the GUI object here.  This is statically allocated, so the GUI
    // will disappear the moment your program leaves the main function.
    // The GUI object should only be used by main, and not by any other function
    // or object.
    RailwayGUI gui(backgroundImageFilename, vertexPositions);

    // Tell the GUI about the graph we have.
    gui.updateRailwayMap(graph);

    // TODO: Write code that runs the game.  You'll want to write most of your
    // game logic into the RailwayGame class and then use an object of that type
    // here to control the game and relay what it says to the GUI.  This
    // assignment is more open-ended than the previous assignments.

    // TODO: Delete the following code.  It's just here at the start of the
    // assignment to make sure that you can see what the GUI looks like.  If we
    // didn't do something here (like wait for the user to press enter on the
    // console), then the main function would stop and the GUI would instantly
    // vanish.
    Player* player1 = new Player(1);
    Player* player2 = new Player(2);
    Player* currplayer;
    Player* otherplayer;
    RailwayGame* game = new RailwayGame();
    int turn = 0;
    pair<bool, string> appropriate;
    vector<string> playermove;
    //Fix the game message when player is out of tracks. It currently prints warning message and next player's turn.
    player1->goals= game->makeGoal(player1->goals, graph);
    gui.updatePlayerStatus(player1->getPlayernum(), player1->getPlayerScore(), 
        player1->getPlayerTrack(),player1->goals);   
    player2->goals= game->makeGoal(player2->goals, graph);
    gui.updatePlayerStatus(player2->getPlayernum(), player2->getPlayerScore(), 
        player2->getPlayerTrack(),player2->goals);
          
    gui.updateMessage("Player1: it is your turn");
    playermove = gui.getNextMove();
    bool off= game->gameFinish(player1, player2,playermove,graph);
    
    while (!off){
         if( playermove[0] == "close"){
            return 0;
        }
        
        if(turn%2== 0){
            currplayer = player1;
            otherplayer = player2;
            game->isImpossible(currplayer, otherplayer, graphcopy1);
        }else{
            currplayer = player2;
            otherplayer = player1;
            game->isImpossible(currplayer, otherplayer, graphcopy2);
        }
        
        appropriate = game->checkMovement(graph, playermove, currplayer, otherplayer);
        
        
        // if (playermove[0]!="pass"){
        //     Edge<string, int, int> moveEdge = graph->getEdge(playermove[1], playermove[2]);
        //     if (moveEdge.getWeight() > currplayer->getPlayerTrack()){
        //         gui.updateMessage(appropriate.second);
        //     }
        // }
        gui.updateMessage(appropriate.second);
        if (appropriate.first || playermove[0] == "pass"){

            game->updatePlayerAttributes(currplayer, graph, playermove);
            
            gui.updatePlayerStatus(currplayer->getPlayernum(), currplayer->getPlayerScore(), 
                currplayer->getPlayerTrack(),currplayer->goals);
            
            gui.updateRailwayMap(graph);
            turn++;
           
        }
        playermove = gui.getNextMove();
        off= game->gameFinish(player1, player2,playermove,graph);

    }
   
    
    if (player1->getPlayerScore()>player2->getPlayerScore()){
        gui.updateMessage("Player 1 has won the game");
    }else{
        gui.updateMessage("Player 2 has won the game");
    }
    gui.getNextMove();

    // Finally, clean up and exit successfully.
    delete player1;
    delete player2;
    delete currplayer;
    delete otherplayer;
    delete graphcopy1;
    delete graphcopy2;
    delete game;
    delete graph;
    delete vertexPositions;
    return 0;
}
