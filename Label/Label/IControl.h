#pragma once
#ifndef _ICONTROL_
#define _ICONTROL_

#include <Windows.h>
#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

enum class BorderType { Single, Double, None };
enum class ForegroundColor { Red, Blue, Green, Purple, Teal, Yellow, White, Black };
enum class BackgroundColor { Red, Blue, Green, Purple, Teal, Yellow, White, Black };
class IControl
{
protected:
	HANDLE handle;
	COORD coord;
	DWORD dw;
	BorderType border;

public:
	IControl(short width, short height);
	virtual ~IControl();
	virtual void Show() const;
	virtual void Hide();
	virtual void SetForeground(ForegroundColor color);
	virtual void SetBackground(BackgroundColor color);
	virtual void SetBorder(BorderType _border);
	virtual string GetInput() = 0;
};

#endif
