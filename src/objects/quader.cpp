/*
 * quader.cpp
 *
 *  Created on: 16.06.2015
 *      Author: Mo
 */

#include "quader.h"

Quader::Quader() : Object(){
	x = -1.5;
	y = .5;
	cout << "Quader created" << endl;
	setObjectType("Quader");
}

Quader::~Quader(){}

bool Quader::collsQuader(double SphereX, double SphereY){
	SphX = SphereX, SphY = SphereY;
	if(SphX-2 < x && SphX > x && this->getZ() < 1){  		//x Wert  des Objektes �berpr�ft mit Kugelradius .5
		if(SphY-.8 < y && SphY+1.3 > y && this->getZ() < 1){ 	//y Wert des Objekt �berpr�ft
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

bool Quader::collsX(double SphereX){
	SphX = SphereX;
	if(SphX-2< x && SphX > x && this->getZ() < 1){
		return true;
	} else {
		return false;
	}
}

bool Quader::collsY(double SphereY){
	SphY = SphereY;
	if(SphY-.8 < y && SphY+1.3 > y && this->getZ() < 1){
		return true;
	} else {
		return false;
	}
}

bool Quader::collsZiel(double SphereX, double SphereY){
	SphX = SphereX, SphY = SphereY;
	if(SphX-4 < x && SphX > x && this->getZ() < 1){  		//x Wert  des Objektes �berpr�ft mit Kugelradius .5
		if(SphY-1 < y && SphY+4.5 > y && this->getZ() < 1){ 	//y Wert des Objekt �berpr�ft
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

bool Quader::collsXZiel(double SphereX){
	SphX = SphereX;
	if(SphX-4< x && SphX > x && this->getZ() < 1){
		return true;
	} else {
		return false;
	}
}

bool Quader::collsYZiel(double SphereY){
	SphY = SphereY;
	if(SphY-1 < y && SphY+4.5 > y && this->getZ() < 1){
		return true;
	} else {
		return false;
	}
}



void Quader::draw(){

	glTranslated(x, z, -y);
	glRotated(degree, 0, 1, 0);
	glScaled(s, s, s);


	double p [8][3];
	p[0][0] = 0; p[0][1] = 0; p[0][2] = 0; 	// p0
	p[1][0] = xWidth; p[1][1] = 0; p[1][2] = 0;	// p1
	p[2][0] = xWidth; p[2][1] = 0; p[2][2] = yWidth;	// ... (siehe Zeichnung)
	p[3][0] = 0; p[3][1] = 0; p[3][2] = yWidth;
	p[4][0] = 0; p[4][1] = h; p[4][2] = 0;
	p[5][0] = xWidth; p[5][1] = h; p[5][2] = 0;
	p[6][0] = xWidth; p[6][1] = h; p[6][2] = yWidth;
	p[7][0] = 0; p[7][1] = h; p[7][2] = yWidth;

	glEnable(GL_NORMALIZE);
	glShadeModel(GL_FLAT);
	glBegin(GL_QUADS);
		// Boden
		glNormal3d(0,-1,0);
		glVertex3d(p[0][0],p[0][1],p[0][2]);
		glVertex3d(p[1][0],p[1][1],p[1][2]);
		glVertex3d(p[2][0],p[1][1],p[2][2]);
		glVertex3d(p[3][0],p[3][1],p[3][2]);
		// Seite Hinten
		glNormal3d(0,0,-1);
		glVertex3d(p[3][0],p[3][1],p[3][2]);
		glVertex3d(p[2][0],p[2][1],p[2][2]);
		glVertex3d(p[6][0],p[6][1],p[6][2]);
		glVertex3d(p[7][0],p[7][1],p[7][2]);
		// Seite Rechts
		glNormal3d(1,0,0);
		glVertex3d(p[2][0],p[2][1],p[2][2]);
		glVertex3d(p[1][0],p[1][1],p[1][2]);
		glVertex3d(p[5][0],p[5][1],p[5][2]);
		glVertex3d(p[6][0],p[6][1],p[6][2]);
		// Seite Vorne
		glNormal3d(0,0,1);
		glVertex3d(p[1][0],p[1][1],p[1][2]);
		glVertex3d(p[0][0],p[0][1],p[0][2]);
		glVertex3d(p[4][0],p[4][1],p[4][2]);
		glVertex3d(p[5][0],p[5][1],p[5][2]);
		// Seite Links
		glNormal3d(-1,0,0);
		glVertex3d(p[0][0],p[0][1],p[0][2]);
		glVertex3d(p[3][0],p[3][1],p[3][2]);
		glVertex3d(p[7][0],p[7][1],p[7][2]);
		glVertex3d(p[4][0],p[4][1],p[4][2]);
		// Deckel
		glNormal3d(0,1,0);
		glVertex3d(p[7][0],p[7][1],p[7][2]);
		glVertex3d(p[6][0],p[6][1],p[6][2]);
		glVertex3d(p[5][0],p[5][1],p[5][2]);
		glVertex3d(p[4][0],p[4][1],p[4][2]);
	glEnd();
}

