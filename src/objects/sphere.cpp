/*
 * sphere.cpp
 *
 *  Created on: 09.06.2015
 *      Author: Mo
 */

#include "sphere.h"

Sphere::Sphere() : Object(){
	x = 0;
	y = 0;
	r = .5;
	cout << "Sphere created" << endl;
	setObjectType("Sphere");
}

Sphere::~Sphere(){}

bool Sphere::collsSphere(double SphereX, double SphereY){
	SphX = SphereX, SphY = SphereY;
	if(SphX-(r+.5) < x && SphX+(r+.5) > x){  		//x Wert  des Objektes überprüft mit Kugelradius .5
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
	}else{
		return false;
	}
}

bool Sphere::collsX(double SphereX){
	SphX = SphereX;
	if(SphX-(r+.5) < x && SphY+(r+.5) > x) {
		return true;
	}else{
		return false;
	}
}

bool Sphere::collsY(double SphereY){
	SphY = SphereY;
	if(SphY-(r+.5) < y && SphY+(r+.5) > y) {
		return true;
	} else {
		return false;
	}
}

void Sphere::draw(){
	int     i, j,
		  n1 = 30, n2 = 30; // n1 und n2: Auflösung der Kugeln
	Vec3    normal, v1, v2;
	double  a1, a1d = M_PI / n1,
		  a2, a2d = M_PI / n2,
		  s1, s2,
		  c1, c2;

	v1 = Vec3(x, r, 0);

	glTranslated(x, 0, -y);
	glRotated(degree, 0, 1, 0);
	glScaled(s, s, s);

	glShadeModel(GL_SMOOTH);
	for(i = 0; i < n1; i++){
		a1 = i * a1d;

		glBegin(GL_TRIANGLE_STRIP);
		for(j = 0; j <= n2; j++){
			a2 = (j + .5 * (i % 2)) * 2 * a2d;

			s1 = sin(a1);
			c1 = cos(a1);
			s2 = sin(a2);
			c2 = cos(a2);
			normal = c1 * XVec3 + s1 * (c2 * YVec3 + s2 * ZVec3);
			v2 = v1 + r * normal;
			glNormal3dv(normal.p);
			glVertex3dv(v2.p);

			s1 = sin(a1 + a1d);
			c1 = cos(a1 + a1d);
			s2 = sin(a2 + a2d);
			c2 = cos(a2 + a2d);
			normal = c1 * XVec3 + s1 * (c2 * YVec3 + s2 * ZVec3);
			v2 = v1 + r * normal;
			glNormal3dv(normal.p);
			glVertex3dv(v2.p);
		}

		glEnd();
	}
}
