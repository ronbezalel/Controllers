#pragma once
#include "CheckList.h"

class RadioList : public CheckList
{
public:
	RadioList(string* textList, int listSize, short width, short hieght, DWORD color);
	~RadioList();
	void Mark();
	string GetInput();
	int LongestOptios();
};

