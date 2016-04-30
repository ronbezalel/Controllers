#include "TextBox.h"



TextBox::TextBox(int boxLength, short width, short height) :
	InterActiveController(width, height), textIndex(0), focus(false)
{
	boxSize = boxLength;
	text = vector<char>(boxLength);
	CONSOLE_CURSOR_INFO newCci = { 100, true };
	SetConsoleCursorInfo(handle, &newCci);
}

void TextBox::Print() {
	DWORD dw = FOREGROUND_BLUE | BACKGROUND_RED | FOREGROUND_INTENSITY;
	for (short i = coord.X; i < coord.X + boxSize + 2; i++) {
		COORD tmpCoord = { i,coord.Y };
		SetConsoleCursorPosition(handle, tmpCoord);
		SetConsoleTextAttribute(handle, dw);
		if (i == coord.X) {
			tmpCoord.Y = tmpCoord.Y;
			SetConsoleCursorPosition(handle, tmpCoord);
			cout << '\xDA';
			tmpCoord.Y = tmpCoord.Y + 1;
			SetConsoleCursorPosition(handle, tmpCoord);
			cout << '\xB3';
			tmpCoord.Y = tmpCoord.Y + 1;
			SetConsoleCursorPosition(handle, tmpCoord);
			cout << '\xC0';
			continue;
		}
		if (i == coord.X + boxSize + 1) {
			tmpCoord.Y = tmpCoord.Y;
			SetConsoleCursorPosition(handle, tmpCoord);
			cout << '\xBF';
			tmpCoord.Y = tmpCoord.Y + 1;
			SetConsoleCursorPosition(handle, tmpCoord);
			cout << '\xB3';
			tmpCoord.Y = tmpCoord.Y + 1;
			SetConsoleCursorPosition(handle, tmpCoord);
			cout << '\xD9';
			continue;
		}
		cout << '\xC4';
		tmpCoord.Y = tmpCoord.Y + 2;
		SetConsoleCursorPosition(handle, tmpCoord);
		cout << '\xC4';
	}
	curserPosition = coord.X;
	COORD endPrint = { curserPosition, coord.Y };
	SetConsoleCursorPosition(handle, endPrint);
}

TextBox::~TextBox()
{
}

void TextBox::HandleInput(INPUT_RECORD iRecord) {
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

void TextBox::MouseEventProc(MOUSE_EVENT_RECORD mer) {
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
	}
}

void TextBox::MousePressed(MOUSE_EVENT_RECORD mer) {
	int res = CheckPosition(mer);
	if (res != -1) {
		curserPosition = res;
		textIndex = res - coord.X - 1;
		COORD reset = { res , coord.Y + 1 };
		SetConsoleCursorPosition(handle, reset);
		focus = true;
	}
}

int TextBox::CheckPosition(MOUSE_EVENT_RECORD mer) {
	int YAxis = mer.dwMousePosition.Y;
	int XAxis = mer.dwMousePosition.X;
	if (XAxis <= coord.X + boxSize && XAxis >= coord.X + 1 &&
		YAxis == coord.Y + 1) {
		return XAxis;
	}
	return -1;
}

void TextBox::KeyEventProc(KEY_EVENT_RECORD ker) {
	if (ker.bKeyDown) {
		switch (ker.wVirtualKeyCode)
		{
		case VK_LEFT:
		case VK_NUMPAD4:
			MoveLeft();
			break;
		case VK_NUMPAD6:
		case VK_RIGHT:
			MoveRight();
			break;
		case VK_BACK:
			Delete();
			break;
		default:
			AddCharecter(ker.uChar.AsciiChar);
			break;
		}
	}
}
void TextBox::MoveLeft() {
	if (curserPosition > coord.X + 1) {
		curserPosition--;
		COORD left = { curserPosition , coord.Y + 1 };
		SetConsoleCursorPosition(handle, left);
		if (focus) {
			textIndex--;
		}
		else focus = true;
	}
}

void TextBox::MoveRight() {
	if (curserPosition < coord.X + boxSize + 1) {
		curserPosition++;
		COORD right = { curserPosition , coord.Y + 1 };
		SetConsoleCursorPosition(handle, right);
		if (focus) {
			textIndex++;
		}
		else focus = true;
	}
}

void TextBox::Delete() {
	if (focus) {
		int offset = 1;
		for (int i = textIndex; i < boxSize; i++) {
			if (i == boxSize - 1) {
				text[i] = ' ';
				cout << text[i];
				break;
			}
			text[i] = text[i + 1];
			cout << text[i];
			COORD moveRight = { curserPosition + offset++ , coord.Y + 1 };
			SetConsoleCursorPosition(handle, moveRight);
		}
		COORD reset = { curserPosition , coord.Y + 1 };
		SetConsoleCursorPosition(handle, reset);
	}
}

void TextBox::AddCharecter(char c) {
	if (focus) {
		if (textIndex < boxSize) {
			text[textIndex] = c;
			cout << c;
			MoveRight();
		}
	}
}

void TextBox::SetText(string textToEnter) {
	if (textToEnter.size() < text.size()) {
		COORD reset = { coord.X + 1 , coord.Y + 1 };
		SetConsoleCursorPosition(handle, reset);
		cout << textToEnter;
		for (int i = 0; i < textToEnter.size(); i++) {
			text[i] = textToEnter[i];
		}
	}
}

string TextBox::GetInput() {
	string str(text.begin(), text.end());
	return str;
}