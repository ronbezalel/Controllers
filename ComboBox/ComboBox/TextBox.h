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
	DWORD textDw;
	BorderType border;
	bool enableWrite;

	void MoveRight();
	void MoveLeft();
	void Delete();
	void BackSpace();
	void AddCharecter(char c);
	int CheckPosition(MOUSE_EVENT_RECORD mer);
	void MousePressed(MOUSE_EVENT_RECORD mer);
	void Print();
	int LastLetterIndex(int position);

public:
	TextBox(int boxLength, short width, short height);
	TextBox(int width);

	void KeyEventProc(KEY_EVENT_RECORD ker);
	void MouseEventProc(MOUSE_EVENT_RECORD mer);
	void HandleInput(INPUT_RECORD iRecord);
	string GetValue();
	void Show() const;
	void Show();
	void Hide();
	void SetForeground(ForegroundColor color);
	void SetBackground(BackgroundColor color);
	void SetBorder(BorderType _border);
	void SetText(string textToEnter);
	~TextBox();
};


#endif // _TEXTBOX_H_


