#pragma once
#include "CheckList.h"

class RadioList : public CheckList
{
public:
	RadioList(string* textList, int listSize, short width, short hieght, DWORD color);
	RadioList(int height, int width, vector<string> options);
	~RadioList();
	void Mark();
	string GetValue();
	size_t GetSelectedIndex();
	void SetSelectIndex(size_t index);
	int LongestOptios();
	//abort method of check list
private:
	void SelectIndex(size_t index) {}
	void DeselectIndex(size_t index) {}
	vector<size_t> GetSelectedIndices() {}

};
