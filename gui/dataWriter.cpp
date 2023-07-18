/*
  Copyright (c) 2023
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, A. Danner, L. Fontes, L. Meeden, Z. Palmer, A. Soni
  Distributed as course material for Spring 2023
  CPSC 035: Data Structures and Algorithms
*/

#include <functional>
#include <ostream>
#include <string>
#include <utility>
#include <vector>

#include "../adts/dictionary.h"
#include "../adts/edge.h"
#include "../adts/graph.h"
#include "../adts/list.h"
#include "dataWriter.h"

using namespace std;

DataWriter::DataWriter(ostream& output, bool debug) : output(output) {
    this->debug = debug;
    output.exceptions(std::ostream::failbit | std::ostream::badbit);
}

void DataWriter::writeCharToStream(char c) {
    output << c;
    if (debug) {
        cerr << "sent: " << c << endl;
    }
}

void DataWriter::writeStringToStream(string s) {
    output << s;
    if (debug) {
        cerr << "sent: " << s << endl;
    }
}

void DataWriter::flushStream() {
    output.flush();
}

void DataWriter::writeInt(int i) {
    writeCharToStream('i');
    writeStringToStream(to_string(i));
    writeCharToStream('$');
}

void DataWriter::writeString(string s) {
    writeCharToStream('s');
    writeInt(s.length());
    writeStringToStream(s);
    writeCharToStream('$');
}
