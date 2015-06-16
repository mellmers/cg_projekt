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
#include <iostream>
#include "vec3.hpp"
#include "./objects/table.h"
#include "./objects/cylinder.h"
#include "./objects/sphere.h"

using namespace std;

static double rotate_x = 0;
static double rotate_y = 90;
//static double alpha_z = 0;
static double window_width_ = 1024;
static double window_height_ = 768;
static double scale = 1, c = 0, d = 0, e = 0;


// Objects
Table table;
Cylinder cylinder;
Sphere sphere;


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

      // Perspektive:
      glFrustum(-4,4,-3,3,10,300);
      // Kameraposition
      glTranslated(c, d,-28+e);

      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();
}

void createWorld() {
	glPushMatrix();
		SetMaterialColor(2, 0, .35, 0);
		SetMaterialColor(1, 0.3, 0.2, 0.1);
		table.drawTable();
	glPopMatrix();

	glPushMatrix();
		SetMaterialColor(2, 1, 0, 0);
		SetMaterialColor(1, 0, 1, 0);
		cylinder.draw(Vec3(100,100,100));
	glPopMatrix();

	glPushMatrix();
		SetMaterialColor(3, 1, 1, 1);
		sphere.draw(Vec3(0,.2,0),.2);
	glPopMatrix();
}

// draw the entire scene
void Preview() {

  glMatrixMode(GL_MODELVIEW);


  glLoadIdentity();				// Reset The Current Modelview Matrix
                                // since camera is at origin
  glRotated(rotate_x, 0, 1, 0);
  glRotated(rotate_y, 1, 0, 0);
  glScaled(scale, scale, scale);

  createWorld();

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
	 rotate_x += wert;
	 cout << "Rotate X: " << rotate_x << endl;
}

void rotate_H(int wert)
{
	 rotate_y += wert;
	 cout << "Rotate Y: " << rotate_y << endl;
}
/*
 * wird bisher nicht benutzt

void rotate_D(int wert){

	rotate_y += wert;
	cout << "Rotate Y: " << rotate_y << endl;
}
*/

/*
 * Brauchen wir open und close??

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
*/

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
    }
    /*else if(key == GLFW_KEY_O && (action == GLFW_PRESS || action == GLFW_REPEAT)){
    	d_open();
    }else if(key == GLFW_KEY_C && (action == GLFW_PRESS || action == GLFW_REPEAT)){
    	d_close();
    }*/
    else if(key == GLFW_KEY_PAGE_UP && (action == GLFW_PRESS || action == GLFW_REPEAT)){
    	scale+=0.2;
    	cout << "ZoomIn" << endl;
    }else if(key == GLFW_KEY_PAGE_DOWN && (action == GLFW_PRESS || action == GLFW_REPEAT)){
    	scale-=0.2;
    	cout <<"ZoomOut" << endl;
    }
}

int main() {
  GLFWwindow* window = NULL;

  cout << "Here we go!" << endl;

  if(!glfwInit()){
    return -1;
  }

  window = glfwCreateWindow(window_width_, window_height_,
                            "Minigolf", NULL, NULL);
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

  cout << "Goodbye!" << endl;

  return 0;
}
