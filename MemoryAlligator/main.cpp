//
//  main.cpp
//  MemoryAlligator
//
//  Created by Даниил on 11/08/2016.
//  Copyright (c) 2016 Даниил. All rights reserved.
//

#include <iostream>
#include "Alligator.h"

class Shelf{
public:
    Shelf (long n, long x): a(n), b(x) {}
    inline void* operator new(size_t);
    inline void  operator delete(void*);
private:
    long a;
    long b;
    
};

Alligator<Shelf> gAtor;

void* Shelf::operator new (size_t size){
    return gAtor.allocate(size);
}


void Shelf::operator delete (void* p){
    gAtor.free(p);
}

int main(int argc, const char * argv[]) {
    Shelf* array[1000];
    //std::allocator<Shelf> al;
   // Shelf* a = al.allocate(1000);
    for (int i = 0; i < 5000; i++){
        for (int j = 0; j < 1000; j++){
            array[j] = new Shelf (i, j);
        //    al.construct(a+j,i,j);
        }
        for (int j = 0; j < 1000; j++) {
           delete array[j];
        //    al.destroy(a+j);
        }
    }
    return 0;
}
