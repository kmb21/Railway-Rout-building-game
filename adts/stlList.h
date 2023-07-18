#pragma once


#include <iterator>
#include <list>
#include <stdexcept>
#include <vector>

#include "list.h"

using std::list;
using std::runtime_error;

template <typename T> class STLList : public List<T> {
  public:
    int getSize();
    bool isEmpty();
    T getFirst();
    T getLast();
    T get(int i);
    void insertFirst(T value);
    void insertLast(T value);
    T removeFirst();
    T removeLast();
    /**
     * Creates a copy of this list in the form of a vector and returns it.
     */
    std::vector<T> toVector();

  private:
    list<T> actualList;
};

template <typename T> int STLList<T>::getSize() {
    return actualList.size();
}

template <typename T> bool STLList<T>::isEmpty() {
    return actualList.empty();
}

template <typename T> T STLList<T>::getFirst() {
    if (actualList.empty()) {
        throw runtime_error("getFirst: empty list");
    } else {
        return actualList.front();
    }
}

template <typename T> T STLList<T>::getLast() {
    if (actualList.empty()) {
        throw runtime_error("getLast: empty list");
    } else {
        return actualList.back();
    }
}

template <typename T> T STLList<T>::get(int i) {
    if (i < 0 || i >= actualList.size()) {
        throw runtime_error("get: invalid index");
    }
    return *(std::next(actualList.begin(), i));
}

template <typename T> void STLList<T>::insertFirst(T value) {
    actualList.push_front(value);
}

template <typename T> void STLList<T>::insertLast(T value) {
    actualList.push_back(value);
}

template <typename T> T STLList<T>::removeFirst() {
    if (actualList.empty()) {
        throw runtime_error("removeFirst: empty list");
    } else {
        T value = getFirst();
        actualList.pop_front();
        return value;
    }
}

template <typename T> T STLList<T>::removeLast() {
    if (actualList.empty()) {
        throw runtime_error("removeLast: empty list");
    } else {
        T value = getLast();
        actualList.pop_back();
        return value;
    }
}

template <typename T> std::vector<T> STLList<T>::toVector() {
    std::vector<T> vec;
    typename std::list<T>::iterator it = this->actualList.begin();
    while (it != this->actualList.end()) {
        vec.push_back(*it);
        it++;
    }
    return vec;
}
