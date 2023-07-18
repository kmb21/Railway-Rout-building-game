/*
  Copyright (c) 2023
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, A. Danner, L. Fontes, L. Meeden, Z. Palmer, A. Soni
  Distributed as course material for Spring 2023
  CPSC 035: Data Structures and Algorithms
*/

#include <stdexcept>
#include "adts/stack.h"
#include "adts/stlStack.h"
#include "adts/dictionary.h"
#include "adts/queue.h"
#include "adts/stlQueue.h"
#include "adts/priorityQueue.h"
#include "adts/edge.h"
#include "adts/stlMinPriorityQueue.h"
#include "adts/stlHashTable.h"

using namespace std;


template <typename V, typename E, typename W>
bool reachableDFS(V src, V dest, Graph<V, E, W>* g) {
    Stack<V>* my_stack = new STLStack<V>();
    Dictionary<V, bool>* visited= new STLHashTable<V,bool>();

    my_stack->push(src);
    visited->insert(src, true);

    while(!my_stack->isEmpty()){
        V current = my_stack->pop();
        if (current== dest){
            return true;
        }
        vector<V> neighbors= g->getNeighbors(current);
        for(int i= 0; i< neighbors.size(); i++){
            if(!visited->contains(neighbors[i])){
                visited->insert(neighbors[i],true);
                my_stack->push(neighbors[i]);
            }

        }
    }
    delete my_stack;
    delete visited;
    my_stack = nullptr;
    visited = nullptr;
    return false;
    
}

template <typename V, typename E, typename W>
vector<V> shortestLengthPathBFS(V src, V dest, Graph<V, E, W>* g) {
   
    vector<V> path;
    vector<V> temp;
    Queue<V>* queue= new STLQueue<V>();
    Dictionary<V,V>* previous= new STLHashTable<V,V>();
    queue->enqueue(src);
    previous->insert(src,src);
    while(!queue->isEmpty()){
        V current= queue->dequeue();
        if(current == dest){
            while(current!= src){//

                path.push_back(current);
                current= previous->get(current);
            }

            path.push_back(src);
            for (int i = path.size()-1; i>=0;i--){

                temp.push_back(path[i]);
            }

        }
        else{
            vector<V> neighbors= g->getNeighbors(current);
        for(int i= 0; i< neighbors.size(); i++){
            if(!previous->contains(neighbors[i])){
                previous->insert(neighbors[i],current);
                queue->enqueue(neighbors[i]);
            }

        }
        }
        
    }
    delete previous;
    delete queue;
    if (temp.size() == 0){
        throw runtime_error("ShortestLengthPathBFS, path does not exist");
    }

    return temp;
}

template <typename V, typename E, typename W>
Dictionary<V, W>* singleSourceShortestPath(V src, Graph<V, E, W>* g) {
    
    STLHashTable<V, W>* cost= new STLHashTable<V, W>();
    STLMinPriorityQueue<W, V>* pq = new STLMinPriorityQueue<W, V>();

    cost->insert(src,0);
    pq->insert(0,src);

    while(!pq->isEmpty()){
        W currPrio= pq->peekPriority();
        V currVer= pq->remove();
        W currCost= cost->get(currVer);
        vector<Edge<V,E,W>> out_going= g->getOutgoingEdges(currVer);
        if (currCost== currPrio){
            for(int i= 0 ; i<out_going.size(); i++ ){
                V nextVertex= out_going[i].getDestination();
                W new_cost= currCost + out_going[i].getWeight();
                if(!cost->contains(nextVertex)){
                    cost->insert(nextVertex, new_cost);
                    pq->insert(new_cost, nextVertex);
                } else if(new_cost< cost->get(nextVertex)){
                    cost->update(nextVertex, new_cost);
                    pq->insert(new_cost, nextVertex);
                }
            }
        } 
    }
    delete pq;
    return cost;
}

