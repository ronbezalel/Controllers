#include "IControl.h"



IControl::IControl(short width, short height) {
	if (width >= 0 && height >= 0) {
		coord = { width, height };
		handle = GetStdHandle(STD_OUTPUT_HANDLE);
		border = BorderType::None;
	}
}
IControl::~IControl() {}

