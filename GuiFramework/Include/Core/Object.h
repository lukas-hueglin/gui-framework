#pragma once
#include "Gui.h"

class IApplication;

class GUI_API Credentials {
private:
	Credentials() = default;

	friend class IApplication;
};

class GUI_API Object {

private:
	IApplication* mp_app;

public:
	Object(const Credentials& creds, IApplication* p_app);

public:
	virtual void onTick(float deltaTime) {};

	virtual void onInitialize() {};
	virtual void onBegin() {};
	virtual void onClose() {};

	IApplication* getApplication();
};