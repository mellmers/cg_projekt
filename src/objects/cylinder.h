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
    void draw();


    bool collisionX, collisionY;
	bool collsCylinder(double sphereX, double sphereY);
	bool collsX(double sphereX),collsY(double sphereY);

	double SphX,SphY;
	double sphereX, sphereZ;

};


#endif /* CYLINDER_H_ */
