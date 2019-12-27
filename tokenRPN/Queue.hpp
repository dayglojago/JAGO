//
//  queue.hpp
//  stackAndQueue
//
//  Created by Swordfish on 10/31/18.
//  Copyright © 2018 Swordfish. All rights reserved.
//

#ifndef queue_hpp
#define queue_hpp

#include <stdio.h>
#include "linkedListFunctions.hpp"

template <class T>
class Queue {
    
public:
    
    class Iterator{
        
    public:
        
        friend class Queue;
        
        Iterator(){
            _pointer = NULL;
        }
        
        Iterator(node<T>* pointer):_pointer(pointer){}
        
        T operator *(){
            assert(_pointer);
            return _pointer->_item;
        }
        
        Iterator& operator ++(){
            if(_pointer == NULL){
                cout << "Cannot advance, at end of list.";
                exit(2000);
            }
            _pointer = _pointer->_next;
            return *this;
        }
        
        friend bool operator != (const Queue<T>::Iterator& lhs, const Queue<T>::Iterator& rhs){
            return lhs._pointer != rhs._pointer;
        }
        
        friend bool operator == (const Queue<T>::Iterator& lhs, const Queue<T>::Iterator& rhs){
            return lhs._pointer == rhs._pointer;
        }
        
        friend ostream& operator << (ostream& outs, const Queue<T>::Iterator printAddress){
            outs << printAddress._pointer;
            return outs;
        }
        
        friend Iterator operator ++ (Iterator& it, int unused){
            if(it._pointer == NULL){
                cout << "Cannot advance, at end of list.";
                exit(2000);
            }
            it._pointer = it._pointer->_next;
            return it;
        }
        
        
        
    private:
        
        node<T>* _pointer;
        
    };
    
    Queue();
    
    ~Queue();
    
    Queue(const Queue& rhs);
    
    Iterator begin() const{
        Iterator it(_front);
        return it;
    }
    
    void emptyQueue();
    
    Iterator end() const{
        
        Iterator it(_back->_next);
        //cout << "back, bitch: " << _back->_next << endl;
        return it;
    }
    
    friend ostream& operator << (ostream& outs, const Queue<T>& theQueue){
        
        for(Queue<T>::Iterator it = theQueue.begin(); it != theQueue.end(); it++){
            outs << *it << " ";
            
        }
        
        return outs;
        
    }
    
    Queue operator = (const Queue& rhs){
        if(this == &rhs){
            return *this;
        }
        clearList(_front);
        _back = copyList(_front, rhs._front);
        return *this;
    }
    
    void push(T item);
    
    T pop();
    
    T front();
    
    bool empty();
    
private:
    
    node<T>* _front;
    node<T>* _back;
    
};

template <class T>
Queue<T>::Queue(){
    _front = NULL;
    _back = NULL;
}

template <class T>
Queue<T>::~Queue(){
    clearList(_front);
}

template <class T>
void Queue<T>::emptyQueue(){
    clearList(_front);
}

template <class T>
Queue<T>::Queue(const Queue& rhs){
    _front = NULL;
    _back = NULL;
    _back = copyList(_front, rhs._front);
}

template <class T>
T Queue<T>::pop(){
    T item;
    if(_front != NULL){
        item = deleteHead(_front);
        _back = lastNode(_front);
    }else{
        cout << "Cannot pop, Queue empty. Exiting." << endl;
        exit(420);
    }
    return item;
}

template <class T>
void Queue<T>::push(T item){
    
    if(_front == NULL && _back == NULL){
        _front = insertHead(_front, item);
        _back = _front;
    }else{
        _back = insertAfter(_back, item);
    }
    
}

template <class T>
T Queue<T>::front(){
    return _front->_item;
}


template <class T>
bool Queue<T>::empty(){
    if(_front == NULL && _back == NULL){
        return true;
    }
    return false;
}


#endif /* queue_hpp */
