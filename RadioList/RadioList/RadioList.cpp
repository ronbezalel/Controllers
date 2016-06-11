#include "RadioList.h"



RadioList::RadioList(string* textList, int listSize, short width, short hieght, DWORD color) :
	CheckList(textList, listSize, width, hieght, color) {

}

RadioList::RadioList(int height, int width, vector<string> options) :
	CheckList(height, width, options) {

}

void RadioList::Mark() {
	if (chosen[currentRow]) {
		string newText = list[currentRow].GetValue();
		newText[1] = ' ';
		int width = list[currentRow].GetWidth();
		COORD newCoord = list[currentRow].GetCord();
		DWORD color = list[currentRow].GetColor();
		list[currentRow] = Label(width, 0, newText, false);
		list[currentRow].SetCoordinates(newCoord.X, newCoord.Y);
		list[currentRow].SetColor(color);
		chosen[currentRow] = false;
	}
	else {
		int oldChoice = -1;
		for (int i = 0; i < list.size(); i++) {
			if (chosen[i]) {
				oldChoice = i;
				chosen[i] = false;
				break;
			}
		}
		if (oldChoice != -1) {
			string unmark = list[oldChoice].GetValue();
			unmark[1] = ' ';
			int width = list[oldChoice].GetWidth();
			COORD unmarkCoord = list[oldChoice].GetCord();
			DWORD unmarkcolor = list[oldChoice].GetColor();
			list[oldChoice] = Label(width, 0, unmark, false);
			list[oldChoice].SetCoordinates(unmarkCoord.X, unmarkCoord.Y);
			list[oldChoice].SetColor(unmarkcolor);
			list[oldChoice].Print();
		}
		//new chosen raw
		string newText = list[currentRow].GetValue();
		newText[1] = 'X';
		int width = list[currentRow].GetWidth();
		COORD newCoord = list[currentRow].GetCord();
		DWORD color = list[currentRow].GetColor();
		list[currentRow] = Label(width, 0, newText, false);
		list[currentRow].SetCoordinates(newCoord.X, newCoord.Y);
		list[currentRow].SetColor(color);
		chosen[currentRow] = true;
	}
	list[currentRow].Print();
	return;
}

int RadioList::LongestOptios() {
	int size = 0;
	for (int i = 0; i < list.size(); i++) {
		if (size <= list[i].Length()) size = list[i].Length();
	}
	return size;
}

string RadioList::GetValue() {
	int index = 0;
	bool flage = false;
	for (index; index < list.size(); index++) {
		if (chosen[index]) {
			flage = true;
			break;
		}
	}
	if (!flage) return "no choose";
	return list[index].GetValue();
}

size_t RadioList::GetSelectedIndex() {
	for (int i = 0; i < list.size(); i++) {
		if (chosen[i]) {
			return i + 1;
		}
	}
}
void RadioList::SetSelectIndex(size_t index) {
	if (index > list.size() || index < 1) {
		return;
	}
	for (int i = 0; i < list.size(); i++) {
		if (chosen[i] && (i + 1) != index) {
			chosen[i] = false;
			string newText = list[i].GetValue();
			newText[1] = ' ';
			list[i].SetValue(newText);
			if (hoverEnable) {
				list[i].Print();
			}
		}
	}
	chosen[index - 1] = true;
	string newText = list[index - 1].GetValue();
	newText[1] = 'X';
	list[index - 1].SetValue(newText);
	if (hoverEnable) {
		list[index - 1].Print();
	}
}

RadioList::~RadioList() {

}
