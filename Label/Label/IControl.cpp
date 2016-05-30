#include "IControl.h"



IControl::IControl(short width, short height) {
	if (width >= 0 && height >= 0) {
		coord = { width, height };
		handle = GetStdHandle(STD_OUTPUT_HANDLE);
		border = BorderType::None;
	}
}

void IControl::Show() const {

}

void IControl::Hide() {

}
void IControl::SetForeground(ForegroundColor color) {
	
	switch (color)
	{
	case ForegroundColor::Red:
		dw = dw | (FOREGROUND_RED);
		break;
	case ForegroundColor::Blue:
		dw = dw | (FOREGROUND_BLUE);
		break;
	case ForegroundColor::Green:
		dw = dw | (FOREGROUND_GREEN);
		break;
	case ForegroundColor::Purple:
		dw = dw | (FOREGROUND_RED | FOREGROUND_BLUE);
		break;
	case ForegroundColor::Teal:
		dw = dw | (FOREGROUND_RED | FOREGROUND_GREEN);
		break;
	case ForegroundColor::Yellow:
		dw = dw | (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		break;
	case ForegroundColor::White:
		dw = dw | (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		break;
	case ForegroundColor::Black:
		dw = dw | !(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		break;
	default:
		break;
	}
}
void IControl::SetBackground(BackgroundColor color) {
	switch (color)
	{
	case BackgroundColor::Red:
		dw = dw | (BACKGROUND_RED);
		break;
	case BackgroundColor::Blue:
		dw = dw | (BACKGROUND_BLUE);
		break;
	case BackgroundColor::Green:
		dw = dw | (BACKGROUND_GREEN);
		break;
	case BackgroundColor::Purple:
		dw = dw | (BACKGROUND_RED | BACKGROUND_BLUE);
		break;
	case BackgroundColor::Teal:
		dw = dw | (BACKGROUND_RED | BACKGROUND_GREEN);
		break;
	case BackgroundColor::Yellow:
		dw = dw | (BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
		break;
	case BackgroundColor::White:
		dw = dw | (BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
		break;
	case BackgroundColor::Black:
		dw = dw | !(BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
		break;
	default:
		break;
	}
}
void IControl::SetBorder(BorderType _border) {
	border = _border;
}

IControl::~IControl() {}
