#pragma once
#include <string>

#include <stdexcept>

using namespace std;

#include "adjacencyListUndirectedGraph.h"
#include "goal.h"


class Player {

    public:
        
        Player(int num);
        ~Player();
        int getPlayernum();
        int getPlayerScore();
        int getPlayerTrack();
        void setPlayerScore(int newScore);
        void setPlayerTracks(int newTracks);
        AdjacencyListGraph<string, int, int>* playerGraph;
        vector<Goal*> goals;
        string getMessage();


        void setMessage(string message);
   
        

    private:
        
        int playernum;
        int score;
        int tracks;
        string message;
        


};