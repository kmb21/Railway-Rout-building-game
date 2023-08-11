/*
  Copyright (c) 2023
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, A. Danner, L. Fontes, L. Meeden, Z. Palmer, A. Soni
  Distributed as course material for Spring 2023
  CPSC 035: Data Structures and Algorithms
*/

#pragma once

#include <string>

using std::string;


class Goal {
  public:
    /* Create a new game goal between two vertices on the map
     * @param location1 label of first vertex
     * @param location2 label of second vertex
     * @param message message to display in GUI window for goal
     */
    Goal(string location1, string location2, string message);

    /* Get one of the two end vertices of the goal
     * @param val must be 1 or 2 to get Location1 or location2
     * throws runtime_error if val is not 1 or 2
     */
    string getLocation(int val);

    /* Get the message to display in GUI */
    string getMessage() {
        return this->message;
    }

  private:
    /** One of the locations in the objective. */
    string location1;
    /** The other location in the objective. */
    string location2;
    /** A message describing the state of the objective. */
    string message;

    // You can safely ignore the following code.  This eliminates some default
    // class routines, preventing you from using them accidentally.
    // Specifically, we are disabling the use of the copy constructor and the
    // copy assignment operator.  You can read more here:
    //   http://www.cplusplus.com/articles/y8hv0pDG/
    Goal(const Goal& goal) = delete;
    Goal& operator=(const Goal& goal) = delete;
};
