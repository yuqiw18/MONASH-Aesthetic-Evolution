/*
 *  GL_routines.cpp
 *
 *  Created by Alan Dorin on Fri May 24 2002.
 *  Copyright (c) 2001 __MyCompanyName__. All rights reserved.
 *
 */

// Modified by Yuqi Wang

#include <iostream>
#include "GL_routines.h"

#include <vector>
#include <math.h>

#include "World.h"
#include "Flower.h"

World *newWorld;
vector<int> inputNum;

extern void cleanQuit( );
extern void drawCircleXZWire(const double, const double, const double);
extern void drawPetal();

void myInitializeOpenGL(int N,float M)
{
	// Set the background/clear-the-screen colour
	glClearColor (0.02, 0.02, 0.02, 0.0);
   
	// These routines ensure that objects further away from
	// the viewpoint will be drawn on top of by closer objects (using a "depth-buffer" or "z-buffer")   
	glDepthMask(GL_TRUE);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
    
    newWorld = new World(N,M);
    inputNum.clear();
    
    std::cerr << "\nIn myInitializeOpenGL(void)";
    
    
    
}

void displayWorld(void)
{   
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// clear the screen and clear the depth-buffer
	glLoadIdentity ();						      		// load the identity matrix
    
    newWorld->moveAndDraw();
    newWorld->hightlightSelected();
    
    // What does this routine do?
	glFlush ();
	
    // This routine "swaps buffers"
    glutSwapBuffers();
}

void reshape (int w, int h)
{
    std::cerr << "\nIn reshape(w,h)";

   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity();
   
   // lookAt from, to, up
  /* gluLookAt (0, -10, 0,
					0, 0, 0,
						0, 0, 1);
      */                  
   gluOrtho2D(-100, +100, -100, 100);
   
   glMatrixMode (GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y)
{
    // extern gYourCreatureCollectionDataStruct here
    
	switch (key) {
        // character 27 is the escape key. Use this or Q/q to quit the program
        case 27:
        case 'q':
        case 'Q':
            // Call your cleanQuit routine to quit neatly
            cleanQuit( );
        break;

        // Assign keys to do different things in you code. For example you might like to....
        case 'r':
        case 'R':
            newWorld = new World(newWorld->getGrid(),newWorld->getMutationRate());
        	glutPostRedisplay();
      	break;
            
        case 'm':
        case 'M':
            newWorld->Mate();
            glutPostRedisplay();
            break;
        
        case 48:  // 0
            inputNum.push_back(0);
            //glutPostRedisplay();
        break;
            
        case 49:
            inputNum.push_back(1);
            //glutPostRedisplay();
            break;
            
        case 50:
            inputNum.push_back(2);
            //glutPostRedisplay();
            break;
            
        case 51:
            inputNum.push_back(3);
            //glutPostRedisplay();
            break;
            
        case 52:
            inputNum.push_back(4);
            //glutPostRedisplay();
            break;
            
        case 53:
            inputNum.push_back(5);
            //glutPostRedisplay();
            break;
            
        case 54:
            inputNum.push_back(6);
            //glutPostRedisplay();
            break;
            
        case 55:
            inputNum.push_back(7);
            //glutPostRedisplay();
            break;
            
        case 56:
            inputNum.push_back(8);
            //glutPostRedisplay();
            break;
        
        case 57:
            inputNum.push_back(9);
            //glutPostRedisplay();
            break;
            
        case 13: //Enter
            if (!inputNum.empty())
            {
                int num = 0;
                
                for (unsigned int i = 0; i < inputNum.size(); i++ )
                {
                    num += inputNum[i] * pow(10,inputNum.size()-(i+1));
                }
                
                std::cout << num <<std::endl;
                
                newWorld->setParent(num);
                
                inputNum.clear();
            }else
            {
                std::cout << "Please input the parent ID" << std::endl;
            }
            glutPostRedisplay();
            break;
            
      	default:
            // Do something or nothing by default when a key you haven't used is pressed here...
      	break;
   }
}

void mouse(int button, int state, int x, int y)
{
	switch (button)
	{
      case GLUT_LEFT_BUTTON:
         if (state == GLUT_DOWN)
         {
            // Do something e.g. gYourPlayerCharacterDataStruct->update()
            
            // and maybe redisplay...
            glutPostRedisplay();
         }
      break;
      
      default:
      
      break;
   }
}

void mouseMove(int x, int y)
{
    // Sometimes its useful to keep track of the old mouse
    // position so that you can compare it to new mouse positions.
    // You'll need static variables to do this... why?
	static int oldX=0;
	static int oldY=0;
	static bool firstCall = true;
    
    // What is the use of this if statement?
	if(firstCall==true)
	{
		oldX=x;
		oldY=y;
		firstCall = false;
		return;
	}
    
    // Do things in here with the difference b/n the new mouse x,y and oldX,oldY
    // to make your program's behaviour respond to mouse movements.
    
    // Then set the old mouse position to the current mouse position
    // for next time around...
    oldX=x;
	oldY=y;
}

void mousePassiveMove(int x, int y)
{
    // What might you write in here?
    // What is this event handler for?
}

void visible(int vis)
{
	if (vis == GLUT_VISIBLE)	glutIdleFunc(updateWorld);
	else						glutIdleFunc(NULL);
}

void updateWorld(void)
{
    // Update your gYourCreatureCollectionDataStruct here
    // for example call gYourCreatureCollectionDataStruct->update() and
    // maybe call gYourPlayerCharacterDataStruct->update() if any non-player controlled aspects need to be updated
    
	// then request a redraw of the display by posting a "redraw" event
	glutPostRedisplay();
}

void null_select(int mode)
{	/* nothing */ }

void menu_select(int mode)
{
	switch (mode)
	{
		case 1:
			// Put code in here to handle the first menu item
		break;

		case 2:
            // Code to handle the menu quit...
			{ cleanQuit( ); }
		break;
		default:
			return;
		break;
	}
}

void glutMenu(void)
{
	int glut_menu;
	
	glut_menu = glutCreateMenu(menu_select);
	
	glutAddMenuEntry("Do Nothing", 1);
	glutAddMenuEntry("Quit", 2);
	
	glutAttachMenu(GLUT_LEFT_BUTTON);
  	glutAttachMenu(GLUT_RIGHT_BUTTON);
}
