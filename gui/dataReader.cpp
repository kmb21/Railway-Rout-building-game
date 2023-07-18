/*
  Copyright (c) 2023
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, A. Danner, L. Fontes, L. Meeden, Z. Palmer, A. Soni
  Distributed as course material for Spring 2023
  CPSC 035: Data Structures and Algorithms
*/

#include <functional>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "dataReader.h"
#include "formatError.h"

using namespace std;

DataReader::DataReader(istream& input, bool debug) : input(input) {
    this->debug = debug;
    input >> noskipws;
    input.exceptions(std::istream::failbit | std::istream::badbit);
}

char DataReader::readCharFromStream() {
    char c;
    input >> c;
    if (this->debug) {
        cerr << "received: " << c;
    }
    return c;
}

void DataReader::requireCharFromStream(char c, string message) {
    if (readCharFromStream() != c) {
        string message = string("Expected character ") + c;
        throw FormatError(message);
    }
}

int DataReader::readInt() {
    requireCharFromStream('i', "Expected integer");
    string s;
    char c = readCharFromStream();
    if (c == '-') {
        s += c;
        c = readCharFromStream();
    }
    while (c >= '0' && c <= '9') {
        s += c;
        c = readCharFromStream();
    }
    if (c != '$') {
        throw FormatError("Expected $ terminator for integer");
    }
    return stoi(s);
}

string DataReader::readString() {
    requireCharFromStream('s', "Expected string");
    int length = readInt();
    string s;
    for (int i = 0; i < length; i++) {
        s += readCharFromStream();
    }
    requireCharFromStream('$', "Expected $ terminator for string");
    return s;
}
