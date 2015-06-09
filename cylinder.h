/*
 * cylinder.h
 *
 *  Created on: 09.06.2015
 *      Author: Mo
 */

#ifndef CYLINDER_H_
#define CYLINDER_H_

#include <iostream>
#include "vec3.hpp"

class Cylinder {
public:
	Cylinder();
	virtual ~Cylinder();
    void drawTop();
	void draw(const Vec3& ctr);
	void setPosi(double x, double z);
	double getPosiX();
	double getPosiZ();
	bool colCylinder(double gameSphereX, double gameSphereZ);
	bool colFinish(double gameSphereX, double gameSphereZ);
	void SetMaterialColor(int side, double r, double g, double b);
	double sphereX, sphereZ, x, z;
	bool collisionX, collisionZ;

	bool colX(double gameSphereX);
	bool colZ(double gameSphereZ);
};


#endif /* CYLINDER_H_ */
