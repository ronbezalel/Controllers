#include "RadioList.h"
#include "Label.h"
#include "Controller.h"

class ComboBox : public Controller
{
private:
	Label* chosenText;
	RadioList* optionsList;
	bool displayList = false;
	int listSize;

	void EraseList();
	void KeyEventProc(KEY_EVENT_RECORD ker);
	void MouseEventProc(MOUSE_EVENT_RECORD mer);
	bool checkPosition(MOUSE_EVENT_RECORD mer);
	void CloseList();
	void OpenList();

public:
	ComboBox(string* textList, int size, short width, short height, DWORD color);
	~ComboBox();
	void Print();
	void HandleInput(INPUT_RECORD iRecord);
	string GetInput();

};

