#pragma once

/*
  Copyright (c) 2023
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, A. Danner, L. Fontes, L. Meeden, Z. Palmer, A. Soni
  Distributed as course material for Spring 2023
  CPSC 035: Data Structures and Algorithms
*/

// This module contains a helper function to standardize error message
// generation in template classes.

#include <string>

namespace cs35 {
    template <typename T>
    std::string to_string(T t) {
        return std::to_string(t);
    }

    std::string to_string(std::string s);
}
