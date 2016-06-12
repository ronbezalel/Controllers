
#include <Windows.h>
#include <stdio.h>
#include "ComboBox.h"
#include "TextBox.h"

HANDLE hStdin;
DWORD fdwSaveOldMode;

void ErrorExit(LPSTR lpszMessage);

int main() {

	/* Label Main */

	DWORD dw = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;

	////////////////////////////////////////////////////////////////////////////////////////


	/* to test one of the controllers comment the "Label main" and un-commet the requested controller */

	Label label = Label(40, "Eyal & Ron & Yossi");
	label.SetForeground(ForegroundColor::Green);
	label.SetCoordinates(20, 0);
	label.Show();
	Sleep(2222);
	vector<string> list = {
		"line 1",
		"line 2",
		"line 3",
		"xx",
		"line 5"
	};
	ComboBox combo = ComboBox(15, list);
	combo.SetForeground(ForegroundColor::White);
	combo.SetBackground(BackgroundColor::Blue);
	combo.SetBorder(BorderType::None);
	combo.SetCoordinates(0, 3);
	combo.Show();
	Sleep(2222);
	combo.Hide();

	RadioList radio = RadioList(5, 15, list);
	radio.SetForeground(ForegroundColor::White);
	radio.SetBackground(BackgroundColor::Blue);
	radio.SetBorder(BorderType::Double);
	radio.SetCoordinates(0, 10);
	radio.Show();
	Sleep(2222);
	radio.Hide();

	CheckList check = CheckList(5, 15, list);
	check.SetForeground(ForegroundColor::White);
	check.SetBackground(BackgroundColor::Blue);
	check.SetBorder(BorderType::Single);
	check.SetCoordinates(0, 18);
	check.Show();
	Sleep(2222);
	check.Hide();

	TextBox text = TextBox(40);
	text.SetCoordinates(20, 5);
	text.SetBackground(BackgroundColor::White);
	text.SetForeground(ForegroundColor::Blue);
	text.SetBorder(BorderType::Single);
	text.Show();
	Sleep(2222);
	text.Hide();

	combo.Show();
	radio.Show();
	text.Show();
	check.Show();
	label.Show();


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
			combo.HandleInput(irInBuf[i]);
			radio.HandleInput(irInBuf[i]);
			check.HandleInput(irInBuf[i]);
			text.HandleInput(irInBuf[i]);
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