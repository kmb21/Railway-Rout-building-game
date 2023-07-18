/*
  Copyright (c) 2023
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, A. Danner, L. Fontes, L. Meeden, Z. Palmer, A. Soni
  Distributed as course material for Spring 2023
  CPSC 035: Data Structures and Algorithms
*/

#pragma once
/* Copyright (c) 2017
   Swarthmore College Computer Science Department, Swarthmore PA
   A. Danner, M. Gagne, J. Brody, Z. Palmer, A. Soni
   Distributed as course material for Fall 2017
   CPSC 035: Data Structures and Algorithms
*/

#include <exception>
#include <ext/stdio_filebuf.h> // NB: Specific to libstdc++
#include <iostream>
#include <memory>
#include <sys/wait.h>
#include <unistd.h>

#include "cpipe.h"

// Example of communication with a subprocess via stdin/stdout
// Original Author: Konstantin Tretyakov
// License: MIT
// https://gist.github.com/konstantint/d49ab683b978b3d74172

class Subprocess {
  public:
    Subprocess(const char* const argv[], bool with_path = false,
               const char* const envp[] = 0);

    void sendEOF();
    int wait();
    void kill();

    int child_pid = -1;
    std::unique_ptr<__gnu_cxx::stdio_filebuf<char>> write_buf = NULL;
    std::unique_ptr<__gnu_cxx::stdio_filebuf<char>> read_buf = NULL;
    std::ostream stdin;
    std::istream stdout;

  private:
    cpipe write_pipe;
    cpipe read_pipe;

    Subprocess(const Subprocess& other) = delete;
    Subprocess& operator=(const Subprocess& other) = delete;
};
