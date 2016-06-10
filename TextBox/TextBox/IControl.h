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
	BorderType border;

public:

	IControl(short width, short height);
	virtual ~IControl();
	virtual void Show() const = 0;
	virtual void Hide() = 0;
	virtual string GetValue() = 0;
	virtual void SetForeground(ForegroundColor color) = 0;
	virtual void SetBackground(BackgroundColor color) = 0;
	virtual void SetBorder(BorderType _border) = 0;
};

#endif

