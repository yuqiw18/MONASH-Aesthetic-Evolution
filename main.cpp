//
//  main.m
//  junkproj
//
//  Created by Alan Dorin

//  Modified by Yuqi Wang

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <GLUT/glut.h>

#include "GL_routines.h"
#include "World.h"
#include "Flower.h"

using namespace std;


// because OpenGL works using eventHandlers you will need to define
// a few global variables. For example...

// YOUR_CREATURE_TYPE	gYourCreatureCollectionDataStruct;

int	gWinRows=500;
int gWinCols=500;

// Define a function which will always exit your program cleanly

void cleanQuit( )
{
    // put code in here to print out the message and quit the program
    exit(0);
}

// ! UNTESTED Circle code that doesn't use anything other than openGL...

int main(int argc, char **argv)
{
    
    // Default value for grid and mutation rate
    
    int gridN = 4;
    float MutationRate = 15;
    
    // Here we can get parameters from command line
    
    for (int i = 0; i < argc; i++)
    {
        if (strncmp(argv[i],"-grid",5)==0)
        {
            printf("Grid: ",argv[i+1]);
            gridN = atoi(argv[i+1]);
        }
        if (strncmp(argv[i],"-mRate",5)==0)
        {
            printf("MutationRate: ",argv[i+1]);
            MutationRate = atoi(argv[i+1]);
        }
    }
    
    
    if ((gridN > 0 && gridN<=12) && (MutationRate >=0 && MutationRate<=100))
    {
        
        srand((unsigned int)time(NULL));// Seed the rand()
        
        // Initialize OpenGL/GLUT (only do this once)
        glutInit(&argc, argv);
        
        // Set up OpenGL to use double buffering, RGB mode, and a depth-buffer
        glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
        
        // Set up the window and open it
        glutInitWindowSize (gWinCols, gWinRows);
        glutInitWindowPosition (0, 0);
        glutCreateWindow ("Aesthetic Evolution of Flowers");
        
        // This routine makes the graphics window take up the whole screen
        // for when you want this to work in game mode
        // glutFullScreen();
        // Do some of your own initializations in this routine
        myInitializeOpenGL(gridN,MutationRate/100);
        // Register all of the event handlers
        glutDisplayFunc(displayWorld);
        glutVisibilityFunc(visible);
        glutReshapeFunc(reshape);
        glutKeyboardFunc(keyboard);
        glutMouseFunc(mouse);
        glutMotionFunc(mouseMove);
        glutPassiveMotionFunc(mousePassiveMove);
        glutIdleFunc(updateWorld);
        
        // Set the software looking for events in an infinite loop
        glutMainLoop();
    }else
    {
        cout << "======================ERROR========================" << endl;
        cout << "Invalid parameter(s)" << endl;
        cout << "Please make sure you enter the correct values:" << endl;
        cout << "The NxN grid must be a int between 1 and 12" << endl;
        cout << "Default value: 4; Use '-grid' <N> to define" << endl;
        cout << "The MutationRate must be any number from 0 to 100" << endl;
        cout << "Default value: 15; Use '-mRate' <Value> to change" << endl;
        cout << "===================================================" << endl;
    }
    
    // ANSI C requires integer return type from main()
    return 0;
}
