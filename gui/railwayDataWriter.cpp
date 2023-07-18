/*
  Copyright (c) 2023
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, A. Danner, L. Fontes, L. Meeden, Z. Palmer, A. Soni
  Distributed as course material for Spring 2023
  CPSC 035: Data Structures and Algorithms
*/

#include "railwayDataWriter.h"

using namespace std;

RailwayDataWriter::RailwayDataWriter(ostream& output, bool debug)
    : DataWriter(output, debug) {
}

void RailwayDataWriter::writeOwner(int owner) {
    writeInt(owner);
}

void RailwayDataWriter::writePoint(std::pair<int, int> point) {
    writePair<int, int>(point, [&](int x) -> void { return writeInt(x); },
                        [&](int x) -> void { return writeInt(x); });
}

void RailwayDataWriter::writeGoal(Goal* goal) {
    writeCharToStream('O');
    writeString("Goal");
    writeString(goal->getLocation(1));
    writeString(goal->getLocation(2));
    writeString(goal->getMessage());
    writeCharToStream('$');
}

void RailwayDataWriter::writePlayerState(int playerNumber, int score,
                                         int tracks, vector<Goal*> goals) {
    writeCharToStream('M');
    writeString("playerState");
    // Writing a RailwayPlayer object inline; didn't want to have to model it
    // for the students directly.
    writeCharToStream('O');
    writeString("RailwayPlayer");
    writeInt(score);
    writeInt(tracks);
    writeVector<Goal*>(goals, [&](Goal* g) -> void { writeGoal(g); });
    writeCharToStream('$');
    writeInt(playerNumber);
    writeCharToStream('$');
    flushStream();
}

void RailwayDataWriter::writeGameMessage(std::string gameMessage) {
    writeCharToStream('M');
    writeString("gameMessage");
    writeString(gameMessage);
    writeCharToStream('$');
    flushStream();
}

void RailwayDataWriter::writeRailwayGraph(Graph<string, int, int>* graph) {
    writeCharToStream('M');
    writeString("graph");
    writeGraph<string, int, int>(graph,
                                 [&](string vertex) { writeString(vertex); },
                                 [&](int owner) { writeOwner(owner); },
                                 [&](int weight) { writeInt(weight); });
    writeCharToStream('$');
    flushStream();
}

void RailwayDataWriter::writeVertexPositions(
    Dictionary<string, pair<int, int>>* positions) {
    writeCharToStream('M');
    writeString("vertexPositions");
    writeDictionary<string, pair<int, int>>(
        positions, [&](string key) { writeString(key); },
        [&](pair<int, int> value) {
            writePair<int, int>(value, [&](int n) { writeInt(n); },
                                [&](int n) { writeInt(n); });
        });
    writeCharToStream('$');
    flushStream();
}
