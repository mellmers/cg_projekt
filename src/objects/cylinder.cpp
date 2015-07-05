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

Cylinder::~Cylinder(){}

bool Cylinder::collsCylinder(double SphereX, double SphereY){
	SphX = SphereX, SphY = SphereY;
	if(SphX-(r+.5) < x && SphX+(r+.5) > x && this->getZ() < 1){  		//x Wert  des Objektes überprüft mit Kugelradius .5
		if(SphY-(r+.5) < y && SphY+(r+.5) > y ){ 	//y Wert des Objekt überprüft
			collisionY = true;
		}else{
			collisionY = false;
		}
		collisionX = true;
	}else{
		collisionX = false;
	}
	if(collisionX && collisionY){
		return true;
	} else {
		return false;
	}
}

bool Cylinder::collsX(double SphereX){
	SphX = SphereX;
	if(SphX-(r+.5) < x && SphX+(r+.5) > x && this->getZ() < 1) {
		return true;
	} else {
		return false;
	}
}

bool Cylinder::collsY(double SphereY){
	SphY = SphereY;
	if(SphY-(r+.5) < y && SphY+(r+.5) > y && this->getZ() < 1) {
		return true;
	} else {
		return false;
	}
}

void Cylinder::draw(){

	glTranslated(x, z, -y);
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
