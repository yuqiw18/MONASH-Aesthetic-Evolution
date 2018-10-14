/*
 * This software is the original work of Yuqi Wang. ID: 24717835
 * This software is submitted in partial fulfilment of the
 * requirements for the degree of Information Technology and System,
 * Monash University
 */

//
//  Flower.h
//  Evolution
//
//  Created by Yuqi Wang on 12/05/2015.
//  Copyright (c) 2015 Yuqi Wang. All rights reserved.
//

#ifndef __Evolution__Flower__
#define __Evolution__Flower__

#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;


class Flower
{
private:
    
    vector<double> petals;
    float myMutationRate;
    
public:
    
    Flower();
    void initialiseRandomly();
    double assignRandomly(int i);
    void drawPetal(int i);
    void drawPetalRing(int i);
    void getDetails();
    void getMeanValue();
    
    void setPetalsGene(int element,double val){petals[element] = val;}
    double getPetalsGene(int element){return petals[element];}
    
    Flower crossover(Flower f, Flower child);
    void mutate();
    void setMutationRate(float M){myMutationRate = M;}

    ~Flower(){};
};

#endif /* defined(__Evolution__Flower__) */
