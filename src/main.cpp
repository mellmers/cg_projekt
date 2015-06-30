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
#include <vector>
#include "vec3.hpp"
#include "./objects/table.h"
#include "./objects/cylinder.h"
#include "./objects/sphere.h"
#include "./objects/quader.h"
#include "./objects/circle.h"
#include "./objects/object.h"

using namespace std;

static double rotate_x = 0;
static double rotate_y = 90;
//static double alpha_z = 0;
static double window_width_ = 800;
static double window_height_ = 600;
static double scale = 1, c = 0, d = 0, e = 0;


// Objects
Table table;
Sphere sphere1;
Quader wall;
Quader target;

double spherePositionX = -4, spherePositionY = 0, sphereSpeed = .005;
int direction = 1;
bool sphereStart = false;

// Dynamic Objects
const int allowedObjects = 5;
Quader quader[allowedObjects];
int quaderId = 0;
bool quaderCreated[allowedObjects] = {false};
Sphere sphere[allowedObjects];
int sphereId = 0;
bool sphereCreated[allowedObjects] = {false};
Cylinder cylinder[allowedObjects];
Circle circle[allowedObjects];
int cylinderId = 0;
bool cylinderCreated[allowedObjects] = {false};

// Switchable Objects (Quader, Sphere, Cylinder)
vector<Object*> selectableObjects;
int selectedObjectId = 0;

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
	// Table
	glPushMatrix();
		SetMaterialColor(2, 0, .35, 0);
		SetMaterialColor(1, .3, .2, .1);
		table.drawTable();
	glPopMatrix();

	// Kugel
	glPushMatrix();
		SetMaterialColor(3, 1, 1, 1);
		if(sphereStart) {
			if(true){ // wenn Collision, dann Richtung �ndern

			}
			spherePositionX += sphereSpeed * direction;
			//spherePositionY += sphereSpeed * direction;
			if(sphereSpeed >= 0) {
				sphereSpeed -= .000001;
			}
		}
		sphere1.draw(Vec3(spherePositionX,0,spherePositionY));
	glPopMatrix();

	// feste Mauer
	glPushMatrix();
		SetMaterialColor(1, .3, .2, .1);
		wall.setX(4);
		wall.setY(6);
		wall.draw();
		wall.setXWidth(.5);
		wall.setYWidth(12);
	glPopMatrix();

	// Zielbereich
	glPushMatrix();
		SetMaterialColor(1, 0, 1, 0);
		target.setX(5.25);
		target.setY(2);
		target.setH(.0005);
		target.draw();
		target.setXWidth(4);
		target.setYWidth(4);
	glPopMatrix();
}


void controls() {

	//Kollisionsverhalten
	//kollision mit dem W�rfel
	bool testCol, x,y = false;
	x = quader->collsX(sphere1.x);
	y = quader->collsX(sphere1.y);
	cout << sphere1.getX()<<endl;
	testCol = quader->collsQuader(sphere1.x, sphere1.y);
	if(x){
		std::cout << "collision mit X";
	}else if(y){
		std::cout << "collision mit Y";
	}

}

// draw the entire scene
void Preview() {

  glMatrixMode(GL_MODELVIEW);


  glLoadIdentity();				// Reset The Current Modelview Matrix
                                // since camera is at origin

  // Welt Rotation und Skalierung
  glRotated(rotate_x, 0, 1, 0);
  glRotated(rotate_y, 1, 0, 0);

  glScaled(scale, scale, scale);

  createWorld();

  // Draw createable Objects
  for (int i = 0; i < allowedObjects; i++)
  {
	  if(quaderCreated[i]) {
		  glPushMatrix();
			  quader[i].draw();
		  glPopMatrix();
	  }
	  if(cylinderCreated[i]) {
		  glPushMatrix();
			  cylinder[i].draw();
			  circle[i].draw();
		  glPopMatrix();
	  }
	  if(sphereCreated[i]) {
		  glPushMatrix();
			  sphere[i].draw(Vec3(0,sphere[i].getR(),0));
		  glPopMatrix();
	  }
  }

  controls();



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

bool vecEmpty() {
	if(selectableObjects.empty()) {
		cout << "SelectableObjects is empty. Please create an object." << endl;
		return true;
	}
	else if(selectedObjectId >= selectableObjects.size()) {
		selectedObjectId = 0;
		return false;
	}
	return false;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	//Spiel verlassen und Fenster schlie�en
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
		glfwSetWindowShouldClose(window, GL_TRUE);
	}else if (key == GLFW_KEY_D && (action == GLFW_PRESS || action == GLFW_REPEAT)){ // world rotate
        rotate_W(1);
    }else if(key == GLFW_KEY_A && (action == GLFW_PRESS || action == GLFW_REPEAT)){ // world rotate
    	rotate_W(-1);
    }else if(key == GLFW_KEY_W && (action == GLFW_PRESS || action == GLFW_REPEAT)){ // world rotate
    	rotate_H(-1);
    }else if(key == GLFW_KEY_S && (action == GLFW_PRESS || action == GLFW_REPEAT)){ // world rotate
    	rotate_H(1);
    }else if(key == GLFW_KEY_1 && (action == GLFW_PRESS || action == GLFW_REPEAT)){	// quader erzeugen
    	if(quaderId < allowedObjects) {
    		// save Quader
			selectableObjects.push_back(&quader[quaderId]);
			quaderCreated[quaderId] = true;
			quaderId++;
			// output and save ID
			quader[quaderId-1].setId(quaderId);
			cout << "Quader " << quaderId << " created"<< endl;
			// select this as current object to move and scale
			selectedObjectId = selectableObjects.size()-1;
    	} else {
    		cout << "No more Quaders can be added" << endl;
    	}
    }else if(key == GLFW_KEY_2 && (action == GLFW_PRESS || action == GLFW_REPEAT)){	// cylinder erzeugen
    	if(cylinderId < allowedObjects) {
			// save cylinder
			selectableObjects.push_back(&cylinder[cylinderId]);
			cylinderCreated[cylinderId] = true;
			cylinderId++;
			// output and save ID
			cylinder[cylinderId-1].setId(cylinderId);
			cout << "Cylinder  " << cylinderId << " created"<< endl;
			// select this as current object to move and scale
			selectedObjectId = selectableObjects.size()-1;
		} else {
			cout << "No more Cylinders can be added" << endl;
		}
    }else if(key == GLFW_KEY_3 && (action == GLFW_PRESS || action == GLFW_REPEAT)){	// sphere erzeugen
    	if(sphereId < allowedObjects) {
			// save sphere
			selectableObjects.push_back(&sphere[sphereId]);
			sphereCreated[sphereId] = true;
			sphereId++;
			// output and save ID
			sphere[sphereId-1].setId(sphereId);
			cout << "Sphere " << sphereId << " created"<< endl;
			// select this as current object to move and scale
			selectedObjectId = selectableObjects.size()-1;
		} else {
			cout << "No more Spheres can be added" << endl;
		}
    }else if(key == GLFW_KEY_N && (action == GLFW_PRESS || action == GLFW_REPEAT)){ // objektauswahl zur�ck
		if (!vecEmpty()) {
			selectedObjectId--;
			if(selectedObjectId < 0) {
				selectedObjectId = selectableObjects.size()-1;
			}
			cout << "SelectedObject: " << selectableObjects.at(selectedObjectId)->getObjectType() << " " << selectableObjects.at(selectedObjectId)->getId() << endl;
		}
    }else if(key == GLFW_KEY_M && (action == GLFW_PRESS || action == GLFW_REPEAT)){	// objektauswahl vor
		if (!vecEmpty()) {
			selectedObjectId++;
			if(selectedObjectId > selectableObjects.size()-1) {
				selectedObjectId = 0;
			}
			cout << "SelectedObject: " << selectableObjects.at(selectedObjectId)->getObjectType() << " " << selectableObjects.at(selectedObjectId)->getId() << endl;
		}
    }else if(key == GLFW_KEY_LEFT && (action == GLFW_PRESS || action == GLFW_REPEAT)){ // move -x
    	if(!vecEmpty()) {
    		selectableObjects.at(selectedObjectId)->move(-.1,0);
    	}
    }else if(key == GLFW_KEY_RIGHT && (action == GLFW_PRESS || action == GLFW_REPEAT)){ // move x
    	if(!vecEmpty()) {
    		selectableObjects.at(selectedObjectId)->move(.1, 0);
    	}
    }else if(key == GLFW_KEY_UP && (action == GLFW_PRESS || action == GLFW_REPEAT)){ // move y
    	if(!vecEmpty()) {
    		selectableObjects.at(selectedObjectId)->move(0, .1);
    	}
    }else if(key == GLFW_KEY_DOWN && (action == GLFW_PRESS || action == GLFW_REPEAT)){ // move -y
    	if(!vecEmpty()) {
    		selectableObjects.at(selectedObjectId)->move(0, -.1);
    	}
    }else if(key == GLFW_KEY_PAGE_UP && (action == GLFW_PRESS || action == GLFW_REPEAT)){ // zoom in world
    	scale+=0.2;
    	cout << "ZoomIn" << endl;
    }else if(key == GLFW_KEY_PAGE_DOWN && (action == GLFW_PRESS || action == GLFW_REPEAT)){ // zoom out world
    	scale-=0.2;
    	cout <<"ZoomOut" << endl;
    }else if(key == GLFW_KEY_KP_ADD && (action == GLFW_PRESS || action == GLFW_REPEAT)){ // scale +
    	if(!vecEmpty()) {
			selectableObjects.at(selectedObjectId)->scale(.1);
		}
    }else if(key == GLFW_KEY_KP_SUBTRACT && (action == GLFW_PRESS || action == GLFW_REPEAT)){ // scale -
    	if(!vecEmpty()) {
			selectableObjects.at(selectedObjectId)->scale(-.1);
		}
    }else if(key == GLFW_KEY_R && (action == GLFW_PRESS || action == GLFW_REPEAT)){ // rotate +
    	if(!vecEmpty()) {
			selectableObjects.at(selectedObjectId)->rotate(5);
		}
    }else if(key == GLFW_KEY_E && (action == GLFW_PRESS || action == GLFW_REPEAT)){ // rotate -
    	if(!vecEmpty()) {
			selectableObjects.at(selectedObjectId)->rotate(-5);
		}
    }else if(key == GLFW_KEY_SPACE && (action == GLFW_PRESS || action == GLFW_REPEAT)) { // Kugel starten
    	cout << "Kugel startet" << endl;
    	sphereStart = true;
    	//cout << "Kugel steht still" << endl;
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
