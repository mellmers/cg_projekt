/*
 * sphere.h
 *
 *  Created on: 09.06.2015
 *      Author: Mo
 */

#ifndef SPHERE_H_
#define SPHERE_H_

#include "object.h"

#include <iostream>


class Sphere : public Object {
public:
	Sphere();
	virtual ~Sphere();
	void draw();
	bool collisionX, collisionY;
	bool collsSphere(double sphereX, double sphereY);
	bool collsX(double sphereX),collsY(double sphereY);
};



#endif /* SPHERE_H_ */
