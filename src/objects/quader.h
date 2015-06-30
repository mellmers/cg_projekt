	/*
	 * quader.h
	 *
	 *  Created on: 16.06.2015
	 *      Author: Mo
	 */

	#ifndef QUADER_H_
	#define QUADER_H_

	#include "object.h"

	class Quader : public Object {
	public:
		Quader();
		virtual ~Quader();
		void draw();
		bool collisionX, collisionY;
		bool collsQuader(double sphereX, double sphereY);
		bool collsX(double sphereX),collsY(double sphereY);

		double SphX,SphY;
	};

	#endif /* QUADER_H_ */
