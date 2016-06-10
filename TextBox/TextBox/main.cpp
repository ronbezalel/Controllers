
#include <Windows.h>
#include <stdio.h>
#include "TextBox.h"

HANDLE hStdin;
DWORD fdwSaveOldMode;

void ErrorExit(LPSTR lpszMessage);

int main() {

	DWORD dw = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
	////////////////////////////////////////////////////////////////////////////////////////

	//TextBox controller = TextBox(20, 5, 5);
	TextBox controller = TextBox(20);
	controller.SetForeground(ForegroundColor::Green);
	controller.SetBackground(BackgroundColor::Red);
	controller.SetBorder(BorderType::None);
	//controller.Show();
	//Sleep(1111);
	controller.Show();
	

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
	int j = 0;
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