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
	void draw(const Vec3& ctr, double r);
};



#endif /* SPHERE_H_ */
