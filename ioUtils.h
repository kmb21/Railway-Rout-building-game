/*
  Copyright (c) 2023
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, A. Danner, L. Fontes, L. Meeden, Z. Palmer, A. Soni
  Distributed as course material for Spring 2023
  CPSC 035: Data Structures and Algorithms
*/

#pragma once

#include <fstream>
#include <iostream>
#include <stdexcept>



#include "adts/dictionary.h"
#include "adts/edge.h"
#include "adts/graph.h"

using std::string;

/**
 * Reads a vertex position map from the specified file.
 * @param filename The file to read.
 * @return A pointer to a dictionary containing the vertex positions.  The
 *         caller becomes the owner of this memory.
 * @throws std::exception If an I/O error occurs.
 */
Dictionary<string, std::pair<int, int>>* readVertexPositions(string filename);

/**
 * Reads a Railway graph from the specified file.  The owner for all edges is
 * set to 0 (no owner).
 * @param filename The file to read.
 * @return A pointer to the graph which was loaded.  The caller becomes the
 *         owner of this memory.
 * @throws std::exception If an I/O error occurs.
 */
Graph<string, int, int>* readRailwayGraph(string filename);
