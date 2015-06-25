/*
 * object.h
 *
 *  Created on: 16.06.2015
 *      Author: Mo
 */

#ifndef OBJECT_H_
#define OBJECT_H_

#include <GLFW/glfw3.h>
#include <math.h>
#include "../vec3.hpp"

#include <iostream>
using namespace std;

class Object {
public:
	Object();
	virtual ~Object();
	void move(double setx, double sety);

	double getX();
	double getY();
	double getH();
	double getR();
	string getObjectType();
	int getId();

	void setX(double xPosition);
	void setY(double yPosition);
	void setH(double height);
	void setR(double radius);
	void setObjectType(string t);
	void setId(int value);

	int id;
	string objectType;
	double x,y,h,r;
};

#endif /* OBJECT_H_ */
