/*
  Copyright (c) 2023
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, A. Danner, L. Fontes, L. Meeden, Z. Palmer, A. Soni
  Distributed as course material for Spring 2023
  CPSC 035: Data Structures and Algorithms
*/

#include "cpipe.h"
#include "guiFailure.h"

cpipe::cpipe() {
    if (pipe(fd) != 0) {
        throw GuiFailure("Failed to create pipe");
    }
}

cpipe::~cpipe() {
    this->close();
}

const int cpipe::read_fd() const {
    return fd[0];
}

const int cpipe::write_fd() const {
    return fd[1];
}

void cpipe::close() {
    ::close(fd[0]);
    ::close(fd[1]);
}
