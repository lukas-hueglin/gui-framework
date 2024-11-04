#include "Gui.h"

class GUI_API Object {

public:
	virtual void onSignalReceived(int id) {};
	virtual void onSignalReceived(int id, float value) {};
	virtual void onSignalReceived(int id, int value) {};
};