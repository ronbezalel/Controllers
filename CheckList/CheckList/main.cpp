#include <Windows.h>
#include <stdio.h>
#include "CheckList.h"


HANDLE hStdin;
DWORD fdwSaveOldMode;

void ErrorExit(LPSTR lpszMessage);

int main() {

	/* Label Main */

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
		"xxxxxxxxxx",
		"ff"
	};

	/*Label l = Label(2, "Yossi gay 5");
	l.SetBackground(BackgroundColor::White);
	l.SetForeground(ForegroundColor::Red);
	l.SetBorder(BorderType::None);
	l.Show();*/

	//original ctor
	//CheckList controller = CheckList(list, 5, 5, 5, dw);
	//new ctor
	CheckList controller = CheckList(6, 15, list1);
	controller.SetForeground(ForegroundColor::White);
	controller.SetBackground(BackgroundColor::Green);
	controller.SetBorder(BorderType::Double);
	//controller.SelectIndex(2);
	//Sleep(1111);
	//controller.DeselectIndex(2);
	//controller.SetCoordinates(5, 5);
	controller.Show();
	Sleep(2222);
	controller.Hide();
	controller.AddSelectedItem("YOSSI GAY!");
	//Sleep(1111);
	//controller.Hide();
	Sleep(1111);
	controller.Show();
	Sleep(1111);
	controller.Hide();
	controller.RemoveSelectedItem("YOSSI GAY!");
	Sleep(1111);
	controller.Show();
	/*controller.SelectIndex(2);
	Sleep(1111);
	controller.SelectIndex(4);*/
	//Sleep(1000);
	//controller.Hide();
	vector<size_t> res = controller.GetSelectedIndices();

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