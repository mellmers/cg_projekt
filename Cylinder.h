//
//  Cylinder.h
//  CG-Demo
//
//  Created by Tolga Özer on 12.06.14.
//  Copyright (c) 2014 Tolga Özer. All rights reserved.
//

#ifndef __CG_Demo__Cylinder__
#define __CG_Demo__Cylinder__

#include <iostream>
#include "Vec3.hpp"



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


#endif /* defined(__CG_Demo__Cylinder__) */
