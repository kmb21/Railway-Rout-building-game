
#include "player.h"

Player :: Player(int num){
    this->score = 0;
    this->playernum = num;
    this->playerGraph = new AdjacencyListUndirectedGraph<string, int, int>();
    if (num == 1){
        this->tracks = 35;
        this->message =  "Player 1 it is your turn";
    }
    else{
        this->tracks = 50;
        this->message = "Player 2 it is your turn";
    }
}


Player :: ~Player(){
    delete this->playerGraph;
    this->playerGraph = nullptr;
}
int Player :: getPlayernum(){
    return this->playernum;
}

int Player :: getPlayerScore(){
    return this->score;
}

int Player :: getPlayerTrack(){
    return this->tracks;
}

void Player :: setPlayerScore(int new_score){
    this->score = new_score;
}

void Player :: setPlayerTracks(int new_tracks){
    this->tracks = new_tracks;
}

string Player :: getMessage(){
   return this->message;
}

void Player :: setMessage(string message){
    this->message = message;
}
