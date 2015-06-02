//
//  Cylinder.cpp
//  CG-Demo
//
//  Created by Tolga Özer on 12.06.14.
//  Copyright (c) 2014 Tolga Özer. All rights reserved.
//

#include "Cylinder.h"
#include <GLFW/glfw3.h>
#include "math.h"


Cylinder::Cylinder(){
    
}

Cylinder::~Cylinder(){
    
}

void Cylinder::setPosi(double xPosi, double zPosi){
	x = xPosi;
	z = zPosi;
}

double Cylinder::getPosiX(){
	return x;
}

double Cylinder::getPosiZ(){
	return z;
}


bool Cylinder::colCylinder(double gameSphereX, double gameSphereZ){
	sphereX = gameSphereX, sphereZ = gameSphereZ;
	if(sphereX-0.8 < x && sphereX+0.8 > x) {
		if(sphereZ-0.8 < z && sphereZ+0.8 > z) {
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
	if(sphereZ-0.8 < z && sphereZ+0.8 > z) {
		return true;
	} else {
		return false;
	}
}

bool Cylinder::colFinish(double gameSphereX, double gameSphereZ){
	sphereX = gameSphereX, sphereZ = gameSphereZ;
	if(sphereX-0.25 < x && sphereX+0.25 > x) {
		if(sphereZ-0.25 < z && sphereZ+0.25 > z) {
			collisionZ = true;
		} else {
			collisionZ = false;
		}
		return collisionX = true;
	} else {
		return collisionX = false;
	}
}


void Cylinder::drawTop(){
    
    float x1,y1,x2,y2;
    float angle;
    double radius=0.5;
    
    x1 = 0.5,y1=0.6;
    glColor3f(1.0,1.0,0.6);
    
    
    glRotated(90, 1, 0, 0);
    glTranslated(-0.5,-0.6,-2);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x1,y1);
    
    for (angle=1.0f;angle<361.0f;angle+=0.2)
    {
        x2 = x1+sin(angle)*radius;
        y2 = y1+cos(angle)*radius;
        glVertex2f(x2,y2);
    }
    
    glEnd();

}



void Cylinder::draw(const Vec3& ctr ){
    
	x = ctr.p[0], z = ctr.p[2];
    glTranslated(ctr.p[0], ctr.p[1], ctr.p[2]);
    
    
    for( double angle = 0.0; angle < M_PI*4; angle += (M_PI / 360.0) ) {
        
        
        glBegin(GL_QUAD_STRIP);
        
        glVertex3f(
                   ( 0.5*(cos(angle)*1) ),
                   ( (0)  ),
                   ( 0.5*(sin(angle)*1) )
                   );
        
        
        glVertex3f(
                   ( 0.5*(cos(angle)*1) ),
                   ( (2)  ),
                   ( 0.5*(sin(angle)*1) )
                   );
    }
    glEnd ();
}


void Cylinder::SetMaterialColor(int side, double r, double g, double b) {
    float	amb[4], dif[4], spe[4];
    int mat;

    dif[0] = r;
    dif[1] = g;
    dif[2] = b;

    for(int i = 0; i < 3; i++) {
        amb[i] = .1 * dif[i];
        spe[i] = .5;
    }
    amb[3] = dif[3] = spe[3] = 0.9;

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

