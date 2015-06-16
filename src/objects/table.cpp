/*
 * table.cpp
 *
 *  Created on: 09.06.2015
 *  Author: RDM
 */

#include "table.h"

Table::Table(){
}

Table::~Table(){
}


// Zeichnung der Minigolffl‰che
void Table::drawTable(){

	glBegin(GL_QUADS);
		// Boden
		glNormal3f(0, -1, 0);
		glVertex3f(-10.5,0,-8);
		glVertex3f(10.5,0,-8);
		glVertex3f(10.5,0,8);
		glVertex3f(-10.5,0,8);

		/*
		 * Innenseiten
		 */
		// Unten
		glNormal3f(0, 0, 1);
		glVertex3f(-10,0,7.5);
		glVertex3f(10,0,7.5);
		glVertex3f(10,.5,7.5);
		glVertex3f(-10,.5,7.5);

		// Linke Seite
		glNormal3f(-1, 0,0);
		glVertex3f(-10,0,-7.5);
		glVertex3f(-10,0,7.5);
		glVertex3f(-10,.5,7.5);
		glVertex3f(-10,.5,-7.5);

		// Oben
		glNormal3f(0, 0, -1);
		glVertex3f(-10,.5,-7.5);
		glVertex3f(10,.5,-7.5);
		glVertex3f(10,0,-7.5);
		glVertex3f(-10,0,-7.5);

		// Rechte Seite
		glNormal3f(1, 0, 0);
		glVertex3f(10,.5,-7.5);
		glVertex3f(10,.5,7.5);
		glVertex3f(10,0,7.5);
		glVertex3f(10,0,-7.5);

		/*
		 * Auﬂenseiten
		 */
		// Unten
		glNormal3f(0, 0, -1);
		glVertex3f(-10.5,0,8);
		glVertex3f(10.5,0,8);
		glVertex3f(10.5,.5,8);
		glVertex3f(-10.5,.5,8);

		// Linke Seite
		glNormal3f(1, 0,0);
		glVertex3f(-10.5,0,8);
		glVertex3f(-10.5,0.5,8);
		glVertex3f(-10.5,.5,-8);
		glVertex3f(-10.5,0,-8);

		// Oben
		glNormal3f(0, 0, 1);
		glVertex3f(-10.5,.5,-8);
		glVertex3f(10.5,.5,-8);
		glVertex3f(10.5,0,-8);
		glVertex3f(-10.5,0,-8);

		// Rechte Seite
		glNormal3f(-1, 0, 0);
		glVertex3f(10.5,.5,-8);
		glVertex3f(10.5,.5,8);
		glVertex3f(10.5,0,8);
		glVertex3f(10.5,0,-8);

		/*
		 * Deckel
		 */
		// Linke Seite
		glNormal3f(0, 1, 0);
		glVertex3f(-10.5,0.5,8);
		glVertex3f(-10,0.5,7.5);
		glVertex3f(-10,0.5,-7.5);
		glVertex3f(-10.5,0.5,-8);

		// Oben
		glNormal3f(0, 1, 0);
		glVertex3f(-10.5,0.5,-8);
		glVertex3f(-10,0.5,-7.5);
		glVertex3f(10,0.5,-7.5);
		glVertex3f(10.5,0.5,-8);

		// Rechte Seite
		glNormal3f(0, 1, 0);
		glVertex3f(10.5,0.5,-8);
		glVertex3f(10,0.5,-7.5);
		glVertex3f(10,0.5,7.5);
		glVertex3f(10.5,0.5,8);

		// Unten
		glNormal3f(0, 1, 0);
		glVertex3f(10.5,0.5,8);
		glVertex3f(10,0.5,7.5);
		glVertex3f(-10,0.5,7.5);
		glVertex3f(-10.5,0.5,8);

	glEnd();
}
