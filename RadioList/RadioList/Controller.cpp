#include "Controller.h"



Controller::Controller(short width, short height) {
	coord = { width, height };
	handle = GetStdHandle(STD_OUTPUT_HANDLE);
}

void Controller::Print() const {

}


Controller::~Controller() {}
