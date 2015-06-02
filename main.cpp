/*
 * main.cpp
 *
 *  Created on: 26.05.2015
 *  Author: RDM
 */




#define GLFW_DLL
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "vec3.hpp"
#include "Table.h"

static double alpha_x = 0;
static double alpha_y = 0;
static double alpha_z = 0;
static bool rotate = false, open = false, perspektiv = true;
static double window_width_ = 1024;
static double window_height_ = 768;
static double xScale, yScale, zScale;



void drawDice(Vec3 strg,double l){
	//glNormal3fv
	//glNormal3dv( strg );
	//vorderseite
	glBegin(GL_QUADS);											// Start Drawing A Triangle
	glNormal3d(0,0,1);										// Set Top Point Of Triangle To Red
	glVertex3d(strg.p[0]-(l/2), strg.p[1]-(l/2),strg.p[2]-(l/2));			// First Point Of The Triangle
	glVertex3d(strg.p[0]+l-(l/2), strg.p[1]-(l/2), strg.p[2]-(l/2));        // Second Point Of The Triangle
    glVertex3d(strg.p[0]+l-(l/2), strg.p[1]+l-(l/2), strg.p[2]-(l/2));		// Third Point Of The Triangle
	glVertex3d(strg.p[0]-(l/2), strg.p[1]+l-(l/2), strg.p[2]-(l/2));
	//RUCKSEITE
	glNormal3d(0,0,-1);
	glVertex3d(strg.p[0]-(l/2), strg.p[1]-(l/2),strg.p[2]-(l/2)+l);			// First Point Of The Triangle
	glVertex3d(strg.p[0]+l-(l/2), strg.p[1]-(l/2), strg.p[2]-(l/2)+l);        // Second Point Of The Triangle
    glVertex3d(strg.p[0]+l-(l/2), strg.p[1]+l-(l/2), strg.p[2]-(l/2)+l);		// Third Point Of The Triangle
	glVertex3d(strg.p[0]-(l/2), strg.p[1]+l-(l/2), strg.p[2]-(l/2)+l);
	//links
	glNormal3d(-1,0,0);
	glVertex3d(strg.p[0]-(l/2), strg.p[1]-(l/2), strg.p[2]-(l/2));			// First Point Of The Triangle
	glVertex3d(strg.p[0]-(l/2), strg.p[1]-(l/2), strg.p[2]-(l/2)+l);        // Second Point Of The Triangle
    glVertex3d(strg.p[0]-(l/2), strg.p[1]+l-(l/2), strg.p[2]-(l/2)+l);		// Third Point Of The Triangle
	glVertex3d(strg.p[0]-(l/2), strg.p[1]+l-(l/2), strg.p[2]-(l/2));
	//oben
	//////////////////////////////////////////
	/*
	//oben
	glNormal3d(0,1,0);
	glVertex3d(strg.p[0]-(l/2), strg.p[1]+l-(l/2), strg.p[2]-(l/2));			// First Point Of The Triangle
	glVertex3d(strg.p[0]-(l/2), strg.p[1]+l-(l/2), strg.p[2]-(l/2)+l);        // Second Point Of The Triangle
    glVertex3d(strg.p[0]+l-(l/2), strg.p[1]+l-(l/2),strg.p[2]-(l/2)+l);
	glVertex3d(strg.p[0]+l-(l/2), strg.p[1]+l-(l/2), strg.p[2]-(l/2));
	*/
	/////////////////////////////////////////
	//rechts
	glNormal3d(1,0,0);
	glVertex3d(strg.p[0]+l-(l/2), strg.p[1]-(l/2), strg.p[2]-(l/2));			// First Point Of The Triangle
	glVertex3d(strg.p[0]+l-(l/2), strg.p[1]-(l/2), strg.p[2]-(l/2)+l);        // Second Point Of The Triangle
    glVertex3d(strg.p[0]+l-(l/2), strg.p[1]+l-(l/2), strg.p[2]-(l/2)+l);
	glVertex3d(strg.p[0]+l-(l/2), strg.p[1]+l-(l/2), strg.p[2]-(l/2));
	//unten
	glNormal3d(0,-1,0);
	glVertex3d(strg.p[0]-(l/2), strg.p[1]-(l/2), strg.p[2]-(l/2));			// First Point Of The Triangle
	glVertex3d(strg.p[0]-(l/2), strg.p[1]-(l/2), strg.p[2]-(l/2)+l);        // Second Point Of The Triangle
    glVertex3d(strg.p[0]+l-(l/2), strg.p[1]-(l/2), strg.p[2]-(l/2)+l);
	glVertex3d(strg.p[0]+l-(l/2), strg.p[1]-(l/2), strg.p[2]-(l/2));
	glEnd();

	}

void drawDeckel(Vec3 strg, double l){

		glBegin(GL_QUADS);											// Start Drawing A Triangle
		glNormal3d(0,1,0);

		glVertex3d(strg.p[0]-(l/2), strg.p[1]+l-(l/2), strg.p[2]-(l/2));			// First Point Of The Triangle
		glVertex3d(strg.p[0]-(l/2), strg.p[1]+l-(l/2), strg.p[2]-(l/2)+l);        // Second Point Of The Triangle
	    glVertex3d(strg.p[0]+l-(l/2), strg.p[1]+l-(l/2),strg.p[2]-(l/2)+l);
		glVertex3d(strg.p[0]+l-(l/2), strg.p[1]+l-(l/2), strg.p[2]-(l/2));
		glEnd();

}

void SetMaterialColor(int side, double r, double g, double b) {
  float	amb[4], dif[4], spe[4];
  int mat;

  dif[0] = r;
  dif[1] = g;
  dif[2] = b;

  for(int i = 0; i < 3; i++) {
    amb[i] = .1 * dif[i];
    spe[i] = .5;
  }
  amb[3] = dif[3] = spe[3] = 1.0;

  switch(side){
    case 1:	mat = GL_FRONT;
      break;
    case 2:	mat = GL_BACK;
      break;
    default: mat = GL_FRONT_AND_BACK;
  }

  glMaterialfv(mat, GL_AMBIENT, amb);
  glMaterialfv(mat, GL_DIFFUSE, dif);
  glMaterialfv(mat, GL_SPECULAR, spe);
  glMaterialf( mat, GL_SHININESS, 20);
}



// set viewport transformations and draw objects
void InitLighting() {
  GLfloat lp1[4]  = { 10,  5,  10,  0};
  GLfloat lp2[4]  = { -5,  5, -10,  0};
  GLfloat red[4]  = {1.0, .8,  .8,  1};
  GLfloat blue[4] = { .8, .8, 1.0,  1};

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  glClearColor(1, 1, 1, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glShadeModel(GL_SMOOTH);
  glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 1);
  glEnable(GL_LIGHTING);

  glLightfv(GL_LIGHT1, GL_POSITION, lp1);
  glLightfv(GL_LIGHT1, GL_DIFFUSE,  red);
  glLightfv(GL_LIGHT1, GL_SPECULAR, red);
  glEnable(GL_LIGHT1);

  glLightfv(GL_LIGHT2, GL_POSITION, lp2);
  glLightfv(GL_LIGHT2, GL_DIFFUSE,  blue);
  glLightfv(GL_LIGHT2, GL_SPECULAR, blue);
  glEnable(GL_LIGHT2);

  glClearColor(1, 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // init viewport to canvassize
  glViewport(0, 0, window_width_, window_height_);

  // init coordinate system
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-15, 15, -10, 10, -20, 20);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}



// draw the entire scene
void Preview() {

  glMatrixMode(GL_MODELVIEW);


  glLoadIdentity();				// Reset The Current Modelview Matrix
                                  // since camera is at origin
  glRotated(alpha_x, 0, 1, 0);
  glRotated(alpha_y, 1, 0, 0);
  glScaled(xScale, yScale, zScale);
  glPushMatrix();
      SetMaterialColor(2, 0, .35, 0);
      SetMaterialColor(1, 0.3, 0.2, 0.1);
      Table table;
      table.drawTable();
  glPopMatrix();



  //pushmartix & popmatrix mehrere koordinatensysteme
  /*old glPushMatrix();
  	glTranslatef(0,1,-1);
  	glRotated(alpha_z, 1, 0, 0);


  	glTranslatef(0,-1,-1);
  	SetMaterialColor( 1, 1, 0, 0);
  	drawDeckel( Vec3( 0, 0, 0), 2);
  	glPopMatrix();

*/
}

void rotate_W(int wert)
{
	 alpha_x += wert;
}

void rotate_H(int wert)
{
	 alpha_y += wert;
}
void rotate_D(int wert){

	alpha_y += wert;
}

void d_open(){
	if(alpha_z < 70 ){
		for(int i=0;i<=70;i++){alpha_z += .1;}
	}
	else alpha_z = 70;
}
void d_close(){
	if(alpha_z >= 0)
		{for(int i=0;i<=70;i++){alpha_z -= .1;}
		}
	else alpha_z = 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_D && (action == GLFW_PRESS || action == GLFW_REPEAT)){
        rotate_W(1);
    }else if(key == GLFW_KEY_A && (action == GLFW_PRESS || action == GLFW_REPEAT)){
    	rotate_W(-1);
    }else if(key == GLFW_KEY_W && (action == GLFW_PRESS || action == GLFW_REPEAT)){
    	rotate_H(-1);
    }else if(key == GLFW_KEY_S && (action == GLFW_PRESS || action == GLFW_REPEAT)){
    	rotate_H(1);
    }else if(key == GLFW_KEY_O && (action == GLFW_PRESS || action == GLFW_REPEAT)){
    	d_open();
    }else if(key == GLFW_KEY_C && (action == GLFW_PRESS || action == GLFW_REPEAT)){
    	d_close();
    }else if(key == GLFW_KEY_PAGE_UP && (action == GLFW_PRESS || action == GLFW_REPEAT)){
    	xScale+=0.2;
    	yScale+=0.2;
    	zScale+=0.2;
    	printf("plus");
    }else if(key == GLFW_KEY_PAGE_DOWN && (action == GLFW_PRESS || action == GLFW_REPEAT)){
    	xScale-=0.5;
    	yScale-=0.5;
    	zScale-=0.5;
    	printf("minus");
    }
}

int main() {
  GLFWwindow* window = NULL;

  printf("Here we go!\n");

  if(!glfwInit()){
    return -1;
  }

  window = glfwCreateWindow(window_width_, window_height_,
                            "Simple 3D Animation", NULL, NULL);
  if(!window) {
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);

  while(!glfwWindowShouldClose(window)) {
    // switch on lighting (or you don't see anything)
    InitLighting();

    // set background color
    glClearColor(0.8, 0.8, 0.8, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // draw the scene
    Preview();

    // make it appear (before this, it's hidden in the rear buffer)
    glfwSwapBuffers(window);

    glfwPollEvents();

    glfwSetKeyCallback(window, key_callback);

  }

  glfwTerminate();

  printf("Goodbye!\n");

  return 0;
}
