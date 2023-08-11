/*
  Copyright (c) 2023
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, A. Danner, L. Fontes, L. Meeden, Z. Palmer, A. Soni
  Distributed as course material for Spring 2023
  CPSC 035: Data Structures and Algorithms
*/


#include <string>

#include "railwayGame.h"


using namespace std;


//Pseudo code will be adjusted during implementation

RailwayGame :: RailwayGame(){
  //Constructor of class
}

RailwayGame :: ~RailwayGame(){
  //Destructor of class

}


vector<Goal*> RailwayGame :: makeGoal(vector<Goal*> goals, Graph<string, int, int>* graph){
  /*
  **use dijktra's algorithm make points for goal**
  Pseudocode:
  Get vertices of the graph
  While size of goals vector is less than three
  Get two random vertices
  Check with reachable DFS
  Add to goals if not in goals and if reachable
  Call updatePlayerStatus
  */
  int rand1;
  int rand2;
  Dictionary<string, int>* sssp;
  int points;
  string message;
  Goal* goal;
  Goal* temp; 
  vector<string> graphVert = graph->getVertices();
  while (goals.size()<3){
    rand1 = rand() % (graphVert.size()-1);
    rand2 = rand() % (graphVert.size()-1);
    vector<string> path = shortestLengthPathBFS(graphVert[rand1], graphVert[rand2], graph);
    if (graphVert[rand1] != graphVert[rand2] && path.size()>2){
      if (reachableDFS(graphVert[rand1], graphVert[rand2], graph)){
        //get points, make goal and add to vector
        sssp = singleSourceShortestPath(graphVert[rand1], graph);
        points = sssp->get(graphVert[rand2])/4;
        message = to_string(points) + " points";
        goal = new Goal(graphVert[rand1], graphVert[rand2], message);
        bool check= true;
        for(int i= 0; i<goals.size(); i++){
          temp = new Goal(graphVert[rand2], graphVert[rand1], message);
          if ((goals[i]->getLocation(1) == goal->getLocation(1) && goals[i]->getLocation(2) == goal->getLocation(2))||
           (goals[i]->getLocation(1) == temp->getLocation(1) && goals[i]->getLocation(2) == temp->getLocation(2))){
            check= false;
          }
        }
        if(check){
          goals.push_back(goal);
        }
      
      }
    }
  }
  delete temp;
  delete sssp;
  temp = nullptr;
  sssp = nullptr;
  return goals;
}

void RailwayGame :: updatePlayerAttributes(Player* myplayer, 
    Graph<string, int, int>* our_graph,vector<string> move){
        // changes scores and tracks; we need to call checkGoalPos
  /*
  
   
  Pseducode: 
      check move using checkMovement and if true
        update gui color(make copy of graph and update edge)current_player->getPlayerTrack() - moveEdge.getWeight()
      else
        update player's message
        call recursively to get another move

  else if vector contains pass
    if tracks is 0
      update tracks
  

  */
  
  if(move[0]=="pass"){
    myplayer->setPlayerTracks(myplayer->getPlayerTrack() + myplayer-> playerGraph->getVertices().size());
    return;
  }
  
  string source= move[1];
  string dest= move[2];
  Dictionary<string, int>* sssp;
  int points;
  
  Edge<string, int, int> moveEdge = our_graph->getEdge(source, dest);
  
  myplayer->setPlayerTracks(myplayer->getPlayerTrack() - moveEdge.getWeight());
  myplayer->playerGraph->insertVertex(source);
  myplayer->playerGraph->insertVertex(dest);
  our_graph->removeEdge(source, dest);

  our_graph->insertEdge(source, dest, myplayer->getPlayernum(), moveEdge.getWeight());

  myplayer->playerGraph->insertEdge(source, dest, myplayer->getPlayernum(), moveEdge.getWeight());


  for (int i =0; i<3;i++){
  
    if ((myplayer->playerGraph->containsVertex(myplayer->goals[i]->getLocation(1)) &&
       myplayer->playerGraph->containsVertex(myplayer->goals[i]->getLocation(2)))
        ){

      string loc1 = myplayer->goals[i]->getLocation(1);
      string loc2 = myplayer->goals[i]->getLocation(2);
      myplayer->goals.erase(myplayer->goals.begin() + i, myplayer->goals.begin() + i + 1);
      string message = "completed";
      Goal* newGoal = new Goal(loc1, loc2, message);

      myplayer->goals.push_back(newGoal);
      sssp = singleSourceShortestPath(myplayer->goals[i]->getLocation(1), our_graph);
      points = sssp->get(myplayer->goals[i]->getLocation(2))/4;
      myplayer->setPlayerScore(points + myplayer->getPlayerScore()+ myplayer->playerGraph->getVertices().size());

  }


  }


}

pair<bool,string> RailwayGame :: checkMovement(Graph<string, int, int>* graph, vector<string> move_vector, 
Player* current_player, Player* player2){
  
  if (move_vector[0] == "pass"){
      string message = "Player " +  to_string(player2-> getPlayernum()) + ": it is your turn";
      return pair<bool, string> (true,message);
    }

  if (move_vector.size()>1){

    string source= move_vector[1];
    string dest= move_vector[2];


    if ( current_player->playerGraph->containsEdge(source, dest) || player2->playerGraph->containsEdge(source, dest)){
      string message = "Player " + to_string(current_player->getPlayernum()) + ": that route has already been taken";
      return pair<bool, string> (false,message);
    }

    if(current_player->playerGraph->getVertices().size()== 0){
      string message = "Player " +  to_string(player2-> getPlayernum()) + ": it is your turn";
      return pair<bool, string> (true,message);
    }

    Edge<string, int, int> moveEdge = graph->getEdge(move_vector[1], move_vector[2]);
    int newtrack = current_player->getPlayerTrack() - moveEdge.getWeight();
    if (newtrack < 0){
      
      string message =  "Player " + to_string(current_player->getPlayernum()) + ": You are out of tracks";
      return pair<bool, string> (false,message);
    }

    vector<Edge<string, int, int>> my_vector = graph->getIncomingEdges(source);
    vector<Edge<string, int, int>> my_vector2 = graph->getOutgoingEdges(dest);
    my_vector.insert(my_vector.end(), my_vector2.begin(), my_vector2.end());
    



    for(int i= 0; i< my_vector.size(); i++){

      string start = my_vector[i].getSource();
      string end = my_vector[i].getDestination();

      if (current_player->playerGraph->containsEdge(start, end)){
        string message = "Player " +  to_string(player2-> getPlayernum()) + ": it is your turn";
        return pair<bool, string> (true,message);
      }
    }
  }
  string message = "Player " +  to_string(current_player->getPlayernum()) + ": you have tapped on a track that is not connected to your tracks";
  return pair<bool, string> (false,message);

}

void RailwayGame :: isImpossible(Player* currplayer, Player* otherplayer, Graph<string, int, int>* graphCopy){
  /*
  remove all of other players edges from graphCopy if it contains the edge
  for each goal of currplayer
    get reachableDFS of its src and dest on the graph copy.
    if false:
      make new goal and change message

  */
  vector<Goal*> currGoals = currplayer->goals;
  vector<Edge<string, int, int>> opponentEdges = otherplayer->playerGraph->getEdges();
  for (int i = 0; i<opponentEdges.size(); i++){
    if (graphCopy->containsEdge(opponentEdges[i].getSource(), opponentEdges[i].getDestination())){
      graphCopy->removeEdge(opponentEdges[i].getSource(), opponentEdges[i].getDestination());
    }
  }
  for (int j=0; j<currGoals.size(); j++){
    string src = currGoals[j]->getLocation(1);
    string dest = currGoals[j]->getLocation(2);
    bool possible = reachableDFS(src, dest, graphCopy);
    if (!possible){
      currplayer->goals.erase(currplayer->goals.begin() + j, currplayer->goals.begin() + j + 1);
      string message = "impossible";
      Goal* newGoal = new Goal(src, dest, message);

      currplayer->goals.push_back(newGoal);
    }
  }
  
}

bool RailwayGame :: gameFinish(Player* player1, Player* player2,vector<string> move, Graph<string, int, int>* our_graph){
  /*
    Pseudocode:
      if move contains close 
        return true
      if all goals are completed
        return true
      if its not possible to use individual tracks to complete any individual goals
        return true
      if all tracks are claimed
        return true
  */
  bool finish;
  int graphSize = our_graph->getEdges().size();
  int p1GraphSize = player1->playerGraph->getEdges().size();
  int p2GraphSize = player2->playerGraph->getEdges().size();
  if (graphSize == (p1GraphSize + p2GraphSize)){
    return true;
  }
  vector<Goal*> goals1 = player1->goals;
  vector<Goal*> goals2 = player2->goals; 
  for (int i = 0; i<3; i++){
    if (goals1[i]->getMessage() == "completed" && goals2[i]->getMessage() == "completed"){
      finish = true;
    }
    else if (goals1[i]->getMessage() == "impossible" && goals2[i]->getMessage() == "impossible"){
      finish = true;
    }
    else if (goals1[i]->getMessage() == "impossible" && goals2[i]->getMessage() == "completed"){
      finish = true;
    }
    else if (goals1[i]->getMessage() == "completed" && goals2[i]->getMessage() == "impossible"){
      finish = true;
    }
    else{
      return false;
    }

  }
 
  return finish;
}


                                                      
// TODO: implement your RailwayGame class constructor and methods here
