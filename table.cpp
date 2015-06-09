/*
 * table.cpp
 *
 *  Created on: 09.06.2015
 *  Author: RDM
 */

#include <GL/gl.h>
#include "table.h"
#include "cylinder.h"

#define GLFW_DLL


Table::Table(){

}

Table::~Table(){

}


// Zeichnung des Billardtisches
void Table::drawTable(){

	glBegin(GL_QUADS);
		// Unterseite
		glNormal3f(0, -1, 0);
		glVertex3f(-10.3,0,-5.3);
		glVertex3f(10.3,0,-5.3);
		glVertex3f(10.3,0,5.3);
		glVertex3f(-10.3,0,5.3);

		// Vorderseite
		glNormal3f(0, 0, 1);
		glVertex3f(-10,0,5);
		glVertex3f(10,0,5);
		glVertex3f(10,.5,5);
		glVertex3f(-10,.5,5);

		// Linke Seite
		glNormal3f(-1, 0,0);
		glVertex3f(-10,0,-5);
		glVertex3f(-10,0,5);
		glVertex3f(-10,.5,5);
		glVertex3f(-10,.5,-5);


		// Rückseite
		glNormal3f(0, 0, -1);
		glVertex3f(-10,.5,-5);
		glVertex3f(10,.5,-5);
		glVertex3f(10,0,-5);
		glVertex3f(-10,0,-5);

		// Rechte Seite
		glNormal3f(1, 0, 0);
		glVertex3f(10,.5,-5);
		glVertex3f(10,.5,5);
		glVertex3f(10,0,5);
		glVertex3f(10,0,-5);


		// Vorderseite Mauer
		glNormal3f(0, 0, -1);
		glVertex3f(-10.3,0,5.3);
		glVertex3f(10.3,0,5.3);
		glVertex3f(10.3,.5,5.3);
		glVertex3f(-10.3,.5,5.3);


		// Linke Seite Mauer
		glNormal3f(1, 0,0);
		glVertex3f(-10.3,0,5.3);
		glVertex3f(-10.3,0.5,5.3);
		glVertex3f(-10.3,.5,-5.3);
		glVertex3f(-10.3,0,-5.3);

		// Rückseite Mauer
		glNormal3f(0, 0, 1);
		glVertex3f(-10.3,.5,-5.3);
		glVertex3f(10.3,.5,-5.3);
		glVertex3f(10.3,0,-5.3);
		glVertex3f(-10.3,0,-5.3);

		// Rechte Seite Mauer
		glNormal3f(-1, 0, 0);
		glVertex3f(10.3,.5,-5.3);
		glVertex3f(10.3,.5,5.3);
		glVertex3f(10.3,0,5.3);
		glVertex3f(10.3,0,-5.3);

		glNormal3f(0, 1, 0);
		glVertex3f(-10.3,0.5,5.3);
		glVertex3f(-10,0.5,5);
		glVertex3f(-10,0.5,-5);
		glVertex3f(-10.3,0.5,-5.3);

		glNormal3f(0, 1, 0);
		glVertex3f( -10.3,0.5,-5.3);
		glVertex3f( -10,0.5,-5);
		glVertex3f(10,0.5,-5);
		glVertex3f(10.3,0.5,-5.3);

		glNormal3f(0, 1, 0);
		glVertex3f(10.3,0.5,-5.3);
		glVertex3f(10,0.5,-5);
		glVertex3f(10,0.5,5);
		glVertex3f(10.3,0.5,5.3);

		glNormal3f(0, 1, 0);
		glVertex3f( 10.3,0.5,5.3);
		glVertex3f(10,0.5,5);
		glVertex3f(-10,0.5,5);
		glVertex3f(-10.3,0.5,5.3);

	glEnd();
}
