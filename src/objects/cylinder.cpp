/*
 * cylinder.cpp
 *
 *  Created on: 09.06.2015
 *      Author: Mo
 */

#include "cylinder.h"

Cylinder::Cylinder() : Object(){
	x = 1;
	cout << "Cylinder created" << endl;
	setObjectType("Cylinder");
}

Cylinder::~Cylinder(){
}

bool Cylinder::colCylinder(double gameSphereX, double gameSphereZ){
	sphereX = gameSphereX, sphereZ = gameSphereZ;
	if(sphereX-0.8 < x && sphereX+0.8 > x) {
		if(sphereZ-0.8 < h && sphereZ+0.8 > h) {
			collisionZ = true;
		} else {
			collisionZ = false;
		}
		collisionX = true;
	} else {
		collisionX = false;
	}
	if(collisionX && collisionZ){
		return true;
	} else {
		return false;
	}
}

bool Cylinder::colX(double gameSphereX){
	sphereX = gameSphereX;
	if(sphereX-0.8 < x && sphereX+0.8 > x) {

		return true;
	} else {
		return false;
	}
}

bool Cylinder::colZ(double gameSphereZ){
	sphereX = gameSphereZ;
	if(sphereZ-0.8 < h && sphereZ+0.8 > h) {
		return true;
	} else {
		return false;
	}
}

bool Cylinder::colFinish(double gameSphereX, double gameSphereZ){
	sphereX = gameSphereX, sphereZ = gameSphereZ;
	if(sphereX-0.25 < x && sphereX+0.25 > x) {
		if(sphereZ-0.25 < h && sphereZ+0.25 > h) {
			collisionZ = true;
		} else {
			collisionZ = false;
		}
		return collisionX = true;
	} else {
		return collisionX = false;
	}
}


void Cylinder::draw(){

	glTranslated(x, 0, -y);
	glRotated(degree, 0, 1, 0);
	glScaled(s, s, s);
    
    glBegin(GL_QUAD_STRIP);
    for( double angle = 0; angle < 2*M_PI + 1; angle += (M_PI / 360.0) ) {
        
        glVertex3f(
                   ( r*(cos(angle)*1) ),
                   ( (0)  ),
                   ( r*(sin(angle)*1) )
                   );
        
        
        glVertex3f(
                   ( r*(cos(angle)*1) ),
                   ( (h)  ),					// zylinder höhe
                   ( r*(sin(angle)*1) )
                   );
    }
    glEnd ();
}
