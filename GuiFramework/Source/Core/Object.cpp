#include "Gui.h"
#include "Core/Object.h"
#include "Core/IApplication.h"

Object::Object(const Credentials& creds, IApplication* p_app) : mp_app(p_app) {}

IApplication* Object::getApplication() {
	return mp_app;
}
