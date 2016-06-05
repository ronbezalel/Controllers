
#include <Windows.h>
#include <stdio.h>
#include "Label.h"
#include "CheckList.h"
#include "RadioList.h"


HANDLE hStdin;
DWORD fdwSaveOldMode;

void ErrorExit(LPSTR lpszMessage);

int main() {

	DWORD dw = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
	////////////////////////////////////////////////////////////////////////////////////////


	/* to test one of the controllers comment the "Label main" and un-commet the requested controller */
	string list[5] = {
		"line 1",
		"line 2",
		"line 3",
		"line 4",
		"line 5"
	};

	vector<string> list1 = {
		"line 1",
		"line 2",
		"line 3",
		"line 4",
		"line 5"
	};

	Label l = Label(2, "Yossi gay 5");
	l.SetBackground(BackgroundColor::White);
	l.SetForeground(ForegroundColor::Red);
	l.SetBorder(BorderType::None);
	l.Show();

	//original ctor
	//CheckList controller = CheckList(list, 5, 5, 5, dw);
	//new ctor
	//CheckList controller = CheckList(5, 5, list1);
	//controller.SetForeground(ForegroundColor::White);
	//controller.SetBackground(BackgroundColor::Green);
	//controller.SetBorder(BorderType::Single);
	////controller.SelectIndex(2);
	//Sleep(1111);
	//controller.DeselectIndex(2);
	//controller.Show();
	//Sleep(1111);
	//controller.SelectIndex(2);
	//Sleep(1111);
	//controller.SelectIndex(5);
	//Sleep(1000);
	//controller.Hide();
	//vector<size_t> res = controller.GetSelectedIndices();

	RadioList controller = RadioList(5, 5, list1);
	controller.SetForeground(ForegroundColor::White);
	controller.SetBackground(BackgroundColor::Green);
	controller.SetBorder(BorderType::Single);
	controller.Show();
	Sleep(1111);
	controller.SetSelectIndex(5);
	Sleep(1111);
	controller.SetSelectIndex(1);
	Sleep(1111);
	controller.SetSelectIndex(1);

	DWORD cNumRead, fdwMode, i;
	INPUT_RECORD irInBuf[128];

	// Get the standard input handle. 
	hStdin = GetStdHandle(STD_INPUT_HANDLE);
	if (hStdin == INVALID_HANDLE_VALUE)
		ErrorExit("GetStdHandle");

	// Save the current input mode, to be restored on exit. 
	if (!GetConsoleMode(hStdin, &fdwSaveOldMode))
		ErrorExit("GetConsoleMode");

	// Enable the window and mouse input events. 
	fdwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
	if (!SetConsoleMode(hStdin, fdwMode))
		ErrorExit("SetConsoleMode");

	// Loop to read and handle the next 100 input events. 
	while (true)
	{
		// Wait for the events. 
		if (!ReadConsoleInput(
			hStdin,      // input buffer handle 
			irInBuf,     // buffer to read into 
			128,         // size of read buffer 
			&cNumRead)) // number of records read 
			ErrorExit("ReadConsoleInput");

		// Dispatch the events to the appropriate handler. 
		for (i = 0; i < cNumRead; i++) {
			//Send the input record to the textbox handler
			controller.HandleInput(irInBuf[i]);
		}
	}


	// Restore input mode on exit.
	SetConsoleMode(hStdin, fdwSaveOldMode);
	return 0;
}

void ErrorExit(LPSTR lpszMessage) {
	fprintf(stderr, "%s\n", lpszMessage);
	// Restore input mode on exit.
	SetConsoleMode(hStdin, fdwSaveOldMode);
	ExitProcess(0);
}