#pragma once

/*
  Copyright (c) 2023
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, A. Danner, L. Fontes, L. Meeden, Z. Palmer, A. Soni
  Distributed as course material for Spring 2023
  CPSC 035: Data Structures and Algorithms
*/

#include <queue>
#include <stdexcept>
#include <utility>
#include <vector>

using std::pair;
using std::runtime_error;
using std::vector;

#include "priorityQueue.h"

template <typename T, typename U> class FirstGreater {
  public:
    bool operator()(pair<T, U> a, pair<T, U> b);
};

template <typename T, typename U>
bool FirstGreater<T, U>::operator()(pair<T, U> a, pair<T, U> b) {
    return a.first > b.first;
}

/**
 * An implementation of a min-priority queue.  The take and peek methods of this
 * priority queue will return the elements with the lowest priority values
 * first.
 */
template <typename P, typename V>
class STLMinPriorityQueue : public PriorityQueue<P, V> {
  public:
    /**
     * Creates a new, empty min-heap priority queue.
     */
    STLMinPriorityQueue();
    /**
     * Creates a new min-heap priority queue which contains the provided values
     * at their associated priorities.  This constructor heapifies the vector
     * and so runs in O(n) time.
     * @param contents The initial contents of the priority queue.
     */
    STLMinPriorityQueue(vector<P, V> contents);
    ~STLMinPriorityQueue();
    void insert(P priority, V value);
    V remove();
    V peek();
    P peekPriority();
    int getSize();
    bool isEmpty();

  private:
    std::priority_queue<pair<P, V>, vector<pair<P, V>>, FirstGreater<P, V>>*
        actualPriorityQueue;

    // You can safely ignore the following code.  This eliminates some default
    // class routines, preventing you from using them accidentally.
    // Specifically, we are disabling the use of the copy constructor and the
    // copy assignment operator.  You can read more here:
    //   http://www.cplusplus.com/articles/y8hv0pDG/
  private:
    STLMinPriorityQueue(const STLMinPriorityQueue& other) = delete;
    STLMinPriorityQueue& operator=(const STLMinPriorityQueue& other) = delete;
};

template <typename P, typename V>
STLMinPriorityQueue<P, V>::STLMinPriorityQueue() {
    actualPriorityQueue =
        new std::priority_queue<pair<P, V>, vector<pair<P, V>>,
                                FirstGreater<P, V>>();
}

template <typename P, typename V>
STLMinPriorityQueue<P, V>::STLMinPriorityQueue(vector<P, V> contents) {
    actualPriorityQueue =
        new std::priority_queue<pair<P, V>, vector<pair<P, V>>,
                                FirstGreater<P, V>>(contents.begin(),
                                                    contents.end());
}

template <typename P, typename V>
STLMinPriorityQueue<P, V>::~STLMinPriorityQueue() {
    delete actualPriorityQueue;
}

template <typename P, typename V>
void STLMinPriorityQueue<P, V>::insert(P priority, V value) {
    actualPriorityQueue->push(pair<P, V>(priority, value));
}

template <typename P, typename V> V STLMinPriorityQueue<P, V>::remove() {
    if (actualPriorityQueue->empty()) {
        throw runtime_error("STLMinPriorityQueue::remove(): empty prio queue");
    }
    V v = actualPriorityQueue->top().second;
    actualPriorityQueue->pop();
    return v;
}

template <typename P, typename V> V STLMinPriorityQueue<P, V>::peek() {
    if (actualPriorityQueue->empty()) {
        throw runtime_error("STLMinPriorityQueue::peek(): empty prio queue");
    }
    return actualPriorityQueue->top().second;
}

template <typename P, typename V> P STLMinPriorityQueue<P, V>::peekPriority() {
    if (actualPriorityQueue->empty()) {
        throw runtime_error(
            "STLMinPriorityQueue::peekPriority(): empty prio queue");
    }
    return actualPriorityQueue->top().first;
}

template <typename P, typename V> int STLMinPriorityQueue<P, V>::getSize() {
    return actualPriorityQueue->size();
}

template <typename P, typename V> bool STLMinPriorityQueue<P, V>::isEmpty() {
    return actualPriorityQueue->empty();
}
