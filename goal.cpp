/*
  Copyright (c) 2023
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, A. Danner, L. Fontes, L. Meeden, Z. Palmer, A. Soni
  Distributed as course material for Spring 2023
  CPSC 035: Data Structures and Algorithms
*/

#include "goal.h"
#include <stdexcept>

using namespace std;

Goal::Goal(string location1, string location2, string message) {
    this->location1 = location1;
    this->location2 = location2;
    this->message = message;
}

string Goal::getLocation(int val) {
    if (val == 1) {
        return this->location1;
    } else if (val == 2) {
        return this->location2;
    }
    throw runtime_error("Goal::getLocation invalid index");
}
