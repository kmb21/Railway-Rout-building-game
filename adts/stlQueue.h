#pragma once

#include <queue>
#include <stdexcept>

#include "queue.h"

using std::runtime_error;
using std::queue;

template <typename T> class STLQueue : public Queue<T> {
  public:
    void enqueue(T element);
    T dequeue();
    int getSize();
    bool isEmpty();
    T getFront();

    void insert(T element);
    T remove();
    T peek();

  private:
    queue<T> actualQueue;
};

template <typename T> void STLQueue<T>::enqueue(T element) {
    actualQueue.push(element);
}

template <typename T> T STLQueue<T>::dequeue() {
    if (actualQueue.empty()) {
        throw runtime_error("dequeue: empty queue");
    }
    T value = actualQueue.front();
    actualQueue.pop();
    return value;
}

template <typename T> int STLQueue<T>::getSize() {
    return actualQueue.size();
}

template <typename T> bool STLQueue<T>::isEmpty() {
    return actualQueue.empty();
}

template <typename T> void STLQueue<T>::insert(T element) {
    this->enqueue(element);
}

template <typename T> T STLQueue<T>::remove() {
    return this->dequeue();
}

template <typename T> T STLQueue<T>::peek() {
    if (actualQueue.empty()) {
        throw runtime_error("peek: empty queue");
    }
    return actualQueue.front();
}
