#ifndef _CHECKLIST_H_
#define _CHECKLIST_H_

#include <Windows.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include "Label.h"
#include "InterActiveController.h"
#include <vector>

class CheckList : public InterActiveController
{
protected:
	vector<Label> list;
	bool* chosen;
	short currentRow;
	short currentPosition;
	int rowMaxLength;

	//private func:
	void MoveUp();
	void MoveDown();
	virtual void Mark();
	void MousePressed(MOUSE_EVENT_RECORD mer);
	void MouseMoved(MOUSE_EVENT_RECORD mer);
	int CheckPosition(MOUSE_EVENT_RECORD mer);

public:
	CheckList(string* textList, int listSize, short width, short height, DWORD color);
	void Print();
	string GetInput();
	void KeyEventProc(KEY_EVENT_RECORD ker);
	void MouseEventProc(MOUSE_EVENT_RECORD mer);
	void HandleInput(INPUT_RECORD iRecord);
	bool* GetChosenRows();
	~CheckList();
};

#endif

