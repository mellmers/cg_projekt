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
using namespace std;

class Sphere : public Object {
public:
	Sphere();
	virtual ~Sphere();
	void draw(const Vec3& ctr);
	bool collisionX, collisionY;
	bool collsSphere(double sphereX, double sphereY);
	bool collsX(double sphereX),collsY(double sphereY);
	double SphX,SphY;

};



#endif /* SPHERE_H_ */
