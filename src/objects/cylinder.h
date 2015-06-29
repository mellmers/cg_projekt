/*
 * cylinder.h
 *
 *  Created on: 09.06.2015
 *      Author: Mo
 */

#ifndef CYLINDER_H_
#define CYLINDER_H_

#include "object.h"

#include <iostream>
using namespace std;

class Cylinder : public Object {
public:
	Cylinder();
	virtual ~Cylinder();
    void draw(double radius);



	bool colCylinder(double gameSphereX, double gameSphereZ);
	bool colFinish(double gameSphereX, double gameSphereZ);
	double sphereX, sphereZ;
	bool collisionX, collisionZ;

	bool colX(double gameSphereX);
	bool colZ(double gameSphereZ);
};


#endif /* CYLINDER_H_ */
