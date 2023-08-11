/*
  Copyright (c) 2023
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, A. Danner, L. Fontes, L. Meeden, Z. Palmer, A. Soni
  Distributed as course material for Spring 2023
  CPSC 035: Data Structures and Algorithms
*/


#pragma once
#include <string>
#include "adts/graph.h"
#include "adts/edge.h"
#include "goal.h"
#include "player.h"
#include<stdexcept>
#include "graphAlgorithms.h"




using namespace std;

/**
 * An instance of this class represents a single game of Railway.  An object of
 * type RailwayGame does not represent the user interface, but does represent
 * the idea of a game of Railway, including the state of the board and all of
 * the information pertaining to both players.  It also includes the logic for
 * making moves in the game and enforces the game's rules.
 */

class RailwayGame {
  public:

    RailwayGame();
    ~RailwayGame();// to be deleted

    /**
    creates goals for the game
    *@param graph(Graph) of game
    *@param goals(Dictionary)
    returns a vector of goals 
    */
    vector<Goal*> makeGoal(vector<Goal*> goals, Graph<string, int, int>* graph);
    /**
    updates the player score, tracks and goal possibility
    *@param graph(Graph) of game
    *@param myplayer(Player) player whose turn it is
    *@param move(vector)
    returns none
    */
    void updatePlayerAttributes(Player* myplayer, Graph<string, int, int>* our_graph, 
      vector<string> move);// changes scores and tracks; we need to call checkGoalPos

    /**
     checks if edge clicked by user is possible/appropriate
     *@param graph Graph of game
     *@param player1(Player) Player whose turn it is
     *@param player2(Player) opponent of player1
     *@param move_vector(Vector) a vector storing source and destination of edge clicked by player
     returns a pair of boolean value and a string message indicating if the move is appropriate
    */

    pair<bool,string> checkMovement(Graph<string, int, int>* graph, vector<string> move_vector, 
      Player* current_player, Player* player2);


    /**
    updates the player score, tracks and goal possibility
    *@param current_player Player whose turn it is to play game
    *@param player2 opponent of current_player
    *@param graphCopy(Graph) copy of game graph
    returns none
    */
    void isImpossible(Player* current_player, Player* player2, Graph<string, int, int>* graphCopy);
    /**
     Checks if the game is over based on certain edge cases
     *@param player1(Player) Player whose turn it is
     *@param player2(Player) opponent of player1
     *@param graph Graph of game
     returns true if game is finish, false otherwise
    */
    bool gameFinish(Player* player1, Player* player2, vector<string> move, Graph<string, int, int>* graph);

    
    // TODO: write your RailwayGame constructor and method declarations here



    // TODO: write your RailwayGame fields here
    // You can safely ignore the following code.  This eliminates some default
    // class routines, preventing you from using them accidentally.
    // Specifically, we are disabling the use of the copy constructor and the
    // copy assignment operator.  You can read more here:
    //   http://www.cplusplus.com/articles/y8hv0pDG/
    RailwayGame(const RailwayGame& game) = delete;
    RailwayGame& operator=(const RailwayGame& game) = delete;
};
