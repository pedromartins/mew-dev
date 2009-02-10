#ifndef _MEW_PRINTER_H
#define _MEW_PRINTER_H

#include <iostream>
#include <string>

using namespace std;

class Printer {
	Printer(){}
	virtual ~Printer(){}

	virtual void print(string str);
};


#endif
