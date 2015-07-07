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
#include <typeinfo>
#include "vec3.hpp"
#include "./objects/table.h"
#include "./objects/cylinder.h"
#include "./objects/sphere.h"
#include "./objects/quader.h"
#include "./objects/circle.h"
#include "./objects/object.h"
#include <time.h>

using namespace std;

static double rotate_x = 0;
static double rotate_y = 90;
//static double alpha_z = 0;
static double window_width_ = 800;
static double window_height_ = 600;
static double scale = 1, c = 0, d = 0, e = 0;


// Objects
Table table;
Sphere *sphere1 = new Sphere();
Quader wall;
Quader target;
Quader ziel;
double z=0;

double spherePositionX = -4, spherePositionY = 0, defaultSpeed = .001 , sphereSpeed = defaultSpeed;
double directionX = 1;
double directionY = 0;
bool sphereStart = false;
bool zielSichtbar = true;

// Dynamic Objects
const int allowedObjects = 5;
Quader *quader[allowedObjects];
int quaderId = 0;
bool quaderCreated[allowedObjects] = {false};
Sphere *sphere[allowedObjects];
int sphereId = 0;
bool sphereCreated[allowedObjects] = {false};
Cylinder *cylinder[allowedObjects];
Circle *circle[allowedObjects];
int cylinderId = 0;
bool cylinderCreated[allowedObjects] = {false};
int objectZ = 15;
double objectZAnimation = objectZ;

// Switchable Objects (Quader, Sphere, Cylinder)
vector<Object*> selectableObjects;
unsigned int selectedObjectId = 0;

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
			double dirX = directionX;
			double dirY = directionY;
			spherePositionX += sphereSpeed * dirX;
			spherePositionY += sphereSpeed * dirY;
			if(sphereSpeed >= 0) {
				sphereSpeed -= .0000005;
			}
		}
		sphere1->setX(spherePositionX);
		sphere1->setY(spherePositionY);
		sphere1->draw();
	glPopMatrix();

	// feste Mauer
	glPushMatrix();
		SetMaterialColor(1, .3, .2, .1);
		wall.setX(4);
		wall.setY(5);
		wall.setXWidth(.5);
		wall.setYWidth(10);
		wall.draw();
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
	if(zielSichtbar){
		glPushMatrix();
			SetMaterialColor(1, 1, 0, 0);
			ziel.setX(-8);
			ziel.setY(.25);
			ziel.setH(.0005);
			ziel.draw();
		glPopMatrix();
	}
}


void checkCollision() {

	// Kollisionsverhalten

	// aktuelle Position der Kugel
	double Sx = (sphere1->getX() + sphere1->getR() / 2) * 2;
	double Sy = sphere1->getY() + sphere1->getR() / 2;
	double Sr = sphere1->getR();

	for(int i = 0; i < allowedObjects; i++) {

		double Qx = quader[i]->getX();
		double Qxw = quader[i]->getXWidth();
		double Qy = quader[i]->getY();
		double Qyw = quader[i]->getYWidth();
		double Qz = quader[i]->getZ();

		if( Sx - Qxw*2 < Qx && Sx > Qx && Qz < 1 ){
			if(Sy - .75 < Qy && Sy + 1.25 > Qy && Qz < 1){
				directionX = -directionX;
				cout << "collision  with Quader" << endl;
				cout << "collision  with Quader" << endl;
			}
		}

//		 alternativ:

//		if( Sx - quader[0]->getXWidth()*2 < Qx && Sx > Qx && Qz < 1 ){
//			if(Sy - .75 < Qy && Sy + 1.25 > Qy && Qz < 1){
//				directionY = -directionY;
//				cout << "collision  with Y--------------------Quader" << endl;
//			}
//		}

		double Cx = cylinder[i]->getX();
		double Cy = cylinder[i]->getY();
		double Cz = cylinder[i]->getZ();

		if(Sx - 1 < Cx && Sx + .25 > Cx && Cz < 1){
			if(Sy - 1.25 < Cy && Sy + .75 > Cy && Cz < 1){
				directionX = -directionX;
				cout << "collision  with Cylinder " << endl;
			}
		}

		double Spx = sphere[i]->getX();
		double Spy = sphere[i]->getY();
		double Spz = sphere[i]->getZ();

		if(Sx - 1 < Spx && Sx + .25 > Spx && Spz < 1){
			if(Sy - 1.25 < Spy && Sy + .75 > Spy && Spz < 1){
				directionX = -directionX;
				cout << "collision  with Sphere" << endl;
			}
		}
	}

	//Sphere im Ziel?
	bool x = target.collsXZiel(Sx);
	bool y = target.collsYZiel(Sy);
	bool testColls = false;
	testColls = target.collsZiel(Sx, Sy);
	if(x){
		if(testColls){
			SetMaterialColor(1, 0, 0, 1);
			glPushMatrix();
				target.setX(5.25);
				target.setY(2);
				target.setH(.0005);
				target.draw();
				target.setXWidth(4);
				target.setYWidth(4);
			glPopMatrix();
		}
	}else if(y){
		if(testColls){
			SetMaterialColor(1, 0, 0, 1);
			glPushMatrix();
				target.setX(5.25);
				target.setY(2);
				target.setH(.0005);
				target.draw();
				target.setXWidth(4);
				target.setYWidth(4);
			glPopMatrix();
		}
	}
	SetMaterialColor(1, 0, 1, 0);

//  Kollision mit der festen Mauer
	if( Sx - sphere1->getR()*2 < wall.getX() + wall.getXWidth() && Sx > wall.getX()){
		if(Sy - Sr < wall.getY() && Sy - Sr  > wall.getX() - wall.getYWidth()){
			directionX = -directionX;
			cout << "Collision with wall" << endl;
		}
	}
	// Kollision mit dem Tisch in X
	if(Sx <= -9 || Sx >= 10) {
		directionX = -directionX;
		cout << "Collision with table X" << endl;
	}
	// Kollision mit dem Tisch in Y
	if(Sy >= 6.75 || Sy <= -6.75){
		directionY = -directionY;
		cout << "Collision with table Y" << endl;
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

  checkCollision();

  createWorld();

  // Draw createable Objects
  for (int i = 0; i < allowedObjects; i++)
  {
	  if(objectZAnimation > 0) {
		  objectZAnimation -= 0.01;
	  }
	  if(quaderCreated[i]) {
		  glPushMatrix();
			  quader[i]->draw();
			  quader[i]->setZ(objectZAnimation);
		  glPopMatrix();
	  }
	  if(cylinderCreated[i]) {
		  glPushMatrix();
			  cylinder[i]->draw();
			  cylinder[i]->setZ(objectZAnimation);
			  circle[i]->draw();
			  circle[i]->setZ(objectZAnimation);
		  glPopMatrix();
	  }
	  if(sphereCreated[i]) {
		  glPushMatrix();
			  sphere[i]->draw();
			  sphere[i]->setZ(objectZAnimation);
		  glPopMatrix();
	  }
  }
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
	//Spiel verlassen und Fenster schlieﬂen
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
			selectableObjects.push_back(quader[quaderId]);
			quaderCreated[quaderId] = true;
			quaderId++;
			// output and save ID
			quader[quaderId-1]->setId(quaderId);
			cout << "Quader " << quaderId << " created"<< endl;
			// select this as current object to move and scale
			selectedObjectId = selectableObjects.size()-1;
			objectZAnimation = objectZ;
    	} else {
    		cout << "No more Quaders can be added" << endl;
    	}
    }else if(key == GLFW_KEY_2 && (action == GLFW_PRESS || action == GLFW_REPEAT)){	// sphere erzeugen
    	if(sphereId < allowedObjects) {
			// save sphere
			selectableObjects.push_back(sphere[sphereId]);
			sphereCreated[sphereId] = true;
			sphereId++;
			// output and save ID
			sphere[sphereId-1]->setId(sphereId);
			cout << "Sphere " << sphereId << " created"<< endl;
			// select this as current object to move and scale
			selectedObjectId = selectableObjects.size()-1;
			objectZAnimation = objectZ;
		} else {
			cout << "No more Spheres can be added" << endl;
		}
    }else if(key == GLFW_KEY_3 && (action == GLFW_PRESS || action == GLFW_REPEAT)){	// cylinder erzeugen
    	if(cylinderId < allowedObjects) {
			// save cylinder
			selectableObjects.push_back(cylinder[cylinderId]);
			cylinderCreated[cylinderId] = true;
			cylinderId++;
			// output and save ID
			cylinder[cylinderId-1]->setId(cylinderId);
			cout << "Cylinder  " << cylinderId << " created"<< endl;
			// select this as current object to move and scale
			selectedObjectId = selectableObjects.size()-1;
			objectZAnimation = objectZ;
		} else {
			cout << "No more Cylinders can be added" << endl;
		}
    }else if(key == GLFW_KEY_N && (action == GLFW_PRESS || action == GLFW_REPEAT)){ // objektauswahl zur¸ck
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
    }else if(key == GLFW_KEY_Y && (action == GLFW_PRESS || action == GLFW_REPEAT)){ // rotate -
		if (ziel.degree > -45) {
			ziel.rotate(-5);
			directionY -= .2;
			cout << "Degree: " << ziel.degree << endl;
		}
		else { cout << "Stop" << endl;}
	}else if(key == GLFW_KEY_X && (action == GLFW_PRESS || action == GLFW_REPEAT)){ // rotate -
		if (ziel.degree < 45) {
			ziel.rotate(5);
			directionY += .2;
			cout << "Degree: " << ziel.degree << endl;
		}
		else { cout << "Stop" << endl;}
    }else if(key == GLFW_KEY_Z && (action == GLFW_PRESS || action == GLFW_REPEAT)){ // rotate -
    	if(zielSichtbar){
    		zielSichtbar = false;
    		return;
    	}zielSichtbar = true;
	}else if(key == GLFW_KEY_C && (action == GLFW_PRESS || action == GLFW_REPEAT)){ // rotate -
		ziel.xWidth -= .2;
		sphereSpeed -= .0002;
	}else if(key == GLFW_KEY_V && (action == GLFW_PRESS || action == GLFW_REPEAT)){ // rotate -
		ziel.xWidth += .2;
		sphereSpeed += .0002;

	}else if(key == GLFW_KEY_SPACE && (action == GLFW_PRESS || action == GLFW_REPEAT)) { // Kugel starten
    	cout << "Sphere start" << endl;
    	sphereStart = true;
    	zielSichtbar = false;
    	//cout << "Sphere stop" << endl;
    }else if(key == GLFW_KEY_BACKSPACE && (action == GLFW_PRESS || action == GLFW_REPEAT)) { // Alles zur¸cksetzen
    	cout << " --------- Game reset --------- " << endl;
    	selectableObjects.clear();
    	selectedObjectId = 0;
    	delete sphere1;
    	sphere1 = new Sphere();
    	memset(quader, '\0', sizeof(quader));
    	memset(sphere, '\0', sizeof(sphere));
    	memset(cylinder, '\0', sizeof(cylinder));
    	memset(circle, '\0', sizeof(circle));
    	for (int i = 0; i < allowedObjects; i++) {
    		quader[i] = new Quader();
    		quaderId = 0;
    		quaderCreated[i] = false;
    		quader[i]->setZ(objectZ);
    		sphere[i] = new Sphere();
    		sphereId = 0;
    		sphereCreated[i] = false;
    		sphere[i]->setZ(objectZ);
			cylinder[i] = new Cylinder();
			cylinderId = 0;
			cylinderCreated[i] = false;
			cylinder[i]->setZ(objectZ);
			circle[i] = new Circle();
			circle[i]->setZ(objectZ);
    	}
    	spherePositionX = -4, spherePositionY = 0, sphereSpeed = defaultSpeed;
    	directionX = 1;
    	directionY = 0;
    	ziel.degree = 0;
    	zielSichtbar = true;
    	ziel.setXWidth(1);
    	sphereStart = false;
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

  // Init Arrays with Objects
  for (int i = 0; i < allowedObjects; i++) {
	quader[i] = new Quader();
	sphere[i] = new Sphere();
	cylinder[i] = new Cylinder();
	circle[i] = new Circle();
	quader[i]->setZ(objectZ);
	sphere[i]->setZ(objectZ);
	cylinder[i]->setZ(objectZ);
	circle[i]->setZ(objectZ);
  }

	ziel.setXWidth(1);
	ziel.setYWidth(.5);

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
