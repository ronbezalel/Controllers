#include "Label.h";

Label::Label(short width, short height, string text, bool isVisible) :
	Controller(width, height)
{
	//cord = { width, hieght };
	labelText = text;
	//handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetCursorEnable(isVisible);
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
	Print();
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
		Print();
		return;
	}
	else {
		dw = ~(BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE) & dw;
		SetColor(dw);
		Print();
	}
	return;
}
void Label::Print() const {
	SetConsoleCursorPosition(handle, coord);
	SetConsoleTextAttribute(handle, dw);
	cout << labelText;
}

int Label::Length() {
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
	Print();
}
Label::~Label() {

}