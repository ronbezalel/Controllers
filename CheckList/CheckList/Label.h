#ifndef _LABEL_H_
#define _LABEL_H_

#include <Windows.h>
#include "Controller.h"
#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;
class Label : Controller {
private:
	//COORD cord = { 0,0 };
	//HANDLE handle;
	DWORD dw;
	CONSOLE_CURSOR_INFO cci;
	string labelText;


public:
	Label(short width, short height, string text, bool isVisible);
	COORD GetCord();
	string GetInput();
	DWORD GetColor();
	void SetColor(DWORD color);
	void SetCursorEnable(bool enable);
	void SwitchContent(string newText);
	void Print() const;
	void Hoover(bool isHover);
	int Length();
	void CleanLabel();
	~Label();
};


#endif // !_LABEL_H_


