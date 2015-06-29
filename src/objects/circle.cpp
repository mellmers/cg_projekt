/*
 * circle.cpp
 *
 *  Created on: 16.06.2015
 *      Author: Mo
 */

#import "circle.h"

Circle::Circle() : Object(){
	cout << "Circle created" << endl;
	setObjectType("Circle");
}

Circle::~Circle(){
}


void Circle::draw(double radius){

	r = radius;

    double x1,y1,x2,y2;
    double angle;

    x1 = 0.5, y1 = 0.5;
    glColor3f(1.0,1.0,0.6);


    glRotated(90, 1, 0, 0);
    if(x == 0 && y == 0) {
    	glTranslated(-r,-r,-h);
    }
    else {
    	glTranslated(x,-y,-h);
    }
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x1,y1);

    for( angle = 0; angle < 2*M_PI + 1; angle += (M_PI / 360.0) ) {

        x2 = x1+sin(angle)*r;
        y2 = y1+cos(angle)*r;
        glVertex2f(x2,y2);
    }

    glEnd();

}
