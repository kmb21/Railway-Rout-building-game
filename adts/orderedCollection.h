#pragma once

/*
  Copyright (c) 2023
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, A. Danner, L. Fontes, L. Meeden, Z. Palmer, A. Soni
  Distributed as course material for Spring 2023
  CPSC 035: Data Structures and Algorithms
*/

/**
 * The OrderedCollection is a pure virtual (abstract) interface representing a
 * collection of elements which may be removed in some order.  The particular
 * implementation of the OrderedCollection dictates the order in which they are
 * removed.
 * @tparam T The type of elements stored in the queue.
 */
template <typename T> class OrderedCollection {
  public:
    virtual ~OrderedCollection(){};

    /**
     * Adds an element to the collection.
     * @param item The element to collection.
     */
    virtual void insert(T element) = 0;

    /**
     * Removes an element from the collection.
     * @return The element that was removed.
     * @throws runtime_error If the collection was empty.
     */
    virtual T remove() = 0;

    /**
     * Determines the size of this collection.
     * @return The number of elements in the collection.
     */
    virtual int getSize() = 0;

    /**
     * Determines whether this collection is empty.
     * @return true if the collection is empty; false if it is not.
     */
    virtual bool isEmpty() = 0;

    /**
     * Retrieves the next element from the collection (without removing it).
     * This is the same element which would be returned by the take() method.
     * @return The next element in the collection.
     * @throws runtime_error If the queue is empty.
     */
    virtual T peek() = 0;

    // You can safely ignore the following code.  This eliminates some default
    // class routines, preventing you from using them accidentally.
    // Specifically, we are disabling the use of the copy constructor and the
    // copy assignment operator.  You can read more here:
    //   http://www.cplusplus.com/articles/y8hv0pDG/
  public:
    OrderedCollection() {
    }

  private:
    OrderedCollection(const OrderedCollection& other) = delete;
    OrderedCollection& operator=(const OrderedCollection& other) = delete;
};
