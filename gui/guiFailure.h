/*
  Copyright (c) 2023
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, A. Danner, L. Fontes, L. Meeden, Z. Palmer, A. Soni
  Distributed as course material for Spring 2023
  CPSC 035: Data Structures and Algorithms
*/

#pragma once

#include <stdexcept>
#include <string>

class GuiFailure : public std::runtime_error {
  public:
    explicit GuiFailure(const char* message) : std::runtime_error(message) {
    }
    explicit GuiFailure(std::string& message) : std::runtime_error(message) {
    }
    virtual ~GuiFailure() throw() {
    }
};
