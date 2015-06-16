/*
 * table.h
 *
 *  Created on: 09.06.2015
 *  Author: RDM
 */

#ifndef TABLE_H_
#define TABLE_H_

#include <GLFW/glfw3.h>
#include <iostream>
using namespace std;

class Table {
public:
	Table();
	virtual ~Table();
	void drawTable();

};

#endif /* TABLE_H_ */
