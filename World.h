/*
 * This software is the original work of Yuqi Wang. ID: 24717835
 * This software is submitted in partial fulfilment of the
 * requirements for the degree of Information Technology and System,
 * Monash University
 */

//
//  World.h
//  Evolution
//
//  Created by Yuqi Wang on 12/05/2015.
//  Copyright (c) 2015 Yuqi Wang. All rights reserved.
//

#ifndef __Evolution__World__
#define __Evolution__World__

#include <stdio.h>
#include <vector>
#include "Flower.h"

using namespace std;

class World
{
private:
    vector<Flower> blossom; //
    int grid;
    float mutationRate;
    int parent1, parent2;
    int currentParent;
    
public:
    World(); // Cons
    World(int N, float M); // Used to initialize the world with parameter N
    void Mate();
    void moveAndDraw();
    void hightlightSelected();
    int getGrid(){return grid;}
    float getMutationRate(){return mutationRate;}
    void setParent(int num);
    
};

#endif /* defined(__Evolution__World__) */
