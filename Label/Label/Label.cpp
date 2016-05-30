#include "Label.h";

Label::Label(short width, short height, string text, bool isVisible) :
	IControl(width, height)
{
	//cord = { width, hieght };
	labelText = text;
	//handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetCursorEnable(isVisible);
}
Label::Label(int width, string value):
	IControl((short)width, 0)
{
	labelText = value;
	SetCursorEnable(false);
}
void Label::SetHeight(int height) {
	if (height >= 0) {
		coord.Y = (short)height;
	}
}
void Label::SetCursorEnable(bool enable) {
	CONSOLE_CURSOR_INFO newCci = { 100, enable };
	SetConsoleCursorInfo(handle, &newCci);
}
void Label::SetColor(DWORD color) {
	dw = color;

}
void Label::SwitchContent(string newText) {
	labelText = newText;
	SetConsoleCursorPosition(handle, coord);
	Show();
}
COORD Label::GetCord() {
	return coord;
}
string Label::GetInput() {
	return labelText;
}
DWORD Label::GetColor() {
	return dw;
}
void Label::Hoover(bool isHover) {
	if (isHover) {
		dw = (BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE) | dw;
		SetColor(dw);
		Show();
		return;
	}
	else {
		dw = ~(BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE) & dw;
		SetColor(dw);
		Show();
	}
	return;
}
void Label::Show() const {
	SetConsoleCursorPosition(handle, coord);
	SetConsoleTextAttribute(handle, dw);
	char luCorner, ruCorner, ldCorner, rdCorner, vertical, horizontal;
	if (border == BorderType::Single) {
		luCorner = '\xDA';
		horizontal = '\xC4';
		ruCorner = '\xBF';
		vertical = '\xB3';
		rdCorner = '\xD9';
		ldCorner = '\xC0';
	}
	else if (border == BorderType::Double) {
		luCorner = '\xC9';
		horizontal = '\xCD';
		ruCorner = '\xBB';
		vertical = '\xBA';
		rdCorner = '\xBC';
		ldCorner = '\xC8';
	}
	else
	{
		cout << labelText;
		return;
	}
	short length =(short)Length();
	for (short i = coord.X; i < coord.X + length + 2; i++) {
		COORD tmpCoord = { i,coord.Y };
		SetConsoleCursorPosition(handle, tmpCoord);
		SetConsoleTextAttribute(handle, dw);
		if (i == coord.X) {
			tmpCoord.Y = tmpCoord.Y;
			SetConsoleCursorPosition(handle, tmpCoord);
			cout << luCorner;
			tmpCoord.Y = tmpCoord.Y + 1;
			SetConsoleCursorPosition(handle, tmpCoord);
			cout << vertical;
			tmpCoord.Y = tmpCoord.Y + 1;
			SetConsoleCursorPosition(handle, tmpCoord);
			cout << ldCorner;
			continue;
		}
		if (i == coord.X + length + 1) {
			tmpCoord.Y = tmpCoord.Y;
			SetConsoleCursorPosition(handle, tmpCoord);
			cout << ruCorner;
			tmpCoord.Y = tmpCoord.Y + 1;
			SetConsoleCursorPosition(handle, tmpCoord);
			cout << vertical;
			tmpCoord.Y = tmpCoord.Y + 1;
			SetConsoleCursorPosition(handle, tmpCoord);
			cout << rdCorner;
			continue;
		}
		cout << horizontal;
		tmpCoord.Y = tmpCoord.Y + 2;
		SetConsoleCursorPosition(handle, tmpCoord);
		cout << horizontal;
	}
	COORD endPrint = { coord.X + 1 , coord.Y + 1 };
	SetConsoleCursorPosition(handle, endPrint);
	cout << labelText;
	return;	
}

int Label::Length() const{
	int i = 0;
	while (true) {
		if (labelText[i] == '\0')break;
		i++;
	}
	return i;
}
void Label::CleanLabel() {
	int i = 0;
	bool flage = true;
	while (flage)
	{
		if (labelText[i] == '\0') break;
		labelText[i] = ' ';
		i++;
	}
	Show();
}
void Label::Hide() {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD dw = (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	SetConsoleTextAttribute(handle, dw);
	COORD crd = { coord.X , coord.Y };
	SetConsoleCursorPosition(handle, crd);
	short length = (short)Length();
	for (short j = crd.X; j < (coord.X + length) ; j++) {
		COORD tmpCrd = { j , coord.Y };
		SetConsoleCursorPosition(handle, tmpCrd);
		cout << " ";
	}

}
Label::~Label() {

}
void Label::SetValue(string value) {
	labelText = value;
}