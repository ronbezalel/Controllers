#include "CheckList.h"



CheckList::CheckList(string* textList, int listSize, short width, short height, DWORD color) :
	InterActiveController(width, height), currentRow(0), currentPosition(0), rowMaxLength(0)
{
	int row = height;
	coord = { width , height };
	currentPosition = height;
	for (int i = 0; i < listSize; i++) {
		list.push_back(Label(width, row++, "[ ] " + textList[i], false));
		if (rowMaxLength < textList[i].size() + 4) rowMaxLength = textList[i].size() + 4;
		list[i].SetColor(color);
	}
	list[0].Hoover(true);
	chosen = new bool[listSize];
	for (int j = 0; j < listSize; j++) {
		chosen[j] = false;
	}
}

void CheckList::Print() {
	for (std::vector<Label>::const_iterator i = list.begin(); i != list.end(); i++) {
		i->Print();
	}
	SetConsoleCursorPosition(handle, coord);
}
bool* CheckList::GetChosenRows() {
	return chosen;
}
void CheckList::HandleInput(INPUT_RECORD iRecord) {
	//if (!isClicked) return;
	switch (iRecord.EventType)
	{
	case KEY_EVENT: // keyboard input 
		KeyEventProc(iRecord.Event.KeyEvent);
		break;

	case MOUSE_EVENT: // mouse input 
		MouseEventProc(iRecord.Event.MouseEvent);
		break;

	default:
		//errorInput();
		break;
	}
}
void CheckList::MouseEventProc(MOUSE_EVENT_RECORD mer) {
#ifndef MOUSE_HWHEELED
#define MOUSE_HWHEELED 0x0008
#endif
	switch (mer.dwEventFlags) {

	case 0:
		//Right button press
		if (mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
			MousePressed(mer);
		}
		break;
	case MOUSE_MOVED:
		MouseMoved(mer);
		break;
	}
}
void CheckList::MousePressed(MOUSE_EVENT_RECORD mer) {
	int res = CheckPosition(mer);
	if (res != -1) {
		list[currentRow].Hoover(false);
		currentRow = res - coord.Y;
		currentPosition = res;
		COORD newPosition = { coord.X , currentPosition };
		SetConsoleCursorPosition(handle, newPosition);
		list[currentRow].Hoover(true);
		Mark();
	}
}
void CheckList::MouseMoved(MOUSE_EVENT_RECORD mer) {
	int res = CheckPosition(mer);
	if (res != -1) {
		list[currentRow].Hoover(false);
		currentRow = res - coord.Y;
		currentPosition = res;
		COORD newPosition = { coord.X , currentPosition };
		SetConsoleCursorPosition(handle, newPosition);
		list[currentRow].Hoover(true);
	}
	else return;
}
int CheckList::CheckPosition(MOUSE_EVENT_RECORD mer) {
	int YAxis = mer.dwMousePosition.Y;
	int XAxis = mer.dwMousePosition.X;
	if (XAxis <= coord.X + rowMaxLength && XAxis >= coord.X &&
		YAxis < coord.Y + list.size() && YAxis >= coord.Y) {
		return YAxis;
	}
	return -1;
}
void CheckList::KeyEventProc(KEY_EVENT_RECORD ker) {
	if (ker.bKeyDown) {
		switch (ker.wVirtualKeyCode)
		{
		case VK_UP:
		case VK_NUMPAD2:
			MoveUp();
			break;
		case VK_NUMPAD8:
		case VK_DOWN:
			MoveDown();
			break;
		case VK_RETURN:
			Mark();
			break;
		default:
			break;
		}
	}
}
void CheckList::MoveUp() {
	if (currentPosition != coord.Y) {
		list[currentRow].Hoover(false);
		currentRow--;
		currentPosition--;
		COORD newPosition = { coord.X , currentPosition };
		SetConsoleCursorPosition(handle, newPosition);
		list[currentRow].Hoover(true);
	}
}
void CheckList::MoveDown() {
	if (currentPosition != coord.Y + list.size() - 1) {
		list[currentRow].Hoover(false);
		currentRow++;
		currentPosition++;
		COORD newPosition = { coord.X , currentPosition };
		SetConsoleCursorPosition(handle, newPosition);
		list[currentRow].Hoover(true);
	}
}
void CheckList::Mark() {
	if (chosen[currentRow]) {
		string newText = list[currentRow].GetInput();
		newText[1] = ' ';
		COORD newCoord = list[currentRow].GetCord();
		DWORD color = list[currentRow].GetColor();
		list[currentRow] = Label(newCoord.X, newCoord.Y, newText, false);
		list[currentRow].SetColor(color);
		chosen[currentRow] = false;
	}
	else {
		string newText = list[currentRow].GetInput();
		newText[1] = 'X';
		COORD newCoord = list[currentRow].GetCord();
		DWORD color = list[currentRow].GetColor();
		list[currentRow] = Label(newCoord.X, newCoord.Y, newText, false);
		list[currentRow].SetColor(color);
		chosen[currentRow] = true;
	}
	list[currentRow].Print();
	return;
}

string CheckList::GetInput() {
	chosen[1] = true;
	chosen[4] = true;
	bool* rows = GetChosenRows();
	string res = "";
	for (int i = 0; i < list.size(); i++) {
		if (rows[i]) {
			string tmp = list[i].GetInput() + ',';
			for (int j = 4; j < tmp.size(); j++) {
				res.push_back(tmp[j]);
			}
		}
	}
	return res;
}

CheckList::~CheckList() {
	free(chosen);
}
