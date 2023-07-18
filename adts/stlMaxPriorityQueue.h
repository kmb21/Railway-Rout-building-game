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

template <typename T, typename U> class FirstLess {
  public:
    bool operator()(pair<T, U> a, pair<T, U> b);
};

template <typename T, typename U>
bool FirstLess<T, U>::operator()(pair<T, U> a, pair<T, U> b) {
    return a.first < b.first;
}

/**
 * An implementation of a max-priority queue.  The take and peek methods of this
 * priority queue will return the elements with the highest priority values
 * first.
 */
template <typename P, typename V>
class STLMaxPriorityQueue : public PriorityQueue<P, V> {
  public:
    /**
     * Creates a new, empty max-heap priority queue.
     */
    STLMaxPriorityQueue();
    /**
     * Creates a new max-heap priority queue which contains the provided values
     * at their associated priorities.  This constructor heapifies the vector
     * and so runs in O(n) time.
     * @param contents The initial contents of the priority queue.
     */
    STLMaxPriorityQueue(vector<pair<P, V>> contents);
    ~STLMaxPriorityQueue();
    void insert(P priority, V value);
    V remove();
    V peek();
    P peekPriority();
    int getSize();
    bool isEmpty();

  private:
    std::priority_queue<pair<P, V>, vector<pair<P, V>>, FirstLess<P, V>>*
        actualPriorityQueue;

    // You can safely ignore the following code.  This eliminates some default
    // class routines, preventing you from using them accidentally.
    // Specifically, we are disabling the use of the copy constructor and the
    // copy assignment operator.  You can read more here:
    //   http://www.cplusplus.com/articles/y8hv0pDG/
  private:
    STLMaxPriorityQueue(const STLMaxPriorityQueue& other) = delete;
    STLMaxPriorityQueue& operator=(const STLMaxPriorityQueue& other) = delete;
};

template <typename P, typename V>
STLMaxPriorityQueue<P, V>::STLMaxPriorityQueue() {
    actualPriorityQueue =
        new std::priority_queue<pair<P, V>, vector<pair<P, V>>,
                                FirstLess<P, V>>();
}

template <typename P, typename V>
STLMaxPriorityQueue<P, V>::STLMaxPriorityQueue(vector<pair<P, V>> contents) {
    actualPriorityQueue =
        new std::priority_queue<pair<P, V>, vector<pair<P, V>>,
                                FirstLess<P, V>>(contents.begin(),
                                                 contents.end());
}

template <typename P, typename V>
STLMaxPriorityQueue<P, V>::~STLMaxPriorityQueue() {
    delete actualPriorityQueue;
}

template <typename P, typename V>
void STLMaxPriorityQueue<P, V>::insert(P priority, V value) {
    actualPriorityQueue->push(pair<P, V>(priority, value));
}

template <typename P, typename V> V STLMaxPriorityQueue<P, V>::remove() {
    if (actualPriorityQueue->empty()) {
        throw runtime_error("STLMaxPriorityQueue::remove(): empty prio queue");
    }
    V v = actualPriorityQueue->top().second;
    actualPriorityQueue->pop();
    return v;
}

template <typename P, typename V> V STLMaxPriorityQueue<P, V>::peek() {
    if (actualPriorityQueue->empty()) {
        throw runtime_error("STLMaxPriorityQueue::peek(): empty prio queue");
    }
    return actualPriorityQueue->top().second;
}

template <typename P, typename V> P STLMaxPriorityQueue<P, V>::peekPriority() {
    if (actualPriorityQueue->empty()) {
        throw runtime_error(
            "STLMaxPriorityQueue::peekPriority(): empty prio queue");
    }
    return actualPriorityQueue->top().first;
}

template <typename P, typename V> int STLMaxPriorityQueue<P, V>::getSize() {
    return actualPriorityQueue->size();
}

template <typename P, typename V> bool STLMaxPriorityQueue<P, V>::isEmpty() {
    return actualPriorityQueue->empty();
}
