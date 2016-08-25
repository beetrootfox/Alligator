//
//  Alligator.h
//  MemoryAlligator
//
//  Created by Даниил on 11/08/2016.
//  Copyright (c) 2016 Даниил. All rights reserved.
//

#ifndef __MemoryAlligator__Alligator__
#define __MemoryAlligator__Alligator__
#define POOLSIZE 1000

#include <stdio.h>
#include <sys/types.h>

#endif /* defined(__MemoryAlligator__Alligator__) */

template<typename T>
class IAlligator{
public:
    virtual void* allocate(size_t) = 0;
    virtual void       free(void*) = 0;
};

template<typename T>
class Alligator : public IAlligator<T>{
    struct XList{
        XList* next;
    };
    void expandPool ();
    void cleanUp ();
    XList* xlisthead;
public:
    Alligator(){
        xlisthead = 0;
        expandPool();
    }
    virtual ~Alligator(){
        cleanUp();
    }
    virtual void* allocate(size_t);
    virtual void       free(void*);
};

/*template<typename T>
inline void* Alligator<T>::allocate(size_t size){
    if(xlisthead == 0) expandPool();
    
    XList* head = xlisthead;
    xlisthead = head->next;
    return head;
}*/

template<typename T>
inline void* Alligator<T>::allocate(size_t size){
    if(xlisthead == 0) expandPool();
    
    XList* head = xlisthead;
    xlisthead = head->next;
    return head;
}

template<typename T>
inline void Alligator<T>::free(void* p){
    XList* head = static_cast <XList*> (p);
    head->next = xlisthead;
    xlisthead = head;
}

template<typename T>
void Alligator<T>::expandPool(){
    size_t size = (sizeof(T) > sizeof(XList*)) ? sizeof(T) : sizeof(XList*);
    XList* head = reinterpret_cast <XList*> (new char[size]);
    xlisthead = head;
    
    for(int i = 0; i < POOLSIZE; i++){
        head->next = reinterpret_cast <XList*> (new char [size]);
        head = head->next;
    }
    
    head->next = 0;
}
/*
template<typename T>
void Alligator<T>::expandPool(){
    size_t size = (sizeof(T) > sizeof(XList*)) ? sizeof(T) : sizeof(XList*);
    XList* head = reinterpret_cast <XList*> (new char[size*POOLSIZE]);
    xlisthead = head;
    
    for(int i = 0; i < POOLSIZE; i++){
        head->next = head + size;
        head = head->next;
    }
    
    head->next = 0;
}*/


template<typename T>
void Alligator<T>::cleanUp(){
    XList* nextPtr = xlisthead;
    for(; nextPtr; nextPtr = xlisthead){
        xlisthead = xlisthead->next;
        delete [] nextPtr;
    }
}
