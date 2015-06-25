/*
 * circle.h
 *
 *  Created on: 16.06.2015
 *      Author: Mo
 */

#ifndef CIRCLE_H_
#define CIRCLE_H_

#include "object.h"

class Circle : public Object {
public:
	Circle();
	virtual ~Circle();
	void draw(double radius);
};

#endif /* CIRCLE_H_ */
