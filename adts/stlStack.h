#pragma once

/*
  Copyright (c) 2023
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, A. Danner, L. Fontes, L. Meeden, Z. Palmer, A. Soni
  Distributed as course material for Spring 2023
  CPSC 035: Data Structures and Algorithms
*/

#include <stack>
#include <stdexcept>

#include "stack.h"

using std::runtime_error;
using std::stack;

template <typename T> class STLStack : public Stack<T> {
  public:
    void push(T element);
    T pop();
    int getSize();
    bool isEmpty();
    T getTop();

    void insert(T element);
    T remove();
    T peek();

  private:
    stack<T> actualStack;
};

template <typename T> void STLStack<T>::push(T element) {
    actualStack.push(element);
}

template <typename T> T STLStack<T>::pop() {
    if (actualStack.empty()) {
        throw runtime_error("pop: empty stack");
    }
    T value = actualStack.top();
    actualStack.pop();
    return value;
}

template <typename T> int STLStack<T>::getSize() {
    return actualStack.size();
}

template <typename T> bool STLStack<T>::isEmpty() {
    return actualStack.empty();
}

template <typename T> void STLStack<T>::insert(T element) {
    this->push(element);
}

template <typename T> T STLStack<T>::remove() {
    return this->pop();
}

template <typename T> T STLStack<T>::peek() {
    if (actualStack.empty()) {
        throw runtime_error("peek: empty stack");
    }
    return actualStack.top();
}
