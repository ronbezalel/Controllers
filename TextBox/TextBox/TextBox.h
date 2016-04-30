#ifndef _TEXTBOX_H_
#define _TEXTBOX_H_

#include <string>
#include <vector>
#include <Windows.h>
#include <stdio.h>
#include <iostream>
#include "InterActiveController.h"

using namespace std;
class TextBox : public InterActiveController
{
private:
	vector<char> text;
	int boxSize;
	int curserPosition;
	int textIndex;
	bool focus;

	void MoveRight();
	void MoveLeft();
	void Delete();
	void AddCharecter(char c);
	int CheckPosition(MOUSE_EVENT_RECORD mer);
	void MousePressed(MOUSE_EVENT_RECORD mer);

public:
	TextBox(int boxLength, short width, short height);
	void Print();
	void KeyEventProc(KEY_EVENT_RECORD ker);
	void MouseEventProc(MOUSE_EVENT_RECORD mer);
	void HandleInput(INPUT_RECORD iRecord);
	string GetInput();
	void SetText(string textToEnter);
	~TextBox();
};


#endif // _TEXTBOX_H_



