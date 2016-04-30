#ifndef _CONTROLLER_
#define _CONTROLLER_

#include <Windows.h>
#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class Controller
{
protected:
	HANDLE handle;
	COORD coord;

public:
	Controller(short width, short height);
	virtual ~Controller();
	virtual void Print() const;
	virtual string GetInput() = 0;
};

#endif
