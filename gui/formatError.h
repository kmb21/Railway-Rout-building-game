/*
  Copyright (c) 2023
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, A. Danner, L. Fontes, L. Meeden, Z. Palmer, A. Soni
  Distributed as course material for Spring 2023
  CPSC 035: Data Structures and Algorithms
*/

#pragma once

#include "guiFailure.h"

class FormatError : public GuiFailure {
  public:
    explicit FormatError(const char* message) : GuiFailure(message) {
    }
    explicit FormatError(std::string& message) : GuiFailure(message) {
    }
    virtual ~FormatError() throw() {
    }
};
