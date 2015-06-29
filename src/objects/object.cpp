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
	degree = 0;
	r = .5;
	h = 1;
	s = 1;
	xWidth = 1;
	yWidth = 1;
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

double Object::getXWidth(){
	return xWidth;
}

double Object::getYWidth(){
	return yWidth;
}

double Object::getDegree(){
	return degree;
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

void Object::setXWidth(double x){
	xWidth = x;
}

void Object::setYWidth(double y){
	yWidth = y;
}

void Object::scale(double scale){
	s += scale;
}

void Object::rotate(double d){
	degree += d;
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
