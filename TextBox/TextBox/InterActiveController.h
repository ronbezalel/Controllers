#pragma once
#include "IControl.h"
class InterActiveController : public IControl {

public:
	InterActiveController(short width, short height);
	virtual ~InterActiveController();
	virtual void KeyEventProc(KEY_EVENT_RECORD ker) = 0;
	virtual void MouseEventProc(MOUSE_EVENT_RECORD mer) = 0;
	virtual void HandleInput(INPUT_RECORD iRecord) = 0;
};

