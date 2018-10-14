/*
 * This software is the original work of Yuqi Wang. ID: 24717835
 * This software is submitted in partial fulfilment of the
 * requirements for the degree of Information Technology and System,
 * Monash University
 */

//
//  Flower.cpp
//  Evolution
//
//  Created by Yuqi Wang on 12/05/2015.
//  Copyright (c) 2015 Yuqi Wang. All rights reserved.
//

#include "Flower.h"
#include "GL_routines.h"
#include <stdlib.h>
#include <math.h>

using namespace std;

Flower::Flower()
{
    initialiseRandomly();
    //getDetails();
}


void Flower::initialiseRandomly()
{
    petals.clear();
    for (unsigned i = 0; i < 3;i ++)
    {
        petals.push_back((rand()%15 + 1)/(rand()%2 + 1));// Radius
        petals.push_back(static_cast <float> (rand()) / static_cast <float> (RAND_MAX));// Red
        petals.push_back(static_cast <float> (rand()) / static_cast <float> (RAND_MAX));// Green
        petals.push_back(static_cast <float> (rand()) / static_cast <float> (RAND_MAX));// Blue
        petals.push_back((int)rand()%20 +1);// Number of edges
        petals.push_back(rand()%10 + 5);// Ring diameter
        petals.push_back((int)(rand()% 10 + 5)/(rand()%2 + 1));// Number of petals
        petals.push_back((int)(rand()% 3));// Display Mode. 0 = outline, 1 = fill, 2 = both
    }
    
}

double Flower::assignRandomly(int i)
{
    // Assign value for specific type of genes
    
    double returnValue =0;
    int geneType =0;
    geneType = i%8;
    
    switch (geneType) {
        case 0:
            returnValue = (rand()%15 + 1)/(rand()%2 + 1); // Radius
            break;
        case 1:
        case 2:
        case 3:
            returnValue = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
            break;
        case 4:
            returnValue = (int)rand()%20 +1;
            break;
        case 5:
            returnValue = rand()%10 + 5;
            break;
        case 6:
            returnValue = (rand()% 10 + 5)/(rand()%2 + 1);
            break;
        case 7:
            returnValue = rand()% 3;
            break;
        default:
            break;
    }
    
    return returnValue;
    
}



void Flower::drawPetal(int i)
{
    glPushMatrix();
    double centX, centY, centZ;
    centX =0;
    centY =0;
    centZ =0.001f; // Use this scalar to highlight the outline because it may be covered by the filled petals
    double currentPointX, currentPointY;
    double angleRadians= 0;
    double stepSize = (2*M_PI)/(double)petals[4+8*i];
    // Set the current colour (white R=G=B=1.0, black R=G=B=0.0)
    glColor3d(petals[1+8*i], petals[2+8*i], petals[3+8*i]);
    
    int drawMode = petals[7+8*i];
    
    switch (drawMode)
    {
        case 0: // Draw outline
            glBegin(GL_LINE_LOOP);
            centZ *= i; // Pull it towards the screen so we can always see the outline
            break;
        case 1: // Fill the petal
            glBegin(GL_POLYGON);
            centZ *= -(2-i); // Push it backwards the screen.(The pattern will always behind the petal outlines)
            break;
        case 2:
            glBegin(GL_POLYGON);
            centZ *= -(2-i);
            for (angleRadians=0; angleRadians < (2*M_PI); angleRadians+=stepSize)
            {
                currentPointX = centX+(petals[8*i] * cos(angleRadians));
                currentPointY = centY+(petals[8*i] * sin(angleRadians));
                glVertex3f(currentPointX, currentPointY,centZ);
            }
            glEnd();
            glBegin(GL_LINE_LOOP);
            break;
        default:
            break;
    }
    
    //glBegin(GL_LINE_LOOP);
    // Traverse around a circle in the specified number of steps
    centX = 0;
    centY = 0;
    for (angleRadians=0; angleRadians < (2*M_PI); angleRadians+=stepSize)
    {
        currentPointX = centX+(petals[8*i] * cos(angleRadians));
        currentPointY = centY+(petals[8*i] * sin(angleRadians));
        glVertex3f(currentPointX, currentPointY,centZ);
    }
    glEnd();
}

void Flower::drawPetalRing(int k)
{
    glPushMatrix();
    for (int i=0; i<petals[6+8*k]; i++)
    {
        glPushMatrix();
        // move petal to position on the ring circumference (angles in radians)
        glTranslated(0.5*petals[5+8*k]*cos(i*2.0*M_PI/petals[6+8*k]),
                     0.5*petals[5+8*k]*sin(i*2.0*M_PI/petals[6+8*k]), 0);
        // rotate petal (in degrees) so it points away from the ring’s centre
        glRotated((double)i*360.0/(double)petals[6+8*k], 0.0, 0.0, 1.0);
        drawPetal(k);
        glPopMatrix();
    }
    glPopMatrix();
}

void Flower::getDetails()
{
    for (unsigned int i=0;i<3;i++) // Get the information for each ring
    {
        cout << "Ring: " << i+1 << endl;
        cout << "Radius: " << petals[i*8] << endl;
        cout << "R_G_B: " << petals[1+i*8] << "," << petals[2+i*8] << "," << petals[3+i*8] << endl;
        cout << "Number of edges: " << petals[4+i*8] << endl;
        cout << "Ring diameter: " << petals[5+i*8] << endl;
        cout << "Number of petals: " << petals[6+i*8] << endl;
        cout << "Character(Display mode): " << petals[7+i*8] << endl;
    }

}


void Flower::getMeanValue()
{
    float mred =0;
    float mgreen =0;
    float mblue =0;
    
    for (unsigned int i =0;i<3;i++)
    {
        mred += petals[1+i*8];
        mgreen += petals[2+i*8];
        mblue += petals[3+i*8];
    }
    
    cout << "Mean R_G_B:" << mred/3 << "," << mgreen/3 << "," << mblue/3 << endl;
    
}


Flower Flower::crossover(Flower f,Flower child)
{
    
    child.setMutationRate(myMutationRate);
    
    int pointPos = rand()% 23 + 1; // Pick random point between 1 and 23
    
    int childType = rand() % 2;
    
    switch (childType) {
        case 0:
            for (unsigned int i = 0; i< pointPos; i++)
            {
                child.setPetalsGene(i,petals[i]); // Set values based on parent #1 before the point
            }
            
            for (unsigned int i = pointPos; i< petals.size(); i++)
            {
                child.setPetalsGene(i, f.getPetalsGene(i)); // Set value based on parent #2 after the point
            }
            break;
            
        case 1:
            for (unsigned int i = 0; i< pointPos; i++)
            {
                child.setPetalsGene(i,f.getPetalsGene(i)); // Set values based on parent #2 before the point
            }
            
            for (unsigned int i = pointPos; i< petals.size(); i++)
            {
                child.setPetalsGene(i, petals[i]); // Set value based on parent #1 after the point
            }
        default:
            break;
    }
    
    child.mutate(); // Then mutate it
    
    return child; // Return the child
    
}



void Flower::mutate()
{
    
    Flower *mutatedChild = new Flower(); // Create a child <- this method is not efficient but seems like it returns better results
    
    float mutateNum = petals.size()*myMutationRate; // Calculate the number of genes that need to be mutated based on the mutate rate
    
    int mutateIndex = 0;
    
    int mutateCount = 0;
    
    int mutateDigit = rand()%11;;
    
    int rateDigit = (myMutationRate*100);
    
    // The mutateNum is a floating number. For example, a flower has 10 genes and the mutate rate is 18%, the number of genes need to be mutated will be 1.8.
    // We can't always use a round number like 2.0 because the average mutation rate will be 20% if we do so.
    // Here we will do something to determine the value
    // Get the last digit of the mutation rate, and we will calculate it based on this digit.
    // Here are some examples:
    // If it is 5 (like 15%), it will have 50% chance to mutate 1 gene and another 50% chance to mutate 2 genes. The average mutation rate will be 15%.
    // If it is 8 (like 28%), it will have 20% chance to mutate 2 genes and 80% chance to mutate 3 genes. The average mutation rate will be 28%.
    // If it is 4 (like 34%), it will have 40% chance to mutate 4 genes and 60% chance to mutate 3 genes. The average mutation rate will be 34%.
    
    rateDigit = rateDigit%10;
    
    if (rateDigit < 5)
    {
        if (mutateDigit > rateDigit)
        {
            mutateIndex = (int)mutateNum;
        }else
        {
            mutateIndex = round(mutateNum);
        }
    }else if(rateDigit >= 5)
    {
        if (mutateDigit > rateDigit)
        {
            mutateIndex = round(mutateNum);
        }else
        {
            mutateIndex = (int)mutateNum;
        }
    }
    
    while (mutateCount < mutateIndex)
    {
        
        int i = rand()% petals.size(); // Randomly pick a gene
        
        petals[i] = mutatedChild->getPetalsGene(i);// Mutate it by replacing the value from the new child *A gene may be mutated multiple times
        
        //petals[i] = assignRandomly(i);// Mutate it by generating a new value for the specific gene // Disable *newmutatedChild to use this method
        
        mutateCount+= 1;
        
    }
    
    getDetails();
    
    delete mutatedChild;
    
}










