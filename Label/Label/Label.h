#pragma once
#ifndef _LABEL_H_
#define _LABEL_H_

#include <Windows.h>
#include "IControl.h"
#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;
class Label : public IControl {
private:
	//COORD cord = { 0,0 };
	//HANDLE handle;
	//DWORD dw;
	CONSOLE_CURSOR_INFO cci;
	string labelText;


public:
	Label(short width, short height, string text, bool isVisible);
	Label(int width, string value);		// api ctor 
	COORD GetCord();
	string GetInput();
	DWORD GetColor();
	void SetHeight(int height);			// api set height default value to 0 
	void SetColor(DWORD color);
	void SetCursorEnable(bool enable);
	void SwitchContent(string newText);
	void SetValue(string value);
	void Show() const;
	void Hide();
	void Hoover(bool isHover);
	int Length() const;
	void CleanLabel();
	~Label();
};


#endif // !_LABEL_H_
