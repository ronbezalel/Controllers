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
	DWORD generalDw;
	bool hoverEnable;
	int maxRowNumber;
	bool firstShow;

	//private func:
	void MoveUp();
	void MoveDown();
	virtual void Mark();
	void MousePressed(MOUSE_EVENT_RECORD mer);
	void MouseMoved(MOUSE_EVENT_RECORD mer);
	int CheckPosition(MOUSE_EVENT_RECORD mer);

public:
	CheckList(string* textList, int listSize, short width, short height, DWORD color);
	CheckList(int height, int width, vector<string> options);
	string GetValue();
	void KeyEventProc(KEY_EVENT_RECORD ker);
	void MouseEventProc(MOUSE_EVENT_RECORD mer);
	void HandleInput(INPUT_RECORD iRecord);
	bool* GetChosenRows();
	~CheckList();
	void SetForeground(ForegroundColor color);
	void SetBackground(BackgroundColor color);
	void SetBorder(BorderType _border);
	void Hide();
	void Show() const {};
	void SelectIndex(size_t index);
	void DeselectIndex(size_t index);
	vector<size_t> GetSelectedIndices();
	void SetCoordinates(short x, short y);
	bool AddSelectedItem(string item);
	bool RemoveSelectedItem(string item);
	void Show();
};

#endif
