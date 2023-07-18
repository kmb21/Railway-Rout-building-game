/*
  Copyright (c) 2023
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, A. Danner, L. Fontes, L. Meeden, Z. Palmer, A. Soni
  Distributed as course material for Spring 2023
  CPSC 035: Data Structures and Algorithms
*/

#pragma once

// Example of communication with a subprocess via stdin/stdout
// Original Author: Konstantin Tretyakov
// License: MIT
// https://gist.github.com/konstantint/d49ab683b978b3d74172

#include <exception>
#include <ext/stdio_filebuf.h> // NB: Specific to libstdc++
#include <iostream>
#include <memory>
#include <sys/wait.h>
#include <unistd.h>

// Wrapping pipe in a class makes sure they are closed when we leave scope
class cpipe {
  private:
    int fd[2];

  public:
    cpipe();
    ~cpipe();
    const int read_fd() const;
    const int write_fd() const;
    void close();
};
