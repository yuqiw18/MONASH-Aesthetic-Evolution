/*
 * This software is the original work of Yuqi Wang. ID: 24717835
 * This software is submitted in partial fulfilment of the
 * requirements for the degree of Information Technology and System,
 * Monash University
 */

//
//  World.cpp
//  Evolution
//
//  Created by Yuqi Wang on 12/05/2015.
//  Copyright (c) 2015 Yuqi Wang. All rights reserved.
//

#include "World.h"
#include "Flower.h"
#include <iostream>
#include <GLUT/glut.h>

using namespace std;

World::World()
{
    currentParent = 2;
    parent1 = 0;
    parent2 = 0;
}

World::World(int N, float M)
{
    // Initialise the world
    grid = N;
    mutationRate = M;
    blossom.clear();
    for (unsigned int i = 0; i < grid*grid; i++)
    {
        Flower* f = new Flower();
        blossom.push_back(*f);
        blossom[i].setMutationRate(M);
    }
    
    // -1 means not selected
    parent1 = -1;
    parent2 = -1;
    
}

void World::Mate()
{
    for (unsigned int i = 0; i < grid*grid; i++)
    {
        if (i != parent1 && i != parent2)
        {
            Flower *newChild = new Flower();
            blossom[i] = (blossom[parent1].crossover(blossom[parent2],*newChild));
            delete newChild;
        }
    }
    
}

void World::moveAndDraw()
{
    for (unsigned int k = 0; k<3 ; k++) // Each flower has 3 rings, we will do this for each ring
    {
        glLoadIdentity();
        glPushMatrix();
        
        glTranslated((-100/grid)*(grid-1), (100/grid)*(grid-1), 0);// Pick the first position for drawing the flower
        
        for (unsigned int i = 0; i < grid; i++)
        {
            double displacement = 0;
            for (unsigned int j = 0; j < grid ; j++)
            {
                int current = j + grid * i;
                blossom[current].drawPetalRing(k);
                glTranslated(200/grid, 0, 0);
                displacement += 200/grid;
            }
            glTranslated(-displacement, 0, 0); // Push it back to the left side
            glTranslated(0, -200/grid, 0); // Push it back to the top
        }
        glPopMatrix();

        
    }
    
}

void World::hightlightSelected()
{
    
    if (parent1 != -1) // If parent #1 is selected
    {
        int row1 = parent1/grid; // Find the row of the selected parent base on the input
        int col1 = parent1%grid; // Find the column of the selected parent base on the input
        
        glLoadIdentity();
        glPushMatrix();
        
        glTranslated((-100/grid)*(grid-1), (100/grid)*(grid-1), 0); // Pick the first position for drawing the flower
        glTranslated((200/grid)*col1, (-200/grid)*row1, 0);
        
        glColor3d(1.0, 1.0, 0); // Set the colour to yellow
        
        glBegin(GL_LINE_STRIP);
        
        glVertex2f(100/grid, 100/grid); // Draw the start point and the end point so that it can draw a line
        glVertex2f(-100/grid, 100/grid);
        glVertex2f(-100/grid, -100/grid);
        glVertex2f(100/grid, -100/grid);
        glVertex2f(100/grid, 100/grid);
        
        glEnd();
        
        glPopMatrix();
        
    }
    
    if (parent2 != -1)
    {
        int row2 = parent2/grid; // Find the row of the selected parent base on the input
        int col2 = parent2%grid; // Find the column of the selected parent base on the input
        
        glLoadIdentity();
        glPushMatrix();
        
        glTranslated((-100/grid)*(grid-1), (100/grid)*(grid-1), 0);// Pick the first position for drawing the flower
        glTranslated((200/grid)*col2, (-200/grid)*row2, 0);
        
        glColor3d(1.0, 1.0, 0); // Set the colour to yellow
        
        glBegin(GL_LINE_STRIP);
        
        glVertex2f(100/grid, 100/grid); // Draw the start point and the end point so that it can draw a line
        glVertex2f(-100/grid, 100/grid);
        glVertex2f(-100/grid, -100/grid);
        glVertex2f(100/grid, -100/grid);
        glVertex2f(100/grid, 100/grid);
        
        glEnd();
        
        glPopMatrix();
    }
}

void World::setParent(int num)
{
    if(num < 1 || num > grid * grid) // Check if the input is in the valid range
    {
        // If not, ignore it
    }
    else
    {
        num -= 1; // Convert the input into the element e.g. number 1 -> element 0 in the vector
        
        if (currentParent == 2) // If last selected parent is parent #2
        {
            parent1 = num;      // Set the value for parent #1
            currentParent = 1;  // Change the last selected parent to parent #1
        }
        else
        {
            parent2 = num;      // Set the value for parent #2
            currentParent = 2;  // Change the last selected parent to parent #2
        }
    }
    
}

