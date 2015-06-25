/*
 * object.cpp
 *
 *  Created on: 16.06.2015
 *      Author: Mo
 */

#include "object.h"

Object::Object(){
	x = 0;
	y = 0;
	r = 0;
	h = 1;
	setObjectType("Object");
}

Object::~Object(){
}

double Object::getX(){
	return x;
}

double Object::getY(){
	return y;
}

double Object::getH(){
	return h;
}

double Object::getR(){
	return r;
}

string Object::getObjectType() {
	return objectType;
}

void Object::setId(int value) {
	id = value;
}

void Object::setX(double xPosition){
	x = xPosition;
}

void Object::setY(double yPosition){
	y = yPosition;
}

void Object::setH(double height){
	h = height;
}

void Object::setR(double radius){
	r = radius;
}

void Object::move(double setx, double sety){
	x += setx;
	y += sety;
}

void Object::setObjectType(string t){
	objectType = t;
}

int Object::getId() {
	return id;
}
